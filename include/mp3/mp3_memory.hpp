#pragma once
#include <mpg123.h>
#include <ao/ao.h>
#include <vector>
#include <string>

namespace MP3 {

    class MP3MemoryPlayer {
    public:
        explicit MP3MemoryPlayer();
        ~MP3MemoryPlayer();

        bool loadFileToMemory(const std::string& filename);
        void play();
        void stop();

    private:
        mpg123_handle* mh = nullptr;
        ao_device* device = nullptr;
        std::vector<unsigned char> mp3_data;
        int channels = 0;
        long rate = 0;
        int encoding = 0;
        size_t buffer_size = 0;
        unsigned char* buffer = nullptr;
    };

}
