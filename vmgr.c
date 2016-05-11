#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const int BLOCK_SIZE = 256;

int main(int argc, char *argv[])
{
  // Check to see if correct arguments exist
  if(argc != 2){
    printf("Incorrect Number of Arguments.\n");
    return 1;
  }

  FILE *pFile;
  pFile = fopen(argv[1], "r");
  if(pFile == NULL)
  {
    printf("Error opening a file %s: %s\n", argv[1], strerror(errno));
    exit(EXIT_FAILURE);
  }

// READ BY LINE
  printf("Read By Line\n" );
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int page_number = 0;
  while((read = getline(&line, &len, pFile)) != -1)
  {
      int offset = atoi(line) & 255;
      int page = atoi(line) & 65280;
      // printf("Page Number = \t\t%d\n", page);
      // printf("Offset = \t\t%d\n", offset);
      printf("Physical Address: \t%d\n", (page_number * BLOCK_SIZE) + offset);
      page_number++;
  }
  free(line);
  fclose(pFile);

  exit(EXIT_SUCCESS);
}
