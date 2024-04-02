#include "WAVReader.h"

WAVReader::WAVReader() {

}

WAVReader::~WAVReader() {

}

WAV_FILE* WAVReader::ReadFileData(std::string url) {
	WAV_FILE* temp = new WAV_FILE();

	std::ifstream ifs(url, std::ios::binary );

	if (ifs.is_open()) {
		// Read the header
		temp->header = new WAV_HEADER;

        ifs.get((char*)(temp->header), sizeof(WAV_HEADER));

        std::stringstream sstr;
        sstr << ifs.rdbuf();
        std::string fileData = sstr.str();

        int idx = fileData.find("data");

        ifs.seekg(ifs.gcount()+idx, std::ios::beg);

        ifs.read(temp->DATA_chunk_ID, 4);

        ifs.read((char*) &temp->DATA_chunk_size, 4);

        temp->data = new std::vector<short>(temp->DATA_chunk_size/2);

        ifs.read((char*)(temp->data->data()), temp->DATA_chunk_size);
	}else {
		std::cout << "Problem opening the file...\n";
	}

    ifs.close();

	return temp;
}


