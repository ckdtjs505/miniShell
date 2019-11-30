#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void make_commend(char **commend, char *buf){
  char * save;
  char * s;
  static const char delim[] = ";";
  int argi = 0;
    s = strtok_r(buf, delim, & save);
    while (s) {
      commend[argi++] = s;
      s = strtok_r(NULL, delim, & save);
    }
    commend[argi] = (char * ) 0;
};