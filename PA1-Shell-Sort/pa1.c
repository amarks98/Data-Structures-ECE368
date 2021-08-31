#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "shell_array.h"
#include "shell_list.h"

int main (int argc, char** argv){
  if (argc != 4) //invalid number of arguments
    return EXIT_FAILURE;  
  long comps = 0;
  int savedNums = 0;
  if (strcmp(argv[1], "-a") == 0){
    int size = 0;
    long* array = Array_Load_From_File(argv[2], &size);
    if (array == NULL) //input failed to open or malloc failed
      return EXIT_FAILURE;
    if (size != 0)
      Array_Shellsort(array, size, &comps);
    savedNums = Array_Save_To_File(argv[3], array, size);
    free(array);
  } 
  else if (strcmp(argv[1], "-l") == 0){
    Node* list = List_Load_From_File(argv[2]);
    if (list != NULL)
      list = List_Shellsort(list, &comps);
    savedNums = List_Save_To_File(argv[3], list);
    Node* curr_node = list;
    Node* next_node;
    while(curr_node != NULL){
      next_node = curr_node->next;
      free(curr_node);
      curr_node = next_node;
    }
  }
  else //invalid second argument
    return EXIT_FAILURE;
  savedNums = savedNums + 0; //gets rid of the warning
  fprintf(stderr, "%ld\n", comps);
  return EXIT_SUCCESS;
}
