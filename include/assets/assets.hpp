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

