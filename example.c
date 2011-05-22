#include <stdio.h>
#include "trymap.h"
#define TRYMAP_H
#define STDIO_H

int int_indexer(void *my_int){
  int *my_real_int = (int *)my_int;

  if(*my_real_int == 0)
    return TRY_END_INDEX;

  int ret = *my_real_int % 10;
  *my_real_int /= 10;
  return ret;
}
int main(){
  trynode *mytry = init_trymap(&int_indexer, 10);
  char hello[] = "hello!!";
  int blah = 17;
  iput_try(mytry,&blah,(void *)hello);
  printf("num elts in mytry: %d\n", size_try(mytry));

  int blah2 = 23;
  char hello2[] = "goodbye!";
  iput_try(mytry,&blah2,(void *)hello2);
  printf("added another, now we have %d elts\n", size_try(mytry));

  blah = 17;
  char *ret = (char *)iget_try(mytry, &blah);
  printf("found: %s\n", ret);

  blah2 = 23;
  ret = (char *)iget_try(mytry, &blah2);
  printf("also found: %s\n", ret);

  free_try(mytry);
}
