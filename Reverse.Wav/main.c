/*main.c - the core file that will use the libraries I gave you and the one you created. The code for
reversing the data samples should be in this file.*/

#include <stdlib.h>
#include <stdio.h>
#include "wav.h"

int main(int argc, char** argv){
    wav_header head;
    head.name = argv[1];
    make_header(&head);
    printf("%s\n",head.name);



    return 0;
}