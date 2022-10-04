#include "Player.h"

#include <thread>

Player::Player(){
    SDL_Init(SDL_INIT_AUDIO);

    this->soundData = new AudioData;
    this->soundData->spec = new SDL_AudioSpec;

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

long long Player::value = 0;
double Player::freq = 1;

static int lastSample = 0;

static void callbackFunc(void* userData, Uint8* stream, int streamLength){
    AudioData* data = (AudioData*) userData;

    if(data->currentLength == 0)
        return;

    Uint32 length = (Uint32) streamLength;

    length = (length > data->currentLength) ? data->currentLength : length;

    /*SDL_memcpy(stream, data->currentPos, length);*/

    Player::value = 0;
    Player::freq = 0;

    for(int i=0;i<length;++i){
        *(stream+i) = *(data->currentPos+i);
        if(i%2==0){
            int sample = *(stream+i-1)<<8 + *(stream+i);
            
            if(lastSample*sample <= 0){
                Player::freq+=1;
            }
            
            lastSample = (sample>=0) ? 1 : -1;

            Player::value += sample;
        }
    }

    std::cout << "Avg. value: " << Player::value/length*2 << "\n";
    std::cout << "Avg. freq: " << Player::freq/length*2.0 << "\n";

    data->currentPos += length;
    data->currentLength -= length;
}

void Player::loadData(){
    RUN( SDL_LoadWAV(filePath, soundData->spec,
                               &soundData->dataPos,
                               &soundData->dataLength) )


    soundData->spec->callback = callbackFunc;
    soundData->spec->userdata = soundData;
}

void Player::handleSound(bool* playing, AudioData* sound){
	SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, sound->spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if(deviceID == 0){
        std::cerr << "Error loading a device...";
        return;
    }

    SDL_PauseAudioDevice(deviceID, 0);

    while(*playing && sound->currentLength > 0){
        SDL_Delay(100);
    }

    *playing = false;

    SDL_CloseAudioDevice(deviceID);
}


void Player::playSound(const char* filePath){
    if(this->playing)
        return;
    
    this->filePath = filePath;
    this->playing = true;

    loadData();

    soundData->currentPos = soundData->dataPos;
    soundData->currentLength = soundData->dataLength;

    this->futureCall = std::async(std::launch::async, 
                                  handleSound, &playing, soundData);                               
}

void Player::restartSound(){
    soundData->currentPos = soundData->dataPos;
    soundData->currentLength = soundData->dataLength;

    if(!this->playing){
        this->playing = true;

        this->futureCall = std::async(std::launch::async, 
                                  handleSound, &playing, soundData);
    }
}

void Player::continueSound(){
    if(this->playing)
        return;
    
    this->playing = true;

    this->futureCall = std::async(std::launch::async, 
                                  handleSound, &playing, soundData);
}

void Player::stopSound(){
    if(!this->playing)
        return;
    
    this->playing = false;
}
