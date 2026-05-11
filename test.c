#include <stdio.h>
#include <stdlib.h>

int main() {
  char *name = malloc(sizeof(char));
  printf(":");
  scanf("%s", name);
  printf("%s\n", name);
}
