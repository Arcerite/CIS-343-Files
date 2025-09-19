// wav.h - Header file for the WAV library
// Defines the wav_header struct, the wav_file struct, and their associated functions.

#ifndef __H__WAV
#define __H__WAV

#include <stdlib.h>
#include <stdio.h>

/**
 * wav_header - Stores metadata for a WAV file.
 * Contains the file name, sample rate, channel count,
 * and the raw header contents.
 */
struct wav_header {
    char* name;           // File name
    unsigned int sample;  // Sample rate
    unsigned int channels;// Number of channels
    char* contents;       // First 44 bytes (header data)
};
typedef struct wav_header wav_header;

/**
 * wav_file - Represents a full WAV file in memory.
 * Contains a pointer to a header struct, the total file size,
 * and the raw data contents.
 */
struct wav_file {
    wav_header* header; // Pointer to the file header
    size_t size;        // File size in bytes
    char* data;         // Full file contents
};
typedef struct wav_file wav_file;

/**
 * make_header - Validates a WAV file header and extracts metadata.
 *
 * @parameters
 * wav_header* - Pointer to the wav_header struct to validate and populate.
 *
 * @returns
 * 0 if the header is valid, 1 if invalid or error.
 */
size_t make_header(wav_header*);

/**
 * load_wav - Loads a WAV file into memory.
 * Allocates a header, sets file metadata, and stores data contents.
 *
 * @parameters
 * char* - Path to the WAV file.
 * wav_file* - Pointer to the wav_file struct to populate.
 *
 * @returns
 * 0 if the file was loaded successfully, 1 if error.
 */
size_t load_wav(char*, wav_file*);

/**
 * make_wav - Creates a reversed version of a WAV file and writes it to disk.
 *
 * @parameters
 * char* - Path to the new (reversed) WAV file.
 * wav_file - The original WAV file to reverse.
 *
 * @returns
 * 0 if the file was written successfully, 1 if error.
 */
size_t make_wav(char*, wav_file);

#endif
