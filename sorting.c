
#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"

void sort(struct darray* arr, int select){

  switch(select){
    case BINARY_SEARCH_ONE   : insertion_sort(arr); break;
    case BINARY_SEARCH_TWO   : quick_sort(arr, 0, arr->size - 1); break;
    case BINARY_SEARCH_THREE :
    case BINARY_SEARCH_FOUR  :
    case BINARY_SEARCH_FIVE  :  // Add your own choices here
    default:
      fprintf(stderr,
              "The value %d is not supported in sorting.c\n",
              select);
      // Keep this exit code as the tests treat 23 specially
      exit(23);
  }
}


// You may find this helpful
void swap(char* *a, char* *b)
{
        char* temp = *a;
        *a = *b;
        *b = temp;
}


void insertion_sort(struct darray* arr){
 //make a new array same size as input array
 // size_t size = (sizeof(arr) / sizeof(arr[0]));
  Value_Type insertionArray[arr->size];

 //initalise array with first element
 insertionArray[0] = arr->cells[0];

 //int to add all the elements into the new array
 int i;
 for(i = 1; i < arr->size; i++)
 {
	 //add new elemnt to back of array
	 insertionArray[i] = arr->cells[i];
	 //2 ints to sort each new element added to new array
	 int a;
	 int b = i - 1;

	 for(a = i; a > 0; a--)
	 {
		 //if elements are in wrong order swap them
		 if(compare(insertionArray[a], insertionArray[b]) < 0)
		 {
		   swap(&insertionArray[a], &insertionArray[b]);
		 } //if

		 b--;
	 } //for


 } //for

	for (int index = 0; index < arr->size; index++)
	{
		printf("%s\n", insertionArray[index]);
		// free(arr->cells[index]);
		arr->cells[index] = insertionArray[index];
	}
} //insertion

int sortingQuick(Value_Type* arr, int frontIndex, int backIndex)
{

  //pivot will be elemet zero, we also will assign 2 pointers, one as the end
  //of array one at the beginning.
  int pivot = frontIndex;


  // printf("%s, %s, \n", quickArray[pivot], quickArray[pivot + 1]);
  //we take element 1 of the array, compare it with the pivot, if it is greater
  //we swap it with elemnet at back index, if less we swap it with element at
  //front index. we always compare with element at index 1. a counter will be
  //used to check that all the elements in the array have been sorted.
  while(backIndex != pivot)
  {
    if(compare(arr[pivot], arr[pivot + 1]) < 0)
    {
      swap(&arr[pivot + 1], &arr[backIndex]);
      backIndex--;
    }

    if(compare(arr[pivot], arr[pivot + 1]) > 0)
    {
      swap(&arr[pivot], &arr[pivot + 1]);
      pivot++;
    }
  }

  return pivot;
}
// Hint: you probably want to define a helper function for the recursive call
void quick_sort(struct darray* arr, int frontIndex, int backIndex) {

// printf(" front index %d\n", frontIndex );
// printf("back index %d\n", backIndex);
// print_set(arr);

if(frontIndex < backIndex)
{
int pivot = (sortingQuick(arr->cells, frontIndex, backIndex));
// printf("pivot %d\n", pivot);
// print_set(arr);

//sort the front side of array
quick_sort(arr, frontIndex, pivot - 1);
//sort the back side of quickArray
quick_sort(arr, pivot + 1, backIndex);

}
}
