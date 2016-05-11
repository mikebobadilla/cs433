//vmgr.c
//Virtual Memory Manager
//CS433 - Final Project
//Professor: Tom Springer
//Authors: Mike Bobadilla, Nelson DeBate
//Date: 5-11-16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const int PAGE_SIZE = 256;
const int VM_SIZE = 256;
const int MM_SIZE = 128;

void increaseAge(int *memory[]);

int main(int argc, char *argv[]){

    int physical_memory[MM_SIZE];
    int virtual_memory[VM_SIZE][2];

    // INITIAL PAGE TABLE FILLING
    // [0] Physical Address [1] Age
    for(int i = 0; i < VM_SIZE; i++){
      virtual_memory[i][0] = (i > MM_SIZE)? -1 : i;
      virtual_memory[i][1] = (i > MM_SIZE)? -1 : MM_SIZE - i;
    }

    // Check to see if correct arguments exist
    if(argc != 2){
        printf("Incorrect Number of Arguments.\n");
        return 1;
    }

    FILE *pFile;
    pFile = fopen(argv[1], "r");

    //checks to see if the .txt file supplied is empty
    if(pFile == NULL){
        printf("Error opening a file %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int page_number = 0;
    int physicalAddress = 0;
    int pageFaultCount = 0;
    int loopCount = 0;

    double pageFaultRate = 0.0;

    printf("==================================\n" );
    printf("||    Virtual Memory Manager    ||\n" );
    printf("==================================\n" );
    printf("Logical Page Number Size: 8 bits\n");
    printf("Logical Offset Size: 8 bits\n");
    printf("Physical Page Number Size: 7 bits\n");
    printf("Physical Offset Size: 8 bits\n\n");

    printf("Translating 1000 Logical Addresses: \n\n");


    while((read = getline(&line, &len, pFile)) != -1){
        increaseAge(&virtual_memory);
        int offset = atoi(line) & 255;
        int page = atoi(line) & 65280;
        int page_table_number = page >> 8;
        // printf("page table number %d\n", page_table_number);

        if(virtual_memory[page_table_number] < 0){
          pageFaultRate++;
          printf("PAGE FAULT: page_table_number: %d\n", page_table_number);

          // EVICT SOMEONE
        }

        //printing formatting for Virtual Address
        if (page < 100) {
            printf("Virtual Address = %d     \t", page);
        }
        else if (page < 1000) {
            printf("Virtual Address = %d   \t", page);
        }
        else {
            printf("Virtual Address = %d  \t", page);
        }


        //calculates the physical address
        physicalAddress = (page_number * PAGE_SIZE) + offset;


        //printing formatting for Physical Address
        if (page >= 32768) {
            printf("Physical Address: DISK\n");
            pageFaultCount++;
        }
        else{
            printf("Physical Address: %d\n", physicalAddress);
        }

        //resets page number to loop back around and fill the physical addresses that weren't previously filled
        if (physicalAddress >= 32768) {
            loopCount++;
            page_number = loopCount;
        }

        page_number++;

    }

    //calculates the % of page faults
    pageFaultRate = (double) pageFaultCount / 1000 * 100;
    printf("\nPage Fault Rate: %.2f%% \n", pageFaultRate);

    free(line);
    fclose(pFile);

    exit(EXIT_SUCCESS);

}

void increaseAge(int *memory[]){
  for(int i = 0; i < VM_SIZE; i++){
    memory[i][1]++;
  }
}
