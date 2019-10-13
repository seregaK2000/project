#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main() {
	char* s;
	int fd[2];
	char str[1000];
	char* strp[1000];
	int n;
	for(;;) {
		printf("[student]$ ");
		char* f = fgets(str, 1000, stdin);
		int k = strlen(str);
		str[k - 1] = '\0';
		if (f == NULL) break; int i = 0;
		for (s = strtok(str, "|"); s != 0; s = strtok(NULL, "|")) {
			strp[i] = s;
			i++;

		}
		int p = fork();
		if (p == 0) {
			pipe(fd);
			int p1 = fork();
			if (p1 != 0) {
				close(fd[0]);
				close(1);
				dup(fd[1]);
				close(fd[1]);

				char* argv[1000]; 
				int j = 0;
				for (s = strtok(strp[0], " "); s != 0; s = strtok(NULL, " ")) {
					argv[j] = s;
					j++;
				}
				argv[j] = NULL;
				execvp(argv[0], argv);
				close(1);
				wait(NULL);
				return 0;
			} else {
				close(fd[1]);
				close(0);
				dup(fd[0]);
				close(fd[0]);
				char* argv1[1000]; int j1 = 0;
				for (s = strtok(strp[1], " "); s != 0; s = strtok(NULL, " ")) {
					argv1[j1] = s;
					j1++;
				}

				argv1[j1] = NULL;
				char buf;
				//while (read(fd[0],&buf, 1) > 0) {

				//write(0, &buf, 1);
				//}
				close(0);
				execlp(argv1[0], argv1[0], *stdin, NULL);
				return 0;

			}
			return 0;
		}
		wait(NULL);

	}
	return 0;
}
