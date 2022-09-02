#include "portaudio.h"

#include "WAVReader.h"

#include <iostream>

#include <chrono>
#include <ctime>

#include <cmath>

#include <SDL2/SDL.h>

#define RUN(CMD) if(!CMD) { \
                    printf("|\n| [%d] PortAudio error: %s\n|\n", __LINE__, SDL_GetError()); \
                    return; \
                 }

struct AudioData{
    Uint8* pos;
    Uint32 length;
};

void CallbackFunc(void* userData, Uint8* stream, int streamLength){
    AudioData* data = (AudioData*) userData;

    if(data->length == 0)
        return;

    Uint32 length = (Uint32) streamLength;

    length = (length > data->length) ? data->length : length;

    SDL_memcpy(stream, data->pos, length);

    data->pos += length;
    data->length -= length;
}

void PlaySoundSDL2(const char* FILE_PATH){
    // Just to make sure SDL is working
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;

	RUN( SDL_LoadWAV(FILE_PATH, &wavSpec, &wavStart, &wavLength) )

	AudioData data;
    data.pos = wavStart;
    data.length = wavLength;

    wavSpec.callback = CallbackFunc;
    wavSpec.userdata = &data;

    std::cout << "\n*============================================================*\n";
    std::cout << "\n\t Playing a file: " << FILE_PATH << std::endl;

    std::cout << "\n\t File format: " << wavSpec.format << std::endl;

    std::cout << "\n\t File frequency: " << wavSpec.freq << std::endl;
    std::cout << "\n*============================================================*\n";

	SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if(deviceID == 0){
        std::cerr << "Error loading a device...";
        return;
    }

    SDL_PauseAudioDevice(deviceID, 0);

    while(data.length > 0){
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(deviceID);
	SDL_FreeWAV(wavStart);

	SDL_Quit();
}