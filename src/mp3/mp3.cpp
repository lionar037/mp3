////////////////////////////////////////////////////////////////
//
//                      mp3.cpp
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <mp3.hpp>


#define BITS 16

namespace MP3
{

    MP3Player::MP3Player() 
    : mh(nullptr), device(nullptr), buffer(nullptr) 
    {
        mpg123_init();
        int err = 0;
        mh = mpg123_new(NULL, &err);
        if (mh == NULL) {
            std::cerr << "Failed to create mpg123 handle: " << mpg123_plain_strerror(err) << std::endl;
        }
    }

    MP3Player::~MP3Player() {
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

    bool MP3Player::loadFile(const std::string& filename) {
        if (!mh) {
            return false;
        }

        int err = mpg123_open(mh, filename.c_str());
        if (err != MPG123_OK) {
            std::cerr << "Failed to open MP3 file: " << mpg123_strerror(mh) << std::endl;
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
        device = ao_open_live(driver, &format, NULL);
        if (device == NULL) {
            std::cerr << "Error opening audio device" << std::endl;
            return false;
        }

        buffer_size = mpg123_outblock(mh);
        buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
        return true;
    }

    void MP3Player::play() {
        if (!mh || !device) {
            return;
        }

        while (mpg123_read(mh, buffer, buffer_size, &buffer_size) == MPG123_OK) {
            ao_play(device, (char *)buffer, buffer_size);
        }
    }

    void MP3Player::stop() {
        // Cleanup will be handled in the destructor
    }

}

/*
    MP3Player::MP3Player() {
        mpg123_init();
        int err = 0;
        mh = mpg123_new(NULL, &err);
        if (mh == NULL) {
            std::cerr << "Failed to create mpg123 handle: " << mpg123_plain_strerror(err) << std::endl;
        }
    }

    MP3Player::~MP3Player() {
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

    bool MP3Player::loadFile(const std::string& filename) {
        if (!mh) {
            return false;
        }

        int err = mpg123_open(mh, filename.c_str());
        if (err != MPG123_OK) {
            std::cerr << "Failed to open MP3 file: " << mpg123_strerror(mh) << std::endl;
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
        device = ao_open_live(driver, &format, NULL);
        if (device == NULL) {
            std::cerr << "Error opening audio device" << std::endl;
            return false;
        }

        buffer_size = mpg123_outblock(mh);
        buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
        return true;
    }

    void MP3Player::play() {
        if (!mh || !device) {
            return;
        }

        while (mpg123_read(mh, buffer, buffer_size, &buffer_size) == MPG123_OK) {
            ao_play(device, (char *)buffer, buffer_size);
        }
    }

    void MP3Player::stop() {
        // Cleanup will be handled in the destructor
    }
*/


