#pragma once

#include <cstdint>
#include <cstdlib>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <fstream>
#include <sstream>

#include <algorithm>
#include <iterator>

struct WAV_HEADER {
	//RIFF
	char RIFF_chunk_ID[4];
	int RIFF_chunk_size;
	char RIFF_format[4];
	//FMT
	char FMT_chunk_ID[4];
	int FMT_chunk_size;
	short FMT_audio_format;
	short FMT_num_channels;
	int FMT_sample_rate;
	int FMT_byte_rate;
	short FMT_block_align;
	short FMT_bits_per_sample;
};

struct WAV_FILE {
	WAV_HEADER* header;

    //Data
    char DATA_chunk_ID[4];
    int DATA_chunk_size;
	std::vector<short>* data;
};

class WAVReader {
public:
	WAVReader();
	~WAVReader();

	WAV_FILE* ReadFileData(std::string url);
private:
};