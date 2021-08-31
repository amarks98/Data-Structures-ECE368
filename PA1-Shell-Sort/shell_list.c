#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"

typedef struct _List {
  Node* node;
  struct _List *next;
} List;

Node *List_Load_From_File(char *filename){
  FILE* fptr = fopen(filename, "rb");
  if (fptr == NULL)
    return NULL;
  fseek(fptr, 0, SEEK_END);
  int size = ftell(fptr)/sizeof(long);
  fseek(fptr, 0, SEEK_SET);
  Node* list = malloc(sizeof(Node));
  if (list == NULL){ //malloc fails
    fclose(fptr);
    return NULL;
  }
  fread(&(list->value), sizeof(long), 1, fptr); //fill in first node
  list->next = NULL;
  Node* prev_node = list;
  for (int i = 1; i < size; i++){
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL){ //malloc fails
      Node* curr = list;
      Node* next;
      while (curr != NULL){
	next = curr->next;
	free(curr);
	curr = next;
      }	
      fclose(fptr);
      return NULL;
    }
    fread(&(new_node->value), sizeof(long), 1, fptr);
    new_node->next = NULL;
    prev_node->next = new_node;
    prev_node = new_node;
  }
  fclose(fptr);
  return list;
}

int List_Save_To_File(char *filename, Node *list){
  FILE* fptr = fopen(filename, "wb");
  if (fptr == NULL)
    return 0;
  int save_count = 0;
  Node* curr_node = list;
  while(curr_node != NULL){
    fwrite(&(curr_node->value), sizeof(long), 1, fptr);
    save_count++;
    curr_node = curr_node->next;
  }
  fclose(fptr);
  return save_count;
}

Node *List_Shellsort(Node *list, long *n_comp){
  if (list == NULL)
    return NULL;
  int size = 0;
  Node* node = list;
  while (node != NULL){
    size++;
    node = node->next;
  }
  int maxK = 1;
  while (size > maxK)
    maxK = 3*maxK + 1; 
  Node* currNode = list;
  for (int k = (maxK-1)/3; k > 1; k = (k-1)/3){
    List* lists = malloc(sizeof(List));
    if (lists == NULL)
      return currNode;
    Node* temp = currNode;
    currNode = currNode->next;
    temp->next = NULL;
    lists->node = temp;
    lists->next = NULL;
    List* currList = lists;
    for (int i = 1; i < size; i++){ //add nodes to sublists in reverse
      Node* currentNode = currNode;
      currNode = currNode->next;
      currentNode->next = NULL; //make sure inserted_node->next is NULL
      if (i < k) { //create k sublists and add their first node
	List* newList = malloc(sizeof(List));
	if (newList == NULL){ //malloc failed
	  currList = lists;
	  List* nextList;
	  Node* first = lists->node;
	  currentNode->next = currNode;
	  first->next = currentNode;
	  while (currList != NULL){
	    nextList = currList->next;
	    free(currList);
	    currList = nextList;
	  }
	  return first;
	}
	newList->next = NULL;
	newList->node = currentNode;
	currList->next = newList;
	if (i == (k - 1)){
	  newList->next = lists;
	  currList = currList->next;
	}
      }
      else {
	Node* curr = currList->node;
	*n_comp += 1; //comp
	if (currentNode->value > curr->value){ //first node swap
	  currList->node = currentNode;
	  currentNode->next = curr;
	}
	else { //2+ descending order insertions 
	  Node* prev;
	  do {
	    prev = curr;
	    curr = curr->next;
	    *n_comp += 1; //comp
	  } while ((curr != NULL) && (curr->value > currentNode->value));
	  prev->next = currentNode;
	  currentNode->next = curr;
	}
      }
      currList = currList->next;
    }
    currList = lists;
    for (int i = 0; i < k; i++){ //use a stack to reverse sorted order
      Node* curr = currList->node;
      Node* stack = NULL;
      while (curr != NULL){ //push onto stack
	if (stack == NULL){
	  stack = curr;
	  curr = curr->next;
	  stack->next = NULL;
	}
	else {
	  Node* t = curr;
	  curr = curr->next;
	  t->next = stack;
	  stack = t;
	}
      }
      currList->node = stack;
      currList = currList->next;
    }
    Node* prevNode = lists->node;
    currList = lists->next;
    lists->node = (lists->node)->next;
    Node* final = prevNode;
    for (int i = 1; i < size; i++){ //recreate list of nodes
      Node* curr = currList->node;
      prevNode->next = curr;
      currList->node = (currList->node)->next;
      List* nextList = currList->next;
      if (currList->node == NULL) //sublist empty
	free(currList);
      currList = nextList;
      prevNode = prevNode->next;
    }
    currNode = final;
  }
  Node* ret = currNode;
  int sorted = 0;
  while (!sorted){ //bubble sort finish
    sorted = 1;
    *n_comp += 1; //comp
    if (currNode->value > (currNode->next)->value){ //swap first two nodes
      Node* temp = currNode->next;
      currNode->next = temp->next;
      temp->next = currNode;
      ret = temp;
      sorted = 0;
    }
    Node* previous = ret;
    currNode = ret->next;
    for (int i = 1; i < (size - 1); i++){
      Node* nextNode = currNode->next;
      *n_comp += 1; //comp
      if (currNode->value > nextNode->value){
	Node* temp = nextNode->next;
	currNode->next = temp;
	nextNode->next = currNode;
	previous->next = nextNode;
	sorted = 0;
      }
      previous = previous->next;
      currNode = previous->next;
    }
    if (!sorted)
      currNode = ret;
  }
  return ret;
}
