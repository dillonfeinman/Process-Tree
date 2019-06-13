#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
 for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-u") == 0){
      fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\nAlso, cannot call both -p and -s at the same time.\n");
      exit(0);
    }
  }
  int num_levels = 1;
  int num_children = 1;
  int paused = 0;
  int sleeptime = -1;
  int sleeping = 1;
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      if(strcmp(argv[i], "-N") == 0){
        if(i+1<argc){
          num_levels = atoi(argv[i+1]);
        }
        if(num_levels < 0){
          fprintf(stderr, "Negative number. Exiting.\n");
          exit(0);
        } else if(num_levels == 0){
  	      fprintf(stderr, "Cannot be 0 or a nonnumber. Exiting.\n");
          exit(0);
        }
      }
      else if(strcmp(argv[i], "-M") == 0){
        if(i+1<argc){
          num_children = atoi(argv[i+1]);
        }
      }
      else if(strcmp(argv[i], "-p") == 0){
        paused = 1;
        sleeping = 0;

      }
      else if(strcmp(argv[i], "-s") == 0){
        if(i+1<argc){
          sleeptime = atoi(argv[i+1]);
        }
        sleeping = 1;
      }
      else {
        fprintf(stderr, "This is an unrecognized command.");
        fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\nAlso, cannot call both -p and -s at the same time.\n");
        exit(0);
      }
    }
  }
  if(num_levels > 4){
    fprintf(stderr, "Cannot have more than four levels.\n");
    exit(1);
  }
  if(num_children > 3){
    fprintf(stderr, "Cannot have more than 3 children.\n");
    exit(1);
  }
  if(sleeptime != -1 && paused == 1){
    fprintf(stderr, "Cannot call both -s and -p at the same time.\n");
    exit(1);
  } else if (sleeptime <= 0 && sleeptime != -1){
    fprintf(stderr, "Sleep time cannot be 0 or negative.\n");
    exit(1);
  } else if (sleeptime == -1){
    sleeptime = 1;
  }
  printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());
  pid_t pid1 = getpid();
  if(num_levels > 1){
	 pid_t pid2;
   for(int i = 0; i < num_children; i++){
     if(pid1 == getpid()){
       pid2 = fork();
     }
   }
   if(pid2 < 0){
     fprintf(stderr, "Fork failed.");
 	 	 return 1;
   }
	 if (pid2 == 0) { /* child process */
     num_levels = num_levels - 1;
     char childstr[2] = {num_children + '0'};
     char levelstr[2] = {num_levels + '0'};
     char sleepstr[8] = {sleeptime + '0'};
     if(paused == 1){
       char * args2[] = {"./prog2tree", "-N", levelstr, "-M", childstr, "-p", NULL};
  	   execv("prog2tree", args2);
       num_levels = num_levels + 1;
     } else {
       char * args2[] = {"./prog2tree", "-N", levelstr, "-M", childstr, "-s", sleepstr, NULL};
  	   execv("prog2tree", args2);
       num_levels = num_levels + 1;
     }
   }
   else { /* parent process */
	 	/* parent will wait for the child to complete */
      for(int i = 0; i < num_levels * num_children; i++){
        wait(NULL);
       }
    }

  } else if(sleeping == 1){
    sleep(sleeptime);
  } else {
    pause();
  }
  printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());
  return 0;
}
