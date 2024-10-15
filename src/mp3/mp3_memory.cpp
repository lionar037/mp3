#include <mp3_memory.hpp>
#include <iostream>
#include <fstream>

#define BITS 16

namespace MP3 {

    MP3MemoryPlayer::MP3MemoryPlayer() 
    : mh(nullptr), device(nullptr), buffer(nullptr) 
    {
        mpg123_init();
        int err = 0;
        mh = mpg123_new(nullptr, &err);
        if (mh == nullptr) {
            std::cerr << "Failed to create mpg123 handle: " << mpg123_plain_strerror(err) << std::endl;
        }
    }

    MP3MemoryPlayer::~MP3MemoryPlayer() {
        if (mh) {
            mpg123_close(mh);
            mpg123_delete(mh);
            mpg123_exit();
        }
        if (buffer) {
            free(buffer);
        }
        if (device) {
            ao_close(device);
            ao_shutdown();
        }
    }

    bool MP3MemoryPlayer::loadFileToMemory(const std::string& filename) {
        if (!mh) {
            return false;
        }

        // Leer el archivo MP3 completo a memoria
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file) {
            std::cerr << "Failed to open MP3 file: " << filename << std::endl;
            return false;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        mp3_data.resize(size);
        if (!file.read((char*)mp3_data.data(), size)) {
            std::cerr << "Failed to read MP3 file: " << filename << std::endl;
            return false;
        }

        int err = mpg123_open_feed(mh);
        if (err != MPG123_OK) {
            std::cerr << "Failed to open feed for MPG123: " << mpg123_strerror(mh) << std::endl;
            return false;
        }

        mpg123_getformat(mh, &rate, &channels, &encoding);
        std::cout << "Rate: " << rate << "Hz, Channels: " << channels << ", Encoding: " << encoding << std::endl;

        // Inicializar la salida de audio
        ao_initialize();
        int driver = ao_default_driver_id();
        ao_sample_format format;
        format.bits = BITS;
        format.channels = channels;
        format.rate = rate;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;
        device = ao_open_live(driver, &format, nullptr);
        if (device == nullptr) {
            std::cerr << "Error opening audio device" << std::endl;
            return false;
        }

        buffer_size = mpg123_outblock(mh);
        buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
        return true;
    }

    void MP3MemoryPlayer::play() {
        if (!mh || !device || mp3_data.empty()) {
            return;
        }

        size_t done = 0;
        while (mpg123_feed(mh, mp3_data.data(), mp3_data.size()) == MPG123_OK) {
            while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
                ao_play(device, (char*)buffer, done);
            }
        }
    }

    void MP3MemoryPlayer::stop() {
        // Cleanup handled in destructor
    }

}
