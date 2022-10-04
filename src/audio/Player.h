#pragma once

#include <iostream>
#include <future>

#include <SDL2/SDL.h>

#include "WAVReader.h"

#define RUN(CMD) if(!CMD) { \
                    printf("|\n| [%d] PortAudio error: %s\n|\n", __LINE__, SDL_GetError()); \
                    return; \
                 }

struct AudioData{
    SDL_AudioSpec* spec;

    Uint8* dataPos;
    Uint8* currentPos;

    Uint32 dataLength;
    Uint32 currentLength;
};

class Player{
public:
    Player();

    ~Player();

    void playSound(const char* filePath);
    void stopSound();
    void restartSound();
    void continueSound();

    static long long value;
    static double freq;

    static void handleSound(bool* playing, AudioData* sound);
    void loadData();

private:
    AudioData* soundData;
    const char* filePath;
    bool playing;

    std::future<void> futureCall;
};
