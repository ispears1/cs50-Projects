//A Program that reverses an input .wav file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    // Read header
    WAVHEADER input_header;
    fread(&input_header, sizeof(WAVHEADER), 1, input_file);

    // Use check_format to ensure WAV format
    if (check_format(input_header) == 0)
    {
        printf("Incorrect input file format\n");
        return 1;
    }

    // Open output file for writing
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("Error opening output file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&input_header, sizeof(WAVHEADER), 1, output_file);

    // Use get_block_size to calculate size of each block of audio data
    int block_size = get_block_size(input_header);

    // Array to collect audio data from input file
    BYTE Audio_Data[block_size];

    // Moves input_file pointer to the end of the file
    fseek(input_file, 0, SEEK_END);

    // ftell returns size of entire file, audio data size is calculated as ftell minus the size of the header.
    long audio_data_size = ftell(input_file) - sizeof(WAVHEADER);

    // The number of audio block is the entire audio data divided by the block size.
    int audio_blocks = (int) audio_data_size / block_size;

    // Travels the input files audio blocks in reverse and writes them to the output file.
    for (int parse = 1; parse < audio_blocks + 1; parse++)
    {
        fseek(input_file, -(parse * block_size), SEEK_END);
        fread(Audio_Data, block_size, 1, input_file);
        fwrite(Audio_Data, block_size, 1, output_file);
    }

    // Closes files
    fclose(input_file);
    fclose(output_file);
}

int check_format(WAVHEADER header)
{
    char correct_filetype[] = {'W', 'A', 'V', 'E', '\0'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != correct_filetype[i])
        {
            return 0;
        }
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    return (header.numChannels * (header.bitsPerSample / 8));
}
