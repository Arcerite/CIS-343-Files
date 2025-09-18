#ifndef			__H__FILE_LIB__
#define			__H__FILE_LIB__

#include <stdlib.h>
#include <stdio.h>

/**
 * Reads a file at the location specified by path into
 * memory.  Allocates the required number of bytes after
 * checking file size.  Stores location of stored bytes
 * in *file_contents.
 * 
 * @parameters
 * char* path - The path to the file we want read.
 * char** file_contents - The location in memory where we 
 *                        wish to store the file data.
 * @return The number of bytes read.
 */
size_t read_file(char* path, char** file_contents);

/**
 * Writes a file to disk.
 *
 * @parameters
 * char* path - The path where we wish to save the file.
 * char* file_contents - The location of the file's bytes.
 * size_t num_bytes - The number of bytes to save.
 */
size_t write_file(char* path, char* file_contents, size_t num_bytes);

size_t read_file(char* path, char** file_contents){
    FILE *file = fopen(path, "rb"); // Open the file in binary mode
    if (file == NULL) {
        perror("File opening failed");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    if (size == -1) {
        perror("ftell failed");
        fclose(file);
        return 1;
    }
    fseek(file, 0, SEEK_SET);
    
    *file_contents = malloc(size * sizeof(char));
    fread(*file_contents, 1, size, file);
    fclose(file);
    return size;
}

size_t write_file(char* path, char* file_contents, size_t num_bytes){
	FILE * file = fopen(path, "wb");
	if(file == NULL){
		perror("File opening for write failed.");
		return 1;
	}
	size_t bytes_written = fwrite(file_contents, 1, num_bytes, file);
	fclose(file);

	return bytes_written;
}
#endif