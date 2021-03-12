#include "cmds.h"
#include "errors.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void execute(cmd c) {
	printf("%s\n", c->usage);
}

cmd new_cmd(error *err, char* usage) {
	cmd c = (cmd) malloc(sizeof(struct cmd));
	if (strlen(usage) > MAX_LINE) {
		*err = STRING_OVERFLOW;
	}
	c->execute = execute;
	strncpy(c->usage, usage, MAX_LINE);
	return c;
}
