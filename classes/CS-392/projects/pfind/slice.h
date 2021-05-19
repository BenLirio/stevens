#ifndef SLICE_H
#define SLICE_H

struct string {
	char *head;
	int start;
	int end;
	int cap;
	char *_data_head;
};
typedef struct string* string;
string new_string();
int string_length(string s);
void free_string(string s);
string append(string base, const char* data);
string slice_string(string base, int start, int end);
#endif
