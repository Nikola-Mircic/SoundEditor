#include "WAVReader.h"

#include <iostream>
#include <fstream>

WAVReader::WAVReader() {

}

WAVReader::~WAVReader() {

}

WAV_FILE* WAVReader::ReadFileData(std::string url) {
	WAV_FILE* temp = new WAV_FILE();

	std::ifstream ifs(url);

	if (ifs.is_open()) {
		// Read the header
		temp->header = new WAV_HEADER;

        std::cout << "Reading header ... " << std::endl;

		ifs.get((char*)(temp->header), 44);

        std::cout << "Reading data ... " << std::endl;

        // Read the samples
        long bytesRead = ifs.gcount();
		if (bytesRead > 0){
            // PCM
            if(temp->header->FMT_audio_format == 1){
                temp->data = new std::vector<short>(temp->header->DATA_chunk_size/2);

                ifs.get((char*)(temp->data->data()), temp->header->DATA_chunk_size);

                std::cout << "Loaded " << temp->data->size()*2 << " bytes of data! " << std::endl;
            }else{
                std::cout << "Audio format is " << temp->header->FMT_audio_format << "! \n";
                std::cout << "Program stoped" << std::endl;
            }
        }else{
            std::cout <<  "Bytes read [ " << bytesRead << "] <= 0 !" << std::endl;
        }
	}else {
		std::cout << "Problem opening the file...\n";
	}

    ifs.close();

	return temp;
}

