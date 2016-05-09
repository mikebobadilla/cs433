#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  // Check to see if correct arguments exist
  if(argc != 2){
    printf("Incorrect Number of Arguments.\n");
    return 1;
  }

  FILE *pFile;
  // pFile = fopen("address.txt", "r");
  pFile = fopen(argv[1], "r");
  if(pFile == NULL)
  {
    // printf("Error opening a file %s: %s\n", argv[1], strerror(errno));
    exit(EXIT_FAILURE);
    // exit(1);
  }

  // READ BY CHARACTER
  char c;
  // while((c = fgetc(pFile)) != EOF)
  // {
  //   printf("%c", c);
  // }

// READ BY LINE
  printf("Read By Line\n" );
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  // int x =  28720 % 256;
  // printf("28720 and 65280: %d\n", x);
  while((read = getline(&line, &len, pFile)) != -1)
  {
      // int x = (int)*line & 65280;
      // int y = (int)*line & 255;
      // printf("Page Number = %d\n", x);
      // printf("Offset = %d\n", y);
      printf("%zd\n", *line);
  }
  free(line);
  fclose(pFile);

  exit(EXIT_SUCCESS);
}
