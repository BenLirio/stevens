#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_WORD 128
#define MAX_CMDS 16

enum bool {false, true};
typedef enum bool bool;

int main() {
  char b[MAX_LINE];
  char cmds[MAX_CMDS][MAX_WORD];
  int cur_cmd = 1;
  while (1) {
    int n = read(0, &b, MAX_LINE);
    if (n == 0) {
      exit(0);
    }
    bool white_space = false;
    for (int i = 0; i < n; i++) {
      bool seperator = *(b+i) == ' ' || *(b+i) == '\t' || *(b+i) == '\n';
      if (seperator == false && white_space == true) {
        cur_cmd++;
      }
      white_space = seperator;
      if (seperator == false) {
        cmds[cur_cmd] = "asdf";
      }
    }
  }
  return 0;
}
