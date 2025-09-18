#ifndef			__H__WAV
#define			__H__WAV

#include <stdlib.h>
#include <stdio.h>
/*wav.h - a header for the wave file library that includes
a struct for a wave file header called a wav_header .
a struct for a wav_file that has a pointer to the header, the file size, and a pointer to the
data
a function that takes the first 44 bytes of a file's contents and creates a header from it
a function that loads a wave file by calling the read_file function from the file library,
then takes the returned bytes and creates a new wav_file . It must then set the header,
data size, and pointer to the data section. It will then return a pointer to the new
wav_file .
a function that takes a wav_file and a file path, and prepares a byte array of the file. It
then calls upon our write_file function to write the new audio file to disk.*/



//deal with this later
//a struct for a wave file header called a wav_header .
struct wav_header{
    char* name;
    char* out;
    int sample;
    int channels;
    char* contents;
};
typedef struct wav_header wav_header;
//a struct for a wav_file that has a pointer to the header, the file size, and a pointer to the
//data
struct wav_file{
    wav_header* header;
    size_t size;
    char* data;
};
typedef struct wav_file wav_file;

//a function that takes the first 44 bytes of a file's contents and creates a header from it
size_t make_header(wav_header* header);

/*a function that loads a wave file by calling the read_file function from the file library,
then takes the returned bytes and creates a new wav_file . It must then set the header,
data size, and pointer to the data section. It will then return a pointer to the new
wav_file .*/
size_t load_wav(wav_header,wav_file);

/*a function that takes a wav_file and a file path, and prepares a byte array of the file. It
then calls upon our write_file function to write the new audio file to disk.*/
size_t make_wav(char* path, char* contents, size_t num_bytes);

#endif