#include "args.h"

#include <argp.h>

#include "help.h"
#include "version.h"

static struct argp_option options[] = {
  { "help", 'h', 0, OPTION_ARG_OPTIONAL, "Display help message." },
  { "ascii", 'a', 0, OPTION_ARG_OPTIONAL, "Display ASCII representation of data." },
  { "output", 'o', "output", 0, "Output read data to a file." },
  { "version", 'v', 0, OPTION_ARG_OPTIONAL, "Display version." },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  settings_t *sets = state->input;
  switch (key) {
    case 'h': display_help(HELP_INFO); break;
    case 'a': sets->ascii = 1; break;
    case 'o':
      sets->output = 1;
      sets->file_to_output=arg;
      break;
    case 'v': display_help(HELP_VER); break;
    default: return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = {
  options, parse_opt, PROGRAM_ARGS_DOC, PROGRAM_DOC, 0, 0, 0
};

settings_t parse_args(int argc, char **argv) {
  settings_t settings;
  settings.file = argv[argc - 1];
  settings.ascii = 0;
  settings.output = 0;
  settings.file_to_output = 0;

  argp_parse(&argp, argc, argv, 0, 0, &settings);

  return settings;
}
