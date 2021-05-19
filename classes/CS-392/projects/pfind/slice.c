#include <stdlib.h>
#define STRING_SIZE 254
#include "slice.h"
#include <string.h>

string new_string() {
	string s = malloc(sizeof(struct string));
	s->start = 0;
	s->end = 0;
	s->cap = STRING_SIZE;
	s->_data_head = malloc(sizeof(char*) * s->cap);
	s->head = s->_data_head + s->start;
	return s;
}
int string_length(string s) {
	return s->end - s->start;
}
void free_string(string s) {
	free(s->_data_head);
	free(s);
}
string append(string base, const char* data) {
	int len = strlen(data);
	strncpy(base->head + base->end, data, len);
	base->end += len;
	*(base->_data_head + base->end) = '\0';
	return base;
}
string slice_string(string base, int start, int end) {
	base->start = start;
	base->end = end;
	base->head = base->_data_head + base->start;
	*(base->_data_head + base->end) = '\0';
	return base;
}
