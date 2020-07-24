#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "global.h"
#include "darray.h"
#include "sorting.h"


// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}


struct darray* initialize_set (int size)
{

  struct darray* arr = malloc(sizeof(struct darray));
  check(arr);
  arr->cells = (Value_Type*) (malloc(sizeof(Value_Type)*size));
  check(arr->cells);
  arr->capacity = size;
  arr->size = 0;
  arr->sorted = false;
  arr->resizes = 0;
  return arr;
}

void tidy(struct darray* arr)
{
  if(arr){
    // free memory created by strdup
    for(unsigned i=0; i<arr->size;i++){ free(arr->cells[i]); }
    // free array and struct
    free(arr->cells);
    free(arr);
  }
}

int size(struct darray* arr){ return arr->size; }

struct darray* insert (Value_Type value, struct darray* arr)
{
  // If we have reached capacity, double size and copy
  if(arr->size >= arr->capacity){
    struct darray* new_arr = initialize_set(arr->capacity*2);
    for(unsigned int i=0;i<arr->size;i++){
      new_arr->cells[i] = arr->cells[i];
    }
    new_arr->size = arr->size;
    new_arr->resizes = arr->resizes+1;
    free(arr->cells);
    free(arr);
    arr = new_arr;
  }

  arr->cells[arr->size] = strdup(value);
  arr->size++;

  // changing the array means it may no longer be sorted
  arr->sorted = false;

  return arr;
}

bool find (Value_Type value, struct darray* arr)
{
	//size_t is an unsigned integreal type reccomded for variables
	//tthat represent an arrays size
  int size = arr->size;
	//as reference i have used the c how to programme book 7th edition
	//hard copy from the library
  if(mode == LINEAR_SEARCH){
		//linear search sequentially iterates over the array and
		//once desired element is found prints out this element
		//and its index - else return false.

    int i;
		for(i = 0; i < size; i++)
		{
			Value_Type thisOne = arr->cells[i];
			if(compare(thisOne, value) == 0)
			{
				// printf("element found at index %d\n", i );
				return true;
			}
		}
    //TODO implement linear search through arr->cells
  }
  else{ // Binary Search
    if(!arr->sorted){
      if(verbose > 0){
        printf("Dynamic Array not sorted, sorting...\n");
      }
      sort(arr,mode);
			// printf("\n");
			print_set(arr);

      if(verbose > 0){
        printf("Dynamic Array sorted\n");
      }
      arr->sorted = true;
    }
    //TODO implement binary search through arr->cells

		//element to store the low value - type size_t
		int bottom = 0;
		int top = size - 1;

		//variable to store the middle variable
		int middle;

		//the loop should continue until the low pointer has 'overlapped'
		//the high pointer - elemnt is not present
		while(bottom <= top)
		{
			//define middle
			middle = (bottom + top) / 2;

			Value_Type thatOne = arr->cells[middle];
			// printf("%d\n", compare(thatOne, value));
			// printf("%s\n", thatOne );
			if(compare(thatOne, value) == 0)
			{
				// printf("element found at index %d\n", middle );
				return true;
			}

			//if the value is less than middle we chop the array to the lower half
			else if(compare(thatOne, value) > 0)
			{
				// printf("array chopped lower\n");
				top = middle - 1;
			}

			//if value is greater than middle
			else
			{
				// printf("array chopped higher\n");
				bottom = middle + 1;
			}
		}

  }
  // To supress warning, default return value
  return false;
}

// You can make any changes you want to this function
void print_set (struct darray* arr)
{
  printf("DArray:\n");
  for(unsigned i=0;i<arr->size;i++){
    printf("\t%s\n",arr->cells[i]);
  }
}

// You can make any changes you want to this function
void print_stats (struct darray* arr)
{
  printf("Dynamic array of capacity %d contains %d elements\n",arr->capacity,arr->size);
  printf("Dynamic array was resized %d times\n",arr->resizes);
}
