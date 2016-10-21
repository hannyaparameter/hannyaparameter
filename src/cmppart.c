/*
  cmppart.c

  >mingw32-make -f makefile.tdmgcc64
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

long long chksize(char *fn)
{
  long long len = 0;
  struct stat st;
  int fd;
  FILE *fp;
  if((fd = open(fn, O_RDONLY)) == -1){
    fprintf(stderr, "error open: %s\n", fn);
    return -1;
  }
  if(fstat(fd, &st) == -1){ // fd == fileno(fp) or stat(fn, &st) for UNIX
    fprintf(stderr, "error fstat: %s\n", fn);
    close(fd);
    return -2;
  }
  len = st.st_size;
  fprintf(stdout, "size: %12lld (%s)\n", len, fn);
  if(!(fp = fdopen(fd, "rb"))){
    fprintf(stderr, "error fopen: %s\n", fn);
    close(fd);
    return -3;
  }
  fclose(fp);
  close(fd);
  return len;
}

int cmppart(char *f0, char *f1)
{
  long long fl0 = chksize(f0);
  long long fl1 = chksize(f1);

  return 0;
}

int main(int ac, char **av)
{
  int i;
  if(ac < 3){
    fprintf(stderr, "Usage: %s file file\n", av[0]);
    return 1;
  }
  for(i = 0; i < ac; ++i)
    fprintf(stdout, "argv[%02d] = [%s]\n", i, av[i]);
  cmppart(av[1], av[2]);
  return 0;
}
