////////////////////////////////////////////////////////////////
//
//                      main.cpp
//                      dependencies :sudo apt install libmpg123-dev
//                      g++ -std=c++17 -o mp3_player src/main.cpp -lmpg123 -lao -lpthread -I/home/pi/src/mp3/include/assets/
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <mp3_memory.hpp>
#include <assets.hpp>

int main() {
    MP3::MP3MemoryPlayer player;

    // Cambia el índice según el archivo que quieras reproducir
    const char* filename = MP3::getMP3Filename(8);
    std::cout << "Reproduciendo desde memoria: " << filename << "\n";

    if (!player.loadFileToMemory(filename)) {
        std::cerr << "No se pudo cargar el archivo MP3 en memoria" << std::endl;
        return 1;
    }

    player.play();
    
    return 0;
}
