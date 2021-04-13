#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main () {
	char buf[1024];
	
	int pipe12[2];
	pid_t pid12;
	
	int pipe23[2];
	pid_t pid23;
	
	int pipe34[2];
	pid_t pid34;
	
	int pipe45[2];
	pid_t pid45;
	
	int pipe51[2];
	pid_t pid51;
	
	int arr[2];
	
	// Create pipe12
	if(pipe(pipe12) < 0) {
		perror("pipe error");
	}
	// Create fork12
	if((pid12 = fork()) < 0) {
		perror("fork error");
	}
	 
	// Process 1 to 2
	if(pid12 > 0) {// Parent process
		close(pipe12[0]);
		printf("%d : first", getpid());
		
		// Create pipe23
		if(pipe(pipe23) < 0) {
			perror("pipe error");
		}
		// Create fork23
		if((pid23 = fork()) < 0) {
			perror("fork error");
		}
		
		// Process 2 to 3
		if(pid23 > 0) {// Parent process
			close(pipe23[0]);
			printf("%d : second", getpid());
			
			// Create pipe34
			if(pipe(pipe34) < 0) {
				perror("pipe error");
			}
			// Create fork34
			if((pid34 = fork()) < 0) {
				perror("fork error");
			}
			
			// Process 3 to 4
			if(pid34 > 0) {// Parent process
				close(pipe34[0]);
				printf("%d : third", getpid());
				
				// Create pipe45
				if(pipe(pipe45) < 0) {
					perror("pipe error");
				}
				// Create fork45
				if((pid45 = fork()) < 0) {
					perror("fork error");
				}
				
				// Process 4 to 5
				if(pid45 > 0) {// Parent process
					close(pipe45[0]);
					printf("%d : fourth", getpid());
				}
				else {// Child process
					close(pipe45[1]);
					read(pipe45[0], buf, 1024);
					printf("%s\n", buf);
					memset(buf, 0, sizeof(buf));
					//exit(1);
				}
			}
			else {// Child process
				close(pipe34[1]);
				read(pipe34[0], buf, 1024);
				printf("%s\n", buf);
				memset(buf, 0, sizeof(buf));
				//exit(1);
			}
		}
		else {// Child process
			close(pipe23[1]);
			read(pipe23[0], buf, 1024);
			printf("%s\n", buf);
			memset(buf, 0, sizeof(buf));
			//exit(1);
		}
	}
	else {// Child process
		close(pipe12[1]);
		//exit(1);
	}
	
	
	// Create pipe51
	if(pipe(pipe51) < 0) {
		perror("pipe error");
	}
	// Create fork51
	if((pid51 = fork()) < 0) {
		perror("fork error");
	}
	
	// Process 5 to 1
	if(pid51 > 0) {// Parent process
		close(pipe51[1]);
	}
	else {// Child process
		close(pipe51[0]);
		printf("%d : fourth", getpid());
		//exit(1);	
	}
	
	
	
	return 0;
}
