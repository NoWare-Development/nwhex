#include "args.h"
#include "help.h"

#include "hex.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    display_help(HELP_IU);
    return 255;
  }

  settings_t settings = parse_args(argc - 1, argv);

  settings.file = argv[argc - 1];

  if (strcmp(argv[argc - 1], "--version") == 0 ||
      strcmp(argv[argc - 1], "-v") == 0) {
    display_help(HELP_VER);
    return 0;
  }
  else if (strcmp(argv[argc - 1], "--help") == 0 ||
           strcmp(argv[argc - 1], "-h") == 0) {
    display_help(HELP_INFO);
    return 0;
  }

  print_hex(&settings);

  return 0;
}
