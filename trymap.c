#include "trymap.h"
#include <stdio.h>
#include <stdlib.h>

// just to avoid including strings.h, even though they might have a more
// efficent version.
void my_bzero(void *array, size_t size)
{
  char *cur = (char *)array;
  for(int i = 0; i < size; i++)
    *(cur++) = (char)0;
}

trynode *init_trymap(int (*indexer)(void *), int n_children)
{
  trynode *root	  = (trynode *)malloc(sizeof(trynode));
  root->payload	  = NULL;
  root->nchildren = n_children;
  root->children  = (trynode **)malloc(n_children * sizeof(trynode *));
  root->nbelow	  = 0;
  root->get_index = indexer;
  root->cur_i	  = 0;

  for(int i = 0; i < root->nchildren; i++)
    root->children[i] = NULL;

  return root;
}

trynode *newchild_try(trynode *root, int child_index)
{
  trynode *child    = (trynode *)malloc(sizeof(trynode));
  child->payload    = NULL;
  child->nchildren  = root->nchildren;
  child->children   = (trynode **)malloc(root->nchildren * sizeof(trynode *));
  child->nbelow	    = 0;
  child->get_index  = root->get_index;
  child->cur_i	    = 0;
  root->children[child_index] = child;

  for(int i = 0; i < root->nchildren; i++)
    child->children[i] = NULL;

  return child;
}

int free_try(trynode *root)
{
  if(root == NULL)
    return 0;

  for(int i = 0; i < root->nchildren; i++){
    free_try(root->children[i]);
  }
  free(root->children);
  free(root);
  return 0;
}

int put_try(trynode *root, void *key, void *val)
{
  int next_index = root->get_index(key);
  if(next_index == TRY_END_INDEX){
    int nadded = (root->payload) ? 0 : 1;
    root->nbelow += nadded;
    root->payload = val;
    return nadded;
  }

  if(root->children[next_index] == NULL)
    newchild_try(root,next_index);

  int nadded = put_try(root->children[next_index], key, val);
  root->nbelow += nadded;
  return nadded;
}
int sput_try(trynode *root, char *key, void *val)
{
  return put_try(root, (void *)key, val);
}
int iput_try(trynode *root, int *key, void *val)
{
  return put_try(root, (void *)key, val);
}

void *get_try(trynode *root, void *key)
{
  int next_index = root->get_index(key);
  if(next_index == TRY_END_INDEX)
    return root->payload;

  if(root->children[next_index])
    return get_try(root->children[next_index], key);

  return NULL;
}
void *sget_try(trynode *root, char *key)
{
  return get_try(root, (void *)key);
}
void *iget_try(trynode *root, int *key)
{
  return get_try(root, (void *)key);
}

int size_try(trynode *root)
{
  return root->nbelow;
}

int traverse_from_0(trynode *root)
{
  fprintf(stderr, "traverse_from_0 UNIMPLEMENTED\n");
  return 0;
}
