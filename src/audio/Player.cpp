#include "Player.h"

#include <thread>
#include <iostream>

Animator* Player::animator = nullptr;

Player::Player(Animator* animator){
    SDL_Init(SDL_INIT_AUDIO);

    this->animator = animator;

    this->soundData = new AudioData;
    this->soundData->spec = new SDL_AudioSpec();

    this->filePath = "";
    this->playing = false;
}

Player::~Player(){
	if(soundData->dataPos)
        SDL_FreeWAV(soundData->dataPos);
    SDL_Quit();

    playing = false;

    delete soundData->spec;
    delete soundData;
}

double Player::value = 0;
double Player::freq = 1;

static int lastSample = 0;

static void callbackFunc(void* userData, Uint8* stream, int streamLength){
    AudioData* data = (AudioData*) userData;

    if(data->currentLength == 0)
        return;

    Uint32 length = (Uint32) streamLength;

    length = (length > data->currentLength) ? data->currentLength : length;

    Player::value = 0;
    Player::freq = 0;

    for(int i=0;i<length;++i){
        *(stream+i) = *(data->currentPos+i);
        if(i%2==0){
            short sample = *(stream+i+1)<<8 | *(stream+i);
            
            sample = std::abs(sample);

            if(lastSample*sample <= 0){
                Player::freq+=1;
            }
            
            lastSample = (sample>=0) ? 1 : -1;

            Player::value += sample*1.0/(length);
        }
    }

    Player::freq/=(1.0*length)/(data->spec->freq);

    if(Player::animator){
        sample s = std::make_pair(Player::value, Player::freq);

        // Push new data to animator
        (Player::animator->tslist).push(s);
    }

    data->currentPos += length;
    data->currentLength -= length;
}

void Player::loadData(){
    std::cout << "Loading from : " << filePath << std::endl;

    SDL_LoadWAV(filePath, soundData->spec, &soundData->dataPos, &soundData->dataLength);

    std::cout << "========> Data loaded <============= " << std::endl;
    std::cout << "Size: " << soundData->dataLength << " bytes" << std::endl;
    std::cout << "Chanels: "<< (int) soundData->spec->channels << " @ " << soundData->spec->freq << "Hz" << std::endl;
    std::cout << "==================================== " << std::endl;

    soundData->spec->callback = callbackFunc;
    soundData->spec->userdata = soundData;
}

void Player::handleSound(bool* playing, AudioData* sound){
	SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, sound->spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if(deviceID == 0){
        std::cerr << "Error loading a device..." << std::endl;

        std::cerr << SDL_GetError();
        return;
    }

    SDL_PauseAudioDevice(deviceID, 0);

    while(*playing && sound->currentLength > 0){
        SDL_Delay(100);
    }

    *playing = false;

    SDL_CloseAudioDevice(deviceID);

    if(animator)
        animator->ActivateRenderLoop(false); 
}


void Player::playSound(const char* filePath){
    std::cout << "Playing sound ... " << std::endl;

    if(this->playing)
        return;

    std::cout << filePath << std::endl;

    this->filePath = filePath;
    this->playing = true;

    loadData();

    soundData->currentPos = soundData->dataPos;
    soundData->currentLength = soundData->dataLength;

    std::thread handler(handleSound, &playing, soundData);
    handler.detach();
}

void Player::restartSound(){
    soundData->currentPos = soundData->dataPos;
    soundData->currentLength = soundData->dataLength;

    if(!this->playing){
        this->playing = true;

        std::thread handler(handleSound, &playing, soundData);
        handler.detach();
    }
}

void Player::continueSound(){
    if(this->playing || !soundData)
        return;
    
    this->playing = true;

    std::thread handler(handleSound, &playing, soundData);
    handler.detach();
}

void Player::stopSound(){
    if(!this->playing)
        return;
    
    if(animator)
       animator->ActivateRenderLoop(false); 
    this->playing = false;
}
