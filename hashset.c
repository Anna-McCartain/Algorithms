#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "global.h"
#include "hashset.h"

//global variable for collisions
int collisionTotal = 0;

// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}

// Helper functions for finding prime numbers
bool isPrime (int n)
{
  for (int i = 2; i*i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
}

int nextPrime(int n)
{
  for (; !isPrime(n); n++);
  return n;
}

// Your code


struct hashset* initialize_set (int size)
{
  printf("initalise!!!!\n");
  //based off the structure for initialzing darray given
  struct hashset* set = malloc(sizeof(struct hashset));
  if(!set)
  {
    printf("Memory allocation failed\n");
    exit(0);
  }
  // check(set);
  set->cells = (cell*) (malloc(sizeof(cell)*nextPrime(size)));
  // check(set->cells);
  if(!set->cells)
  {
    printf("Memory allocation failed\n");
    exit(0);
  }
  set->size = nextPrime(size);
  set->num_entries = 0;

  //set all elements state to empty and elements to null
  int i;
  for(i = 0; i < set->size; i++)
  {
    set->cells[i].state = empty;
    set->cells[i].element = NULL;
  }
  printf("initalise done!!!!\n");

  return set;

}



void tidy(struct hashset* set)
{
  if(set)
  {
    int j;
    for(j = 0; j < set->size; j++)
    {
      if(set->cells[j].state == in_use)
        free(set->cells[j].element);
    }
    free(set->cells);
    free(set);
  }
}

int size(struct hashset* set){
  return set->num_entries;
}


int hashKeyA(Value_Type value)
{
  //first method is using the acii value of the code - we find the total then
  //mod it using how many characters there were.
  int characterCount = 0;
  int asciiTotal = 0;

  //convert to string

  char *value2String = value;

  sscanf(value, "%s", value2String);

  while(*value2String)
  {
    int thisValue = (int)*value2String;
    value2String++;
    characterCount++;
    asciiTotal += thisValue;
  }

  int keyA = asciiTotal % characterCount;

  return keyA;
}


int powerMethod(int value, int power)
{
  if(power == 0)
    return 1;
  if(power == 1)
    return value;
  if(power > 1)
  {
    int multiply;
    int multiplyTotal = value;
    for(multiply = 2; multiply < power; multiply++)
      multiplyTotal *= value;
    return multiplyTotal;
  }
}

int hashKeyB(Value_Type value)
{
  //second method using the power method as discussed in lectures - we take the
  //ascii code and multiply by itself by the positin in the string. (weighted)
  int characterCount = 0;
  int asciiTotal = 0;

  //convert to string
  char *value2String = value;
  sscanf(value, "%s", value2String);
  while(*value2String)
  {
    int thisValue = (int)*value2String;
    thisValue = powerMethod(thisValue, characterCount);
    value2String++;
    characterCount++;
    asciiTotal += thisValue;
  }

  int keyB = asciiTotal % characterCount;
  return keyB;
}

struct hashset* resizing (struct hashset* set)
{
  printf("RESIZING...");
  //get old size
  int oldsize = set->size;
  int newsize = oldsize * 2;
  struct hashset* newSet = initialize_set(newsize);
  int i;
  for(i = 0; i <= set->size; i++)
  {
    if(set->cells[i].state == in_use)
    {
      Value_Type value = set->cells[i].element;
      insert(value, newSet);
    }
  }
  tidy(set);
  printf("RESIZED TO %d\n", newSet->size);
  return newSet;

}
struct hashset* insert (Value_Type value, struct hashset* set)
{
  printf("INSERT: %s\n", value);
  if(set->num_entries > set->size)
  {
    printf("No Room left in Hash Set \n");
    set = resizing(set);
  }

  int key;

  //key dependant on the mode chosen
  if(mode == HASH_1_LINEAR_PROBING)
    key = hashKeyA(value);
  else
    key = hashKeyB(value);

  //if cells is empty - filil with value
  if(set->cells[key].state == empty)
  {
    set->cells[key].element = strdup(value);
    set->cells[key].state = in_use;
    set->num_entries++;
    printf("value %s easy inserted done at position %d!!!\n", value, key);
    return set;
  }

  if(set->cells[key].state == in_use)
  {
    //check if the values are the same - if so do not add to the hashmap
    if(strcmp(value, set->cells[key].element) == 0)
      return set;

    //if they are different - use linear probing to go along the set and find
    //next available space
    collisionTotal++;

    while(set->cells[key].state == in_use)
    {
      key++;
      if(key >= set->size)
      {
        printf("element could not be inserted...");
        set = resizing(set);
      }
    }

      set->cells[key].element = strdup(value);
      set->cells[key].state = in_use;
      set->num_entries++;
      printf("value %s linear inserted done at position %d!!!\n", value, key);
      return set;
    }
  } //if


bool find (Value_Type value, struct hashset* set)
{
  printf("FIND %s\n", value);

  int key;
  //method very similar to insert see above.
  //key dependant on the mode chosen
  if(mode == HASH_1_LINEAR_PROBING)
    key = hashKeyA(value);
  else
    key = hashKeyB(value);

  if(strcmp(value, set->cells[key].element) == 0)
  {
    printf("value, %s, found at position, %d\n", value, key);
    return true;
  }

  //else cycle thorugh the elements after this and find see if it is present.
  else
  {
    while(key != set->size)
    {
      if(set->cells[key].state != empty)
      {
        if(strcmp(value, set->cells[key].element) == 0)
        {
          printf("value, %s, found at position, %d\n", value, key);
          return true;
        }
      }

      key++;
    }

    printf("key size = %d size = %d \n", key, set->size);
    printf("value, %s, NOT FOUND\n", value);
    return false;
  }
}

void print_set (struct hashset* set)
{
  printf("PRINT SET \n");
  int i;
  for(i = 0; i < size(set); i++)
  {
    if(set->cells[i].state == in_use)
    {
      printf("element at position %d is %s\n", i, set->cells[i].element);
    }
  }
}

void print_stats (struct hashset* set)
{
  printf("PRINT STATS \n");
  printf("Total number of cells is %d\n", set->size);
  printf("Total number of used cells is %d\n", size(set));
  printf("Total number of collions on insertion are %d\n", collisionTotal);
  tidy(set);
}

