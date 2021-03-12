#ifndef CMDS_H
#define CMDS_H
#define MAX_LINE 128
struct cmd {
	char usage[MAX_LINE];
	void (*execute)();
};
typedef struct cmd* cmd;
cmd new_cmd();
#endif
