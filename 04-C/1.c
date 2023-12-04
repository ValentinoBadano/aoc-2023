#include <stdio.h>
#include <string.h>

char str[1000];

int main() {
  FILE *f;
  char filename[] = "../input.txt";
  f = fopen(filename, "r"); 
  
  while(fgets(str, 100, f)) {
    printf("%s", str);
  }
  fclose(f);
}
