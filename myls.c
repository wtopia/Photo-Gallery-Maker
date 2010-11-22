#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
/*
void
perror(const char *s);
*/

#include <stdlib.h>
#include <dirent.h>
/*
DIR *
opendir(const char *dirname);
*/
#include <string.h>

int add(int n1, int n2){
  return n1 + n2;
}

int sub(int n1, int n2){
  return add(n1, n2);
}

void listImages(char *imgs_path){
  DIR *dirp;
  struct dirent *p;
  if( (dirp = opendir(imgs_path)) == NULL ){
    perror("opendir");
    exit(1);
  }
  errno = 0;
  while( (p = readdir(dirp)) != NULL){
    if( !(strcmp(p->d_name, ".")) || !(strcmp(p->d_name, "..")) )
      continue;
    else{
      printf("%s\n", p->d_name);
      printf("add = %d\n", add(10, 2));
      printf("sub = %d\n", sub(10, 2));
    }
  }
  if(errno != 0){
    perror("readdir");
    exit(1);
  }
  if(closedir(dirp) != 0){
    perror("closedir");
    exit(1);
  }
}

int main(int argc, char *argv[]){
  
  listImages(argv[1]);
  
  return 0;
}
