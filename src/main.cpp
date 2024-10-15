////////////////////////////////////////////////////////////////
//
//                      main.cpp
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
//sudo apt install libmpg123-dev
#include <mpg123.h>

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
    const char* filename = "assets/sounds/dualipa.mp3";
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

    // Reproducir audio
    size_t buffer_size;
    unsigned char* buffer;
    err = mpg123_outblock(mh);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

    while (mpg123_read(mh, buffer, buffer_size, &buffer_size) == MPG123_OK) {
        // Aquí puedes hacer lo que quieras con los datos del audio (por ejemplo, reproducirlo)
    }

    // Limpiar
    free(buffer);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    return 0;
}
