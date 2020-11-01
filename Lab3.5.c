#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
	void sigint_handler(int sig);
	int num,buffer,pipefds[2];
	int flag =0;

	if(signal(SIGINT, sigint_handler) == SIG_ERR)
	{

	   perror("signal");
	   exit(1);
	}

	pipe(pipefds);
	pid_t pid = fork();

	if(pid == 0) 
	{
		close(pipefds[0]);
		printf("Please enter a number:");
		scanf("%d",&num);
		write(pipefds[1], &num, sizeof(num));
		printf("Number receive and sending to parent\n");
		exit(EXIT_SUCCESS);
	}

	else if(pid > 0 )
	{
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0],&buffer, sizeof(int));
		close(pipefds[0]);

		for(int i=2;i<=buffer/2;i++)
		{
			
			if(buffer%i==0)
			{
			  flag=1;
			  break;
			}
		}

		if(buffer==1)
		{
		  printf("1 is not prime number\n");
		}
		else{
		    if(flag ==0)
		      printf("%d is a prime number\n", buffer);
		    else
		      printf("%d is a not prime number\n", buffer);
		}
		return 0;
	}

	return EXIT_SUCCESS;
}

void sigint_handler(int sig)
{
	printf("Continue\n");
}
