#include <stdio.h>

static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) { 
    // Define stuff here 
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) { 
    // Check arguments and set things up
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;


    ftw(argv[1], callback, MAX_FTW_DEPTH);

    // Print out the results 
}
