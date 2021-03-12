#ifndef ERRORS_H
#define ERRORS_H
enum error {NIL, STRING_OVERFLOW};
typedef enum error error;
char* error_string(error *err);
#endif /* ERRORS_H */
