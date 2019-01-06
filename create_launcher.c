#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
  char * app=calloc(120,sizeof(char));
  char * exec=calloc(120,sizeof(char));
  if (app==NULL || exec==NULL) return 1;

  printf("App name:\n" );
  fgets(app, 50, stdin);
  printf("Command to launch app:\n");
  fgets(exec, 50, stdin);

//Removing the /n 's  from app and exec.
  const size_t len = strlen(app);
if (len && app[len-1] == '\n') {
    app[len-1] = '\0';
}
const size_t len2 = strlen(exec);
if (len2 && exec[len-1] == '\n') {
    exec[len-1] = '\0';
}


  char file_path[250];
  strcpy(file_path,"/home/jean/Desktop/");
  strcat(file_path, app);
  char * str=".desktop";
  strcat(file_path, str);

  FILE * fp=NULL;
  fp=fopen(file_path, "w");
  if (!fp) {

    fprintf(stderr, "Could not open/create file: %s\n", strerror(errno) );
    return 1;
  }

  fprintf(fp, "#!/usr/bin/env xdg-open\n\n");
  fprintf(fp, "[Desktop Entry]\n" );
  fprintf(fp, "Name=%s\n",app);
  fprintf(fp, "Exec=%s\n",exec );
  fprintf(fp, "Terminal=false\n");
  fprintf(fp, "Type=Application\n" );

  int err =chmod(file_path, 00777);
  if (err < 0)
      {
          fprintf(stderr, "error in chmod : %s\n", strerror(errno));
          exit(1);
      }

  fclose(fp);
  free(fp);
  free(app);
  free(exec);
  return 0;
}
