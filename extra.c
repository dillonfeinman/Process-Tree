#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char * argv[]){
  printf("Child PID: %d\nParent PID: %d\n", getpid(), getppid());
  int i = wait(NULL);
  return 0;
}
