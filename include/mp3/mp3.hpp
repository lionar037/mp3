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
        explicit MP3Player();
        ~MP3Player();
    
        bool loadFile(const std::string& filename);
        void play();
        void stop();
    
    private:
        mpg123_handle* mh = nullptr;
        ao_device* device = nullptr;
        int channels = 0;
        long rate = 0;
        int encoding = 0;
        size_t buffer_size = 0;
        unsigned char* buffer = nullptr;
    };

} // END MP3
