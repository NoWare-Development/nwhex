#include "help.h"

#include <stdio.h>
#include "version.h"

void display_help(int type) {
  switch (type) {
    case HELP_INFO: {
      fprintf(stdout, "%s\n", PROGRAM_VERSION);
      fprintf(stdout, "Usage:\n");
      fprintf(stdout, "\tnwhex [flags] <file>\n\n");
      fprintf(stdout, "Available flags:\n");
      fprintf(stdout, "\t--help -h -- Display help message.\n");
      fprintf(stdout, "\t--version -v -- Display version.\n");
      fprintf(stdout, "\t--ascii -a -- Display ASCII representation of data.\n");
      fprintf(stdout, "\t--output -o [file] -- Output read data to a file.\n");
    } break;
    case HELP_IU: {
      fprintf(stdout, "Usage:\n");
      fprintf(stdout, "\tnwhex [flags] <file>\n\n");
      fprintf(stdout, "Available flags:\n");
      fprintf(stdout, "\t--help -h -- Display help message.\n");
      fprintf(stdout, "\t--version -v -- Display version.\n");
      fprintf(stdout, "\t--ascii -a -- Display ASCII representation of data.\n");
      fprintf(stdout, "\t--output -o [file] -- Output read data to a file.\n");
    } break;
    case HELP_UA: {

    } break;
    case HELP_VER: {
      fprintf(stdout, "%s\n", PROGRAM_VERSION);
    } break;
  }
}
