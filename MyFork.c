#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char name[99];
void childTask(){
	printf("Please Enter Your Name :\n");
	scanf("%99s", name);
	printf("Name : %s\n\n", name);
}

void parentTask(){
	printf("Job is done\n");
}

int main(void){
	for(int j=1; j<5; j++){
		pid_t pid = fork();

		if(pid==0){
			childTask();
			exit(EXIT_SUCCESS);
		}
		else{
			wait(NULL);
		}
	}
	parentTask();
	return EXIT_SUCCESS;
}
