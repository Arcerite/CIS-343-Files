//H file for the wav library, defines the wav_header struct, the wav_file struct, and there associated methods
#ifndef	__H__WAV
#define	__H__WAV

#include <stdlib.h>
#include <stdio.h>
//Defines a wav_header, has name of the file,the sample size, the channels, and the contents of the header
struct wav_header{
    char* name;
    unsigned int sample;
    unsigned int channels;
    char* contents;
};
typedef struct wav_header wav_header;

//Defines a wav_file, has a pointer to a wav_header, the size of the data, and the data itself
struct wav_file{
    wav_header* header;
    size_t size;
    char* data;
};
typedef struct wav_file wav_file;

//Defines the make_header function. Takes in a wav_header type to assign the values to the struct
size_t make_header(wav_header*);

//Defines the load_wav function. Takes in a char* for the file path, and a pointer to a wav_file to change the values of
size_t load_wav(char *, wav_file*);

//Defines the make_Wav function. Takes in a char* for the path to the new file, and a wav_file to reverse
size_t make_wav(char*, wav_file);

#endif
