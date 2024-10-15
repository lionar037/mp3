#include <assets.hpp>


namespace MP3{

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

}

