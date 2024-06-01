#include "hex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char *TEMPLATE_STRINGS[4] = {
  "| Offset   | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |\n",
  "| -------- | ----------------------------------------------- |\n",
  "| Offset   | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | ASCII            |\n",
  "| -------- | ----------------------------------------------- | ---------------- |\n",
};

#define print_to(fd, str, ...) \
  {                                       \
    if (fd != 0) {                        \
      fprintf(fd, str, ##__VA_ARGS__);    \
    }                                     \
    fprintf(stdout, str, ##__VA_ARGS__);  \
  }

void print_start_of_the_line(int index, FILE *fd) {
  if (index > 0) {
    print_to(fd, "|\n| %.08X | ", index);
    return;
  }
  print_to(fd, "| %.08X | ", index);
}

void print_hex(settings_t *settings) {
  FILE *fd = fopen(settings->file, "rb");
  if (!fd) {
    fprintf(stderr, "Failed to open \"%s\".\n", settings->file);
    return;
  }

  fseek(fd, 0, SEEK_END);
  int flen = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  char *content = (char *)malloc(flen);
  if (!content) {
    fprintf(stderr, "Failed to allocate memory for buffer.\n");
    return;
  }
  fread(content, 1, flen, fd);
  if (!content) {
    fprintf(stderr, "Buffer is empty.\n");
    return;
  }

  FILE *out = 0;
  if (settings->file_to_output != 0) {
    out = fopen(settings->file_to_output, "wb");
    if (!out) {
      fprintf(stderr, "Failed to open \"%s\" for writing.\n",
              settings->file_to_output);
      return;
    }
  }

  if (settings->ascii) {
    print_to(out, "%s", TEMPLATE_STRINGS[2]);
    print_to(out, "%s", TEMPLATE_STRINGS[3]);
  }
  else {
    print_to(out, "%s", TEMPLATE_STRINGS[0]);
    print_to(out, "%s", TEMPLATE_STRINGS[1]);
  }

  int index = 0;
  while (index < flen) {
    if (index % 0x10 == 0) {
      if (index > 0) {
        if (settings->ascii) {
          print_to(out, "| ");
          int buffered_index = index - 0x10;
          while (buffered_index != index) {
            if (content[buffered_index] < 32 ||
                content[buffered_index] > 126) {
              print_to(out, ".");
            }
            else {
              print_to(out, "%c", content[buffered_index]);
            }
            buffered_index++;
          }

          print_to(out, " ");
          print_start_of_the_line(index, out);
        }
        else print_start_of_the_line(index, out);
      }
      else print_start_of_the_line(index, out);
    }

    print_to(out, "%.02X ", content[index]);
    if (index == flen - 1) {
      int last_index = index;
      int remain = index - (index % 0x10);
      index++;

      while (index % 0x10 != 0) {
        print_to(out, "   ");
        index++;
      }
      print_to(out, "|");

      if (settings->ascii) {
        print_to(out, " ");
        int buffered_index = remain;
        while (buffered_index != last_index) {
          if (content[buffered_index] < 32 || content[buffered_index] > 126) {
            print_to(out, ".");
          }
          else {
            print_to(out, "%c", content[buffered_index]);
          }
          buffered_index++;
        }

        while (buffered_index != index) {
          print_to(out, " ");
          buffered_index++;
        }

        print_to(out, " |");
      }
      print_to(out, "\n");
    }
    index++;
  }

  if (out != 0) fclose(out);
  fclose(fd);
}
