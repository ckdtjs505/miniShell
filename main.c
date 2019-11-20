#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXARG 7

main() {
  char buf[256];
  char * arg[MAXARG];
  char * temp[MAXARG];
  char * s;
  char * save;
  int argi, argi2;
  static
  const char delim2[] = " \t\n";
  static
  const char delim[] = ";";
  int pid, pid2, status, i, fd;

  while (1) {
    printf("myshell$ ");
    gets(buf);
    argi = 0;

    s = strtok_r(buf, delim, & save);
    while (s) {
      temp[argi++] = s;
      s = strtok_r(NULL, delim, & save);
    }

    temp[argi] = (char * ) 0;

    int j = 0;
    while (temp[j]) {
      argi2 = 0;
      s = strtok_r(temp[j++], delim2, & save);
      while (s) {
        arg[argi2++] = s;
        s = strtok_r(NULL, delim2, & save);
      }
      arg[argi2] = (char * ) 0;

      int i;
      int check = 0;
      for (i = 0; i < argi2; i++) {
        if (!strcmp(arg[i], "&")) {
          arg[i] = (char * ) 0;
          check = 1;
          break;
        }
      }

      if ((pid = fork()) == -1)
        perror("fork failed");
      else if (pid != 0) {
        if (check == 0)
          pid = waitpid(pid, & status, 0);
      } else {

        for (i = 0; i < argi2; i++) {
          if (!strcmp(arg[i], "<")) {
            fd = open(arg[i + 1], O_RDONLY);
            dup2(fd, 0);
            close(fd);
            arg[i] = (char * ) 0;
            arg[i + 1] = (char * ) 0;

            if((pid2 = fork()) == -1){
              perror("fork error");
            }else if (pid == 0 ){
              execvp(arg[0], arg);
            }
            
            break;
          }
          if (!strcmp(arg[i], ">")) {
            fd = open(arg[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0600);
            dup2(fd, 1);
            close(fd);
            arg[i] = (char * ) 0;
            arg[i + 1] = (char * ) 0;
            execvp(arg[0], arg);
            break;
          }
        }
        execvp(arg[0], arg);
      }
      if (check == 1)
        printf("%d \n", pid);
    }
  }
  exit(0);
}