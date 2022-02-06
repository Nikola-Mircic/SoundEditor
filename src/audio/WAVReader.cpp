#include "WAVReader.h"

#include "wx/filesys.h"

WAVReader::WAVReader() {
	sound = nullptr;
}

WAVReader::~WAVReader() {
}

WAV_FILE* WAVReader::GetLastSound() {
	return sound;
}

WAV_FILE* WAVReader::ReadFileData(std::string url, std::string filename) {
	WAV_FILE* temp = new WAV_FILE();

	FILE* file = fopen(url.append(filename).c_str(), "rb");

	if (file != NULL) {
		// Read the header
		temp->header = new WAV_HEADER();

		size_t bytesRead = fread(temp->header, 1, 44, file);

		if (bytesRead > 0){
			// Read the data
			temp->data = new std::vector<char>(temp->header->DATA_chunk_size);

			fseek(file, bytesRead, SEEK_SET);

			bytesRead = fread(temp->data->data(), 1, temp->header->DATA_chunk_size, file);
		}

		fclose(file);

		sound = temp;
	}

	return temp;
}

