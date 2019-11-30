#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXARG 7

#include "makeCommend.h"
#include "makeToken.h"
#include "execCommend.h"

main() {
  char buf[256];
  char * arg[MAXARG];
  char * commend[MAXARG];
  int argi, argi2;
  int commend_num;

  while (1) {
    // display prompt msg
    printf("myshell$ ");

    // get input
    gets(buf);

    // make commend; 
    make_commend(commend, buf);

    // exec commend;
    commend_num = 0;
    while (commend[commend_num]) {
      make_token(commend, arg, & argi2, & commend_num);
      exec_commend(arg, argi2);
    }
  }
  exit(0);
}