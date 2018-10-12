#include <stdio.h>
#include <ftw.h>

static int num_dirs, num_regular;

// Used by ftw as it traverses the file structure to increment
// the number of directories and files.
static int callback(const char *fpath, const struct stat *sb, int typeflag) { 
  if(typeflag == FTW_D){
    num_dirs++;
  } else if (typeflag == FTW_F) {
    num_regular++;
  }

  return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) { 
  // Check correct number of arguments
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  // ftw is called to move through the file structure with the
  // given path, callback function, and its max depth.
  ftw(argv[1], callback, MAX_FTW_DEPTH);

  // Print out the results 
  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
