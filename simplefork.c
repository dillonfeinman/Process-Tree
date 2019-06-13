#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
 for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-u") == 0){
      fprintf(stderr, "Usage string\n");
      exit(0);
    }
  }
  int num_levels = 1;
  int num_children = 1;
  int paused = 0;
  int sleep = -1;
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-N") == 0){
      if(i+1<argc){
        num_levels = argv[i+1];
      }
      if(num_levels < 0){
        fprintf(stderr, "Negative number. Exiting.\n");
        exit(0);
      } else if(num_levels == 0){
	      fprintf(stderr, "Cannot be 0 or a nonnumber. Exiting.\n");
        exit(0);
      }
    }
    if(strcmp(argv[i], "-M") == 0){
      if(i+1<argc){
        num_children = argv[i+1]
      }
    }
    if(strcmp(argv[i], "-p") == 0){
      paused = 1;

    }
    if(strcmp(argv[i], "-s") == 0){
      if(i+1<argc){
        sleep = argv[i+1];
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
  if(sleep != -1 && paused == 1){
    fprintf(stderr, "Cannot call both -s and -p at the same time.\n");
    exit(1);
  } else if (sleep == -1){
    sleep = 1;
  }
  printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());
  pid_t pid1 = getpid();
  if(num_levels > 1){
	 pid_t pid2; /* for a child process */
   for(int i = 0; i < num_children; i++){
     if(pid1 == getpid()){
       pid1 = fork();
     }
   }
   if(pid1 < 0){  /* error */
     fprintf(stderr, "Fork failed.");
 	 	 return 1;
   }
	 if (pid1 == 0) { /* child process */
     num_levels = num_levels - 1;
     char levelstr = num_levels + '0';
     char childstr = num_children + '0';
     char sleepstr = sleep + '0';
     if(pasued == 1){
       char * args2[] = {"./prog2tree", "-N", levelstr, "-M", childstr, "-p"};
       num_levels = num_levels + 1;
  	   execlp("/Users/dillonfeinman/Desktop/Bollege/Spring\ 2019/CS350/Assignment2/prog2tree", "./prog2tree", NULL);
     } else {
       char * args2[] = {"./prog2tree", "-N", levelstr, "-M", childstr, "-s", sleepstr};
       num_levels = num_levels + 1;
  	   execlp("/Users/dillonfeinman/Desktop/Bollege/Spring\ 2019/CS350/Assignment2/prog2tree", "./prog2tree", NULL);

     }
   }
   else { /* parent process */
	 	/* parent will wait for the child to complete */
      for(int i = 0; i < num_levels; i++){
        wait(NULL);
  	 	  printf("Child Complete.\n");
       }
    }

  } else if(sleep != -1){
    sleep(sleep);
  } else {
    pause();
  }
  printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());
  return 0;
}
