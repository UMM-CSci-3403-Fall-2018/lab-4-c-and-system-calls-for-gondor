#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Uses the stat() function to determine if the file
   * referenced by path is a directory or not.
   * Calls S_ISDIR to see if the file is a directory. Checks the
   * return value from stat in case there is a problem.
   */
  struct stat *buf = (struct stat*) malloc(sizeof(struct stat));
  if(stat(path, buf) < 0){
    printf("Directory or File doesn't exist");
  }
  
  bool dir = S_ISDIR((*buf).st_mode);
  free(buf);

  return dir;
}

void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, uses opendir() to open the
   * directory, and then uses readdir() to loop through the entries
   * and process them. Checks to avoid processing the
   * "." and ".." directory entries. closedir() is called when done.
   *
   * Uses chdir() to move into a new directory and leaves when
   * all of the files and subdirectories are processed.
   */
  num_dirs++;

  chdir(path);
  DIR *dir;
  struct dirent *dp = (struct dirent*) malloc(sizeof(struct dirent));

  dir = opendir(".");
  while((dp = readdir(dir)) != NULL){
   char* name = (*dp).d_name;
    if(strcmp(name, ".")!=0 && strcmp(name, "..")!=0){
      process_path(name);
    }
  }
  closedir(dir);

  chdir("..");
  free(dp);
}

void process_file(const char* path) {
  /*
   * Updates the number of regular files.
   */
  num_regular++;
}

// Checks if an item is a file or a directory
// and processes it accordingly.
void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensures the correct number of
  // arguments are given.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
