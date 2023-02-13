#include <stdio.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* This function creates three processes whose ids must be printed in a file following a specific order */
void callForks(int inputorder[3],char filename[]){
    // <YOUR CODE HERE>
	
	FILE *textfile;
	textfile = fopen(filename,"a");
	

	//printf("%i \n",getpid());
	for(int i = 1; i<4 ; i++){
		int delay;
		for (int k = 0; k<3 ; k++){
			if (inputorder[k] == i)
				delay = k; 
		}
		int child = fork();
    		if (child == 0){
    			
    			sleep(delay);
    			
    			fprintf(textfile, "%i %i\n", getpid(), getppid());    			
    			
    			exit(0);
    		}
    	
	}
    	while (wait(0)>0); // parent must wait to exit after all its children are terminated (must wait for the slower kid)
    	fclose(textfile);
    	return;
}

void main(){
	int inputorder[3] = {3,2,1};
	char filename[] = "processes.txt"; 
	callForks(inputorder,filename);
	return;
}

