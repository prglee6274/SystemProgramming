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
	
	int pipe51[2];
	pid_t pid51;
	
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
		strcpy(buf, "1 to 2");
		write(pipe12[1], buf, strlen(buf));
		
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
			strcpy(buf, "2 to 3");
			write(pipe23[1], buf, strlen(buf));
			
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
				strcpy(buf, "3 to 4");
				write(pipe34[1], buf, strlen(buf));
			}
			else {// Child process
				close(pipe34[1]);
				read(pipe34[0], buf, 1024);
				printf("%s\n", buf);
				memset(buf, 0, sizeof(buf));
				exit(1);
			}
		}
		else {// Child process
			close(pipe23[1]);
			read(pipe23[0], buf, 1024);
			printf("%s\n", buf);
			memset(buf, 0, sizeof(buf));
			exit(1);
		}
	}
	else {// Child process
		close(pipe12[1]);
		read(pipe12[0], buf, 1024);
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
		exit(1);
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
		read(pipe51[0], buf, 1024);
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}
	else {// Child process
		close(pipe51[0]);
		strcpy(buf, "5 to 1");
		write(pipe51[1], buf, strlen(buf));
		exit(1);	
	}
	
	
	
	return 0;
}
