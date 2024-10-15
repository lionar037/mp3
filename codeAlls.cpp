////////////////////////////////////////////////////////////////
//
//                      files.hpp
//
////////////////////////////////////////////////////////////////

#pragma once



////////////////////////////////////////////////////////////////
//
//                      mp3.hpp
//
////////////////////////////////////////////////////////////////

#pragma once 
#include <vector>
#include <memory>
#include <string>
#include <mpg123.h>
#include <ao/ao.h>

namespace MP3{

    class MP3Player {
    public:
        MP3Player();
        ~MP3Player();
    
        bool loadFile(const std::string& filename);
        void play();
        void stop();
    
    private:
        mpg123_handle* mh;
        ao_device* device;
        int channels;
        long rate;
        int encoding;
        size_t buffer_size;
        unsigned char* buffer;
    };

}//END MP3////////////////////////////////////////////////////////////////
//
//                      assets.hpp
//
////////////////////////////////////////////////////////////////

#pragma once

#define MP3_000 "assets/sounds/Dua Lipa TrainingSeason.mp3"
#define MP3_001 "assets/sounds/El pajaro.mp3"
#define MP3_002 "assets/sounds/Hasta que me olvides live.mp3"
#define MP3_003 "assets/sounds/Let Me Love You.mp3"
#define MP3_004 "assets/sounds/Loco tu forma de ser.mp3"
#define MP3_005 "assets/sounds/Shh a nadie lo sabra.mp3"
#define MP3_006 "assets/sounds/Tengo todo excepto a ti.mp3"
#define MP3_007 "assets/sounds/The Weeknd Like A God.mp3"
#define MP3_008 "assets/sounds/The Weeknd lithing.mp3"
#define MP3_010 "assets/sounds/dualipa.mp3"

#define MP3_SOUND(x) MP3_00 #x

const char* getMP3Filename(int index) {
    switch(index) {
        case 0: return "assets/sounds/Dua Lipa TrainingSeason.mp3";
        case 1: return "assets/sounds/El pajaro.mp3";
        case 2: return "assets/sounds/Hasta que me olvides live.mp3";
        case 3: return "assets/sounds/Let Me Love You.mp3";
        case 4: return "assets/sounds/Loco tu forma de ser.mp3";
        case 5: return "assets/sounds/Shh a nadie lo sabra.mp3";
        case 6: return "assets/sounds/Tengo todo excepto a ti.mp3";
        case 7: return "assets/sounds/The Weeknd Like A God.mp3";
        case 8: return "assets/sounds/Lithing.mp3";
        case 9: return "assets/sounds/dualipa.mp3";
        default: return nullptr;  // Devuelve nullptr si el índice no es válido
    }
}

////////////////////////////////////////////////////////////////
//
//                      main.cpp
//                      dependencies :sudo apt install libmpg123-dev
//                      g++ -std=c++17 -o mp3_player src/main.cpp -lmpg123 -lao -lpthread -I/home/pi/src/mp3/include/assets/
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <mpg123.h>
#include <ao/ao.h>
//libraries me
//#include <assets.hpp>
#include <assets/assets.hpp>
#include <mp3.hpp>

#define BITS 16


int main() {
    MP3::MP3Player player;

    // Cambia el índice según el archivo que quieras reproducir
    const char* filename = getMP3Filename(8);
    std::cout << "Reproduciendo: " << filename << "\n";

    if (!player.loadFile(filename)) {
        std::cerr << "No se pudo cargar el archivo MP3" << std::endl;
        return 1;
    }

    player.play();
    
    return 0;
}

////////////////////////////////////////////////////////////////
//
//                      files.cpp
//
////////////////////////////////////////////////////////////////

#include <assets.hpp>
#include <files.hpp>
////////////////////////////////////////////////////////////////
//
//                      mp3.cpp
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <mp3.hpp>


#define BITS 16

namespace MP3{

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

}

