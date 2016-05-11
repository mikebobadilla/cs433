#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    //checks to see if correct number of arguments exist
    if(argc != 2){
        printf("Incorrect Number of Arguments.\n");
        return 1;
    }


    FILE *pFile;
    pFile = fopen("address.txt", "r");
    pFile = fopen(argv[1], "r");


    //checks to see if the .txt file supplied is empty
    if(pFile == NULL){
        printf("Error opening a file %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
        exit(1);
    }

//     READ BY CHARACTER
//    char c;
//     while((c = fgetc(pFile)) != EOF)
//     {
//       printf("%c", c);
//     }

    // READ BY LINE
    printf("Read By Line\n" );
    char *line = NULL;
    size_t len = 0;
    ssize_t read;


    char *virtualAddress = NULL;
    char virtualPageNumber[2];
    char virtualOffset[2];


    char physicalAddress[4];
    char physicalPageNumber[2];
    char physicalOffset[2];


    while((read = getline(&line, &len, pFile)) != -1){

        virtualAddress = line;

        //gets the Virtual Page Number and Offset from the Virtual Address
        strncpy(virtualPageNumber, virtualAddress, 2);
        strncpy(virtualOffset, virtualAddress + 2, 2);

        //automatically copies virtual offset and assigns it to the physical offset
        strncpy(physicalOffset, virtualOffset, 2);








    }


    free(line);
    fclose(pFile);

    exit(EXIT_SUCCESS);
}
