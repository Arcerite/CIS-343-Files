//wav.c - a library for working with wave files. It will have the code for the functions declared in the
//wav.h header.

#include <stdlib.h>
#include <stdio.h>
#include "wav.h"
#include "file_lib.h"

//Theoretically the following checks all the needed criteria, does it work who tf knows.
size_t make_header(wav_header* header){
    
    read_file(header->name, &(header->contents));
    if (header->contents[0] == 'R' && header->contents[1] == 'I' && header->contents[2] == 'F' && header->contents[3]=='F'){
        //The first 4 bytes must correspond with the file type
        if (header->contents[8]=='W' && header->contents[9]=='A' && header->contents[10]=='V'&& header->contents[11]=='E'){
            //Makes sure its a WAV file

            unsigned int format_type = (header->contents[20]|(header->contents[21]<<8));
            if(format_type == 1){
                //Makes sure the format type is correct

                unsigned int channel_type = (header->contents[22]|(header->contents[23]<<8));
                if (channel_type == 2){
                //makes sure the channel type is two
                    return 1;
                }else{
                    printf("File does not have 2 channels\n");
                    return 0;
                }
            }else{
                printf("File does not have proper format type\n");
                return 0;
            }
        }else{
            printf("File is not a proper WAVE file\n");
            return 0;
        }
    }else{
        printf("File is not a RIFF file\n");
        return 0;
    }
}

size_t load_wav(wav_header head, wav_file file){
    return 0;
}