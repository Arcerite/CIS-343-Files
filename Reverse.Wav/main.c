// main.c - Core program for using the WAV library
// Loads a WAV file, validates the header, creates a reversed WAV file,
// and prints out metadata about both files.
// Returns 0 on success and 1 on failure.

#include <stdlib.h>
#include <stdio.h>
#include "wav.h"

/**
 * printer - Helper function to print information about the input WAV file
 *           and the output reversed file.
 *
 * @parameters
 * wav_file f - The loaded WAV file.
 * wav_header h - The header of the WAV file.
 * char* path - The path to the new (reversed) file.
 *
 * @returns
 * void
 */
void printer(wav_file f, wav_header h, char* path){
    printf("Name of File:\t%s\n", f.header->name);
    printf("Size of File:\t%ld\n", f.size);
    printf("Sample Rate:\t%u\n", f.header->sample);
    printf("Channel Num:\t%u\n", f.header->channels);
    printf("New File:\t%s\n", path);
}

/**
 * main - Entry point for the program.
    controls loading, validating, reversing, and printing WAV file info.
 *
 * @parameters
 * int argc - Number of command-line arguments.
 * char** argv - Array of arguments. 
 *               argv[1] = input WAV file path,
 *               argv[2] = output reversed WAV file path.
 *
 * @returns
 * 0 if success, 1 if error.
 */
int main(int argc, char** argv){
    // Note: 1 = error, 0 = success (backwards logic).
    wav_file file;

    // Step 1: Load the WAV file
    size_t bool1 = load_wav(argv[1], &file);
    if (bool1 == 1){
        printf("There were issues loading the WAV file: see above for errors. Terminating program.\n");
        return 1;
    }

    // Step 2: Validate and extract header information
    size_t bool2 = make_header(file.header);
    if (bool2 == 1){
        printf("There were issues making the header: see above for errors. Terminating program.\n");
        return 1;
    }

    // Step 3: Reverse the audio and write to a new file
    size_t bool3 = make_wav(argv[2], file);
    if (bool3 == 1){ 
        printf("There were issues making the reversed file: see above for errors. Terminating program.\n");
        return 1;
    }

    // Step 4: Print info
    printer(file, *file.header, argv[2]);

    // Step 5: Free memory and end the program
    free(file.data);             // allocated in load_wav()
    free(file.header->contents); // allocated in make_header()
    free(file.header);           // allocated in load_wav()

    return 0;
}
