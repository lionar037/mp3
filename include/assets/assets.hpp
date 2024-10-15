////////////////////////////////////////////////////////////////
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

namespace MP3{
    const char* getMP3Filename(int index);
}