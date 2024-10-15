////////////////////////////////////////////////////////////////
//
//                      main.cpp
//                      dependencies :sudo apt install libmpg123-dev
//g++ -std=c++17 -o mp3_player src/main.cpp -lmpg123 -lao -lpthread -I/home/pi/src/mp3/include/assets/
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <mpg123.h>
#include <assets.hpp>
#include <ao/ao.h>
#define BITS 16
//#include "../include/assets/assets.hpp"


int main() {
    mpg123_handle *mh;
    mpg123_init();
    int err = 0;
    mh = mpg123_new(NULL, &err);
    if (mh == NULL) {
        std::cerr << "Failed to create mpg123 handle: " << mpg123_plain_strerror(err) << std::endl;
        return 1;
    }

    // Abrir archivo MP3
    const char* filename = getMP3Filename(8);  // Cambia el índice según el archivo que quieras reproducir
    std::cout << "mp3 : " <<getMP3Filename(8)<<"\n";

    err = mpg123_open(mh, filename);
    if (err != MPG123_OK) {
        std::cerr << "Failed to open MP3 file: " << mpg123_strerror(mh) << std::endl;
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        return 1;
    }

    // Configurar formato de salida
    int channels, encoding;
    long rate;
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
    ao_device *device = ao_open_live(driver, &format, NULL);
    if (device == NULL) {
        std::cerr << "Error opening audio device" << std::endl;
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        return 1;
    }

    // Reproducir audio
    size_t buffer_size;
    unsigned char* buffer;
    err = mpg123_outblock(mh);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

    while (mpg123_read(mh, buffer, buffer_size, &buffer_size) == MPG123_OK) {
        ao_play(device, (char *)buffer, buffer_size);
    }

    // Limpiar
    free(buffer);
    ao_close(device);
    ao_shutdown();
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    return 0;
}

