////////////////////////////////////////////////////////////////
//
//                      mp3.cpp
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <mp3.h>


namespace Mp3_t{

    Mp3_t::Mp3_t(/* args */)
    {
    }

    Mp3_t::~Mp3_t()
    {
    }

}//end MP3

/*
////////////////////////////////////////////////////////////////
//
//                      main.cpp
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
//#include <mp3.hpp>

int main(int argc, char* argv[]) {
    // Inicializar SDL2
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Inicializar SDL_mixer con formato MP3
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Cargar el archivo MP3
    Mix_Music* music = Mix_LoadMUS("tu_archivo.mp3");
    if (!music) {
        std::cerr << "Error al cargar archivo MP3: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Reproducir la música (-1 es para loop infinito, 0 para reproducir una vez)
    if (Mix_PlayMusic(music, 1) == -1) {
        std::cerr << "Error al reproducir música: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Esperar mientras se reproduce la música
    std::cout << "Reproduciendo música... Presiona Enter para salir." << std::endl;
    std::cin.get();

    // Liberar recursos
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

 */