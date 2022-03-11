#include "week_05.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>  

void problem01(){
   int a=3,pid;
   printf ("Hi\n");
   pid=fork();  
   printf ("Bye\n");
   
}

void problem02 () {
	int x=0,pid;
	pid=fork (); /*Child process is created */
	if (pid == 0){ 
		printf ("I am the son\n"); /* Written by the child on the screen*/
		printf ("By daddy; x=%d, pid=%d ppid=%d\n",x,getpid(), getppid()); 
	}
	else { 
		/* without sleep () parent could ends before the child, 
		 * it will show that the new parent of the child is process 1 (init). 
		 * That is because, when the parent dies, init adopts the child so that it does not become a zombie.
*/
		sleep(1);
		printf ("I am the father\n"); /* Written by the parent on the screen*/
		printf ("Hasta la vista Baby; x=%d, pid=%d ppid=%d\n",x,getpid(), getppid()); 
  }

  }


 void problem03 (){
	printf ("Hi\n");
	fork ();
	printf ("One\n");
	fork ();
	printf ("Two pid=%d\n",getpid());
}

 void problem04 (){
	int i,pid;
	for (i=1; i<=2; i++){
		pid = fork();
		if ( pid==0) {
			printf ("I am the child %d\n", i);
			exit(0); 
		}
	}
}

int problem05a(int argc, char *argv[]){
	int pid;
	
	if (argc < 2){
		printf("Usage: exec-command <command>\n");
		exit(-1);
	}
	
	pid=fork();
	if(pid==0){ //create a child
        printf ("Child created, is going to execute the command\n");
       // Execute command
        execvp (argv[1], &argv[1]);
        printf ("ERROR, this line is online executed if the execvp call fail\n");
	}
	
	wait(NULL);
	printf ("end parent process\n");
  
	exit(0);
 } //close main

int problem05b(int argc, char *argv[]){
	int pid;
	char file[80];

	if (argc < 2){
		printf("Usage: exec-command <command>\n");
		exit(-1);
	}
	
	pid=fork();
	if(pid==0){ //create a child
        printf ("Child created, is going to execute the command\n");
		// output redirection
        close(STDOUT_FILENO);
		sprintf(file, "out-%s.txt",argv[1]);
        open(file,O_RDWR|O_CREAT,0660);
       // Execute command
        execvp (argv[1], &argv[1]);
        printf ("ERROR, this line is online executed if the execvp call fail\n");
	}
	
	wait(NULL);
	printf ("end parent process\n");
  
	exit(0);
 } //close main

int problem06a (){
	int i,pid;
 
	for (i=0; i<5; i++){
		pid=fork ();
		if ( pid==0){
			printf ("Child %d ( pid=%d)\n",i+1,getpid());
		exit (0); //return(0);
    }
		else; 
		// parent process has nothing more to do
  }	
  
	sleep(10);

    // to see zombies process execute ps -el | grep 'Z'
    

    // The parent ends without waiting for their child that become horphan (zombies)
    return 0;

    /* If the parent process die having zombies in the process table, they will be addopted by init,
	 * init will execute periodically the call wait() to eliminate zombie process that it has addopted
	 */
}



int problem06b (){
	int i,j,pid;
	
	for (i=1; i<=NUM_CHILD; i++){
		
		pid=fork ();  //parent process create child process
		
		if ( pid==0){
			
			printf ("Child %d ( pid=%d)\n",i,getpid());
			
			for (j=1; j<=NUM_GRAND_SON; j++){
				
				pid=fork ();  //child process create 'grandson' process
				
				if (pid==0){
					printf (" Grandson %d ( pid=%d) from child %d (pid=%d)\n", j,getpid(),i,getppid());
					exit (0);  // grandson finish
				}
			}
			
			for (j=1; j<=NUM_GRAND_SON; j++){  // Child processes wait wait their child (grandsons) until they finish
				wait (NULL);			
			}
			
			exit (0); //child exit
		} // end if childs
		
	} //end creating childs 
  
  for (i=1; i<=NUM_CHILD; i++){  //The parent wait their child until they finish
  
     wait (NULL);
  }
  
   exit (0); //parent exit
  }
   