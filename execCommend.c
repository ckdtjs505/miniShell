#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int exec_commend(char **arg,int argi2){
  int i, j, pid, status, fd, fd2;
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
        for (j = i + 1; j < argi2; j++) {
          if (!strcmp(arg[j], ">")) {
            char * acc1 = arg[i + 1];
            char * acc2 = arg[j + 1];

            fd = open(acc1, O_RDONLY);
            dup2(fd, 0);
            close(fd);

            fd2 = open(acc2, O_CREAT | O_RDWR | O_TRUNC, 0600);
            dup2(fd2, 1);
            close(fd2);

            arg[i] = acc1;
            arg[i + 1] = (char * ) 0;
            arg[j] = (char * ) 0;
            arg[j + 1] = (char * ) 0;
            execvp(arg[0], arg);
          }
        }
      }

      if (!strcmp(arg[i], "<")) {
        fd = open(arg[i + 1], O_RDONLY);
        if(fd == -1){
          perror("없는 파일을 입력했습니다.");
          return;
        }
        dup2(fd, 0);
        close(fd);
        arg[i] = (char * ) 0;
        arg[i + 1] = (char * ) 0;
        break;
      }
      if (!strcmp(arg[i], ">")) {
        fd = open(arg[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0600);
        dup2(fd, 1);
        close(fd);
        arg[i] = (char * ) 0;
        arg[i + 1] = (char * ) 0;
        break;
      }
      if (!strcmp(arg[i], "|")) {
        char * acc = arg[i + 1];
        int pfd[2];
        if (pipe(pfd) == -1) {
          printf("error");
        }
        switch (fork()) {
        case 0:
          close(1);
          dup(pfd[1]);
          close(pfd[0]);
          close(pfd[1]);
          arg[i] = (char * ) 0;
          arg[i + 1] = (char * ) 0;
          execvp(arg[0], arg);
        }
        switch (fork()) {
        case 0:
          close(0);
          dup(pfd[0]);
          close(pfd[0]);
          close(pfd[1]);
          execlp(acc, acc, NULL);
        }
        if (close(pfd[0]) == -1 || close(pfd[1]) == -1) perror("close5");
        while (wait(NULL) != -1);
        return 0;
      }
    }
    execvp(arg[0], arg);
  }
  if (check == 1)
    printf("%d \n", pid);
};