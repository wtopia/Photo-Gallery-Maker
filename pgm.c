#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define JSLIB "jquery-1.4.3.min.js"
#define THEME_GA "galleria.js"
#define THEME_GA1 "galleria.classic.js"
#define APP_GA1 "test.js"
#define APP_GA1_CSS "test.css"

void doctype(void){
  printf("<!DOCTYPE html>\n");
}

void html(int isHead){
  isHead ? printf("<html>\n") : printf("</html>\n");
}


void head(isHead){
  isHead ? printf("<head>\n") : printf("</head>\n");
}

void meta(char *charset){
  printf("<meta charset=\"%s\">\n", charset);
}

void title(char *title){
  printf("<title>%s</title>\n", title);
}

void scpt(char *src){
  printf("<script src=\"%s\"></script>\n",src);
}

void style(void){
  printf("<style>\n");
  printf("</style>\n");
}

void body(int isHead){
  isHead ? printf("<body>\n") : printf("</body>\n");
}

/*void div(char *name, char *content){
  printf("<div %s = \" %s \">\n",name,content);
}
vidはシステム関数
*/


void h(int n, char *content){
  printf("<h%d> %s </h%d>\n",n,content,n);
}

void img(char *imgs_path, char *fn){
  int slash = '/';
  char *ext1 = "jpg";
  char *ext2 = "jpeg";
  char *ext3 = "png";
  char *s_slash;

  char *s_ext1;
  char *s_ext2;
  char *s_ext3;
  
  s_slash = strchr(imgs_path, slash);

  s_ext1 = strstr(fn, ext1);
  s_ext2 = strstr(fn, ext2);
  s_ext3 = strstr(fn, ext3);

  if( (s_slash != NULL) && (s_ext1 != NULL || s_ext2 != NULL || s_ext3 != NULL) ){
    printf("<img src=\"%s%s\">\n", imgs_path, fn);
  }
  else if( s_ext1 != NULL || s_ext2 != NULL || s_ext3 != NULL )
    printf("<img src=\"%s/%s\">\n", imgs_path, fn);
}

int usage(void){
  fprintf(stderr, "Usage: ./pgm -d Photos-Directory -theme [ga1 | ga2]\n");
  return -1;
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
    if( strcmp(p->d_name, ".") == 0 || strcmp(p->d_name, "..") == 0 )
      continue;
    else{
      img(imgs_path, p->d_name);
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
  /* title of photo gallery */
  char *title_str = "Aki Nakada";
  char *charset = "utf-8";
  char *imgs_path = argv[2];

  if(argc != 5){
    usage();
    return -1;
  }
  doctype();
  html(1);
  head(1);
  meta(charset);
  title(title_str);
  scpt(JSLIB);
  scpt(THEME_GA);
  printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"test.css\">\n");
  head(0);
  body(1);
  //  div("class","content");
  //  div("id","galleria");
  printf("<div class=\"content\">\n");
  h(4, "Photo Gallery Maker");
  printf("<div id=\"galleria\">\n");

  listImages(imgs_path);

  printf("</div>\n");
  printf("</div>\n");
  
  scpt(APP_GA1);
  body(0);
  html(0);

  return 0;
}
