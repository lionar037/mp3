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

}//END MP3