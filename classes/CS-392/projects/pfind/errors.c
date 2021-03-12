#include "errors.h"

char* error_string(error *err) {
	switch(*err) {
	case NIL:
		return "nil";
	case STRING_OVERFLOW:
		return "string overflow";
	default:
		return "unkown error";
	}
}
