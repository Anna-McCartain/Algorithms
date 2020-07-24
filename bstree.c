#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "global.h"
#include "bstree.h"

//2 variables to find the avergae number of comparions
int comparisons = 0;
int found = 0;

// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}


struct bstree* initialize_set (int size)
{
  // An empty tree is represented by NULL
  return NULL;
}

void tidy(struct bstree* tree)
{
  if(tree){
    tidy(tree->left);
    tidy(tree->right);
    // assumes tree owns value memory
    free(tree->value);
    free(tree);
  }
}

int size(struct bstree* tree){
  if(tree){
    return 1 + size(tree->left) + size(tree->right);
  }
  return 0;
}

struct bstree* insert (Value_Type value, struct bstree* tree)
{

	//if tree is not null, hence tree has children, insert it in the correct position
	//in the tree
	//i used the c how to program book for reference
  if(tree){
    //if the value to be inserted is less than the value of the node in the tree
		//insert it into the ledt sub tree.
		if(compare(value, tree->value) < 0)
		{
			tree->left = insert(value, tree->left);
			tree->height++;
		}

		//if the value is greater than, insert into right tree
		if(compare(value, tree->value) > 0)
		{
			tree->right = insert(value, tree->right);
			tree->height++;
		}

		//if the value is a duplicate, dont insert it
		if(compare(value, tree->value ) == 0)
		{
			return tree;
		}
  }

  else
	{
  	//if tree is null hence we are at a leaf node, we need to expand the tree
		//by allocating more memory for the tree and inserting the nodes in.

		tree = (struct bstree*) malloc (sizeof(struct bstree));

		//check if memory was allocated
		if(tree)
		{
	    // strdup, it basically returns a pointer to the dupilcated value,
			tree->value = strdup(value);
			tree->left = initialize_set(0);
			tree->right = initialize_set(0);
			tree->height = 0;
		}

		else
		{
			printf("%s cant be inserted as memory could not be allocated.\n", value);
		}

  }
  return tree;
}

bool find (Value_Type value, struct bstree* tree)
{
	//in my find function each layer down the tree can either have 1 2 or 3
	//comparisons. i will find the number of comparions.
  if(tree)
	{
		//if the value is found, return true
		comparisons++;
		if(compare(value, tree->value ) == 0  )
		{
			found++;
			// printf("Value %s  found\n", value );
			return true;
		}
		//if the value to be found is less than the value of the node in the tree
		//go down into the ledt sub tree.
		comparisons++;
		if(compare(value, tree->value) < 0)
		{
			bool foundLeft = find(value, tree->left);
			if(foundLeft)
				return true;
		}

		//if the value is greater than, go down into right tree
		comparisons++;
		if(compare(value, tree->value) > 0)
		{
			bool foundRight = find(value, tree->right);
			if(foundRight)
				return true;
		}

	}

	// printf("Value %s not found\n", value );
  // if tree is NULL then it contains no values
  return false;
}


// You can update this if you want
void print_set_recursive(struct bstree* tree, int depth)
{
  if(tree){
    for(unsigned i=0;i<depth;i++){ printf(" "); }
    printf("%s\n",tree->value);
    print_set_recursive(tree->left,depth+1);
    print_set_recursive(tree->right,depth+1);
  }
}
// You can update this if you want
void print_set (struct bstree* tree)
{
 printf("Tree:\n");
 print_set_recursive(tree,0);
}

void print_stats (struct bstree* tree)
{
	// print_set(tree);
 printf("Size of tree: %d\n", size(tree));
 printf("Height of tree: %d\n", tree->height);
 // printf("Comparisons = %d\n", comparisons);
 // printf("Found = %d\n", found);
 int average_comparisons = comparisons / found;
 printf("Average number of comparisons: %d\n", average_comparisons);

}
