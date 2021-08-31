#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"

long *Array_Load_From_File (char *filename, int *size){
  FILE* fptr = fopen(filename, "rb");
  if (fptr == NULL){ //input fails to open
    *size = 0;
    fclose(fptr);
    return NULL;
  }  
  fseek(fptr, 0, SEEK_END);
  long pos = ftell(fptr); //file size in bytes
  *size = (int) pos/sizeof(long);
  fseek(fptr, 0, SEEK_SET);
  long* array = malloc(*size * sizeof(long)); //multiple of sizeof(long)
  if (array == NULL){ //malloc failed
    fclose(fptr);
    *size = 0;
    return NULL;
  }
  for (int i = 0; i < *size; i++){
    fread(&(array[i]), sizeof(long), 1, fptr);
  }
  fclose(fptr);
  return array;
}

int Array_Save_To_File (char *filename, long *array, int size){
  FILE* fptr = fopen(filename, "wb");
  if ((fptr == NULL) || (size == 0)){ //output file failed to open
    if (fptr != NULL)
      fclose(fptr); //empty file created
    return 0;
  }  
  int i;
  for (i = 0; i < size; i++)
    fwrite(&(array[i]), sizeof(long), 1, fptr);
  fclose(fptr);
  return i;
}

void Array_Shellsort (long *array, int size, long *n_comp){
  if ((array == NULL) || (size == 0)){
    *n_comp = 0;
    return;
  }
  int maxK = 1;
  while (size > maxK) //find maxK
    maxK = 3*maxK + 1;
  for (int k = (maxK-1)/3; k >= 1; k = (k-1)/3){
    for (int j = k; j < size; j++){
      long temp = array[j];
      int i = j;
      while ((i >= k) && (array[i-k] > temp)){
	*n_comp += 1; //while loop comp
	array[i] = array[i-k];
	i -= k;
      }
      *n_comp += 1; //breakout comp
      array[i] = temp;
    }
  }
}


