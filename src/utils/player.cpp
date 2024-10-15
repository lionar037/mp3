////////////////////////////////////////////////////////////////
//
//                      player.cpp
//                      dependencies :sudo apt install libmpg123-dev
//                      g++ -std=c++17 -o mp3_player src/main.cpp -lmpg123 -lao -lpthread -I/home/pi/src/mp3/include/assets/
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <mpg123.h>
#include <ao/ao.h>
//libraries me
#include <assets.hpp>
#include <mp3.hpp>

#define BITS 16

namespace MP3{
        
    int player() {
        MP3Player player;

        // Cambia el índice según el archivo que quieras reproducir
        const char* filename = MP3::getMP3Filename(8);
        std::cout << "Reproduciendo: " << filename << "\n";

        if (!player.loadFile(filename)) {
            std::cerr << "No se pudo cargar el archivo MP3" << std::endl;
            return 1;
        }

        player.play();
        
        return 0;
    }

}