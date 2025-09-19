//This is the core program to use, Loads a wav file, makes the header, makes the reverse wav file, and prints out data associated to it
//Returns 0 on sucess and 1 on fail
#include <stdlib.h>
#include <stdio.h>
#include "wav.h"

//printer - Prints information about a WAV file and its output file (to keep main clean).
void printer(wav_file f, wav_header h, char* path){
    printf("Name of File:\t%s\n", f.header->name);
    printf("Size of File:\t%ld\n", f.size);
    printf("Sample Eate:\t%u\n", f.header->sample);
    printf("Channel Num:\t%u\n", f.header->channels);
    printf("New File:\t%s\n", path);
}

//main - The MAIN (ba dunce) code that runs the entire program
int main(int argc, char** argv){
    // Note: 1 means error, 0 means success (inverted logic (WHY THO!))
    wav_file file;

    // Step 1: Load WAV file 
    size_t bool1 = load_wav(argv[1], &file);
    if (bool1 == 1){
        printf("There were issues loading the wav file: see above for errors: Terminating program\n");
        return 1;
    }

    // Step 2: make sure the header is correct
    size_t bool2 = make_header(file.header);
    if (bool2 == 1){
        printf("There were issues making the header: See above statements for errors: Terminating program\n");
        return 1;
    }

    // Step 3: Reverse the audio and make a new file
    size_t bool3 = make_wav(argv[2], file);
    if (bool3 == 1){ //Nice
        printf("There were issues making the reverse file: see above for errors: Terminating Program\n");
        return 1;
    }

    // Step 4: Print all the info
    printer(file, *file.header, argv[2]);

    // Step 5: Freedom
    free(file.header); 
    return 0;
}
