// Wav.c file to use the functions made in wav.h

#include <stdlib.h>
#include <stdio.h>
#include "wav.h"
#include "file_lib.h"

/**
 * make_header - Reads the first part of a WAV file and validates its header.
 * Checks that the file starts with "RIFF" and "WAVE", 
 * verifies the format type (must be 1), and confirms 
 * the file has 2 channels. It also extracts the sample rate.
 *
 * @parameters
 * wav_header* header - The header struct to validate and update.
 *
 * @returns
 * 0 if the header is valid and information was stored,
 * 1 if the header is invalid or the file could not be read.
 */
size_t make_header(wav_header* header){
    //Checks the data inside the header and makes sures its all valid, if not valid print why and return 1    
    size_t bytes = read_file(header->name, &(header->contents));
    if (bytes == 1){
        return 1; // Error reading file (read_file prints the error for us here)
    }

    //Check to see if its a RIFF file
    if (header->contents[0] == 'R' && header->contents[1] == 'I' && header->contents[2] == 'F' && header->contents[3] == 'F'){

        // Check to see if its a WAVE file
        if (header->contents[8]=='W' && header->contents[9]=='A' && 
            header->contents[10]=='V' && header->contents[11]=='E'){

            //Check format type (we want 1), making sure the shift is done correctly 
            unsigned int format_type = ((unsigned int)(unsigned char)header->contents[20])|((unsigned int)(unsigned char)header->contents[21] << 8);
            if(format_type == 1){

                //Check the number of channels (we want 2)
                header->channels = ((unsigned int)(unsigned char)header->contents[22]|((unsigned int)(unsigned char)header->contents[23] << 8));
                if (header->channels == 2){

                    //Find the sample rate
                    unsigned int sample_rate = ((unsigned int)(unsigned char)header->contents[24])|((unsigned int)(unsigned char)header->contents[25] << 8)|((unsigned int)(unsigned char)header->contents[26] << 16)|((unsigned int)(unsigned char)header->contents[27] << 24);
                    header->sample = sample_rate;
                    return 0; //If it passes all these tests return 0
                } else {
                    printf("File does not have 2 channels\n");
                    return 1;
                }
            } else {
                printf("File does not have proper format type\n");
                return 1;
            }
        } else {
            printf("File is not a proper WAVE file\n");
            return 1;
        }
    } else {
        printf("File is not a RIFF file\n");
        return 1;
    }
}

/**
 * load_wav - Loads a WAV file into memory and prepares its struct.
 * Allocates a wav_header on the heap, assigns the file name,
 * reads the file contents into memory, and stores the file size.
 *
 * @parameters
 * char* path - The path to the WAV file.
 * wav_file* file - Pointer to the wav_file struct to populate.
 *
 * @returns
 * 0 if the file was loaded successfully,
 * 1 if there was an error (read_file will print the reason).
 */
size_t load_wav(char* path, wav_file* file){
    //Loads the wav file and sets its properties to there associated values
    file->header = malloc(sizeof(wav_header)); //Makes a header on the heap we can interact with later
    file->header->name = path; //Sets the name of the file to the header thats associated to this file
    file->size = read_file(file->header->name, &(file->data)); //This sets all the data as well as returning the size of the file
    if (file->size == 1){ //read_file returns 1 in the event of an error
        return 1; //Returns 1 for an error, read_file prints out why
    } 
    return 0; 
}

/**
 * make_wav - Creates a reversed version of a WAV file and writes it to disk.
 * Copies the first 45 bytes (the header) unchanged, then reverses the rest
 * of the file data (audio samples). Writes the result to the given path.
 *
 * @parameters
 * char* path - Path to save the reversed WAV file.
 * wav_file f - The original WAV file to reverse.
 *
 * @returns
 * 0 if the file was successfully written,
 * 1 if there was an error writing the file.
 */
size_t make_wav(char* path, wav_file f){
    // The data for the file starts at byte 45 (this is important later)
    wav_file nf; // Temp wav to set data to (nf means new file)
    nf.data = malloc(f.size); //This grabs more memory to make sure we dont change f (NEED TO FREE IT LATER)
    
    // Copy header (first 45 bytes unchanged)
    for (int i = 0; i < 45; i++) {
        nf.data[i] = f.data[i];
    }

    // Reverse the audio data (bytes after 45)
    for (int i = 45; i < f.size; i++) {
        nf.data[i] = f.data[f.size - 1 - (i - 45)];
        // this works because f.size is the total size, we minus 1 due to 0 based indexing, 
        // then we minus the current index, then we minus 45 since we don't care about the first 45 bytes
    }

    // Write reversed data to file
    size_t sucess = write_file(path, nf.data, f.size);
    free(nf.data); //Frees the storage we grabbed earlier
    return sucess;
}
