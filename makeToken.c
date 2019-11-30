#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void make_token(char **commend , char **arg, int *argi2, int *commend_num){
  char * s;
  char * save;
  static const char delim2[] = " \t\n";  
  *argi2 = 0;
  s = strtok_r(commend[*commend_num], delim2, &save); 
  *commend_num += 1;
  while (s) {
    arg[*argi2] = s;
    *argi2 += 1;
    s = strtok_r(NULL, delim2, & save);
  }
  arg[*argi2] = (char * ) 0;
}