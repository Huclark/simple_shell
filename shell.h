#ifndef SHELL_H
#define SHELL_H

/* Standard Library Headers */
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


/* External environmental variable (Global Variable) */
extern char **environ; /* Standard library variable */


/* Custom prototype for Loop function */
void shell_loop(void);
char *shell_getline(void);
char **parse_line(char *cli_arg);
int shell_exec(char **argv_tkn);
int fork_cmd(char **argv_tkn);
int shell_exit(char **argv_tkn);
int shell_cd(char **argv_tkn);


/* Custom prototypes for string functions */
char *stringcopy(char *target, char *source);
int stringcompare(char *string1, char *string2);
int stringlength(char *str);
char *stringconcat(char *target, char *source);
char *stringdup(const char *source);
int atoi_(char *string);
int check_for_alphabet(int ch);
char *prefix_checker(const char *prefix, const char *string);
int delim_checker(char ch, char *delimiter);
char **strtok_delims(char *string, char *delim);
char **strtok_delim(char *string, char delim);
char *string_n_copy(char *target, char *source, int bytes);
char *string_n_concat(char *target, char *source, int bytes);
char *find_char(char *string, char ch);
char *pathstring_cpy(char *pathsring, int idx_1, int idx_2);
int string_n_cmp(const char *string1, const char *string2, int n);


/* Custom prototypes for print functions */
int put_char(char ch);
int e_put_char(char ch);
void cust_puts(char *string);
void e_cust_puts(char *string);
int print_numbers(int num, int file_desc);
int puts_file_desc(char *string, int file_desc);
int put_file_desc(char ch, int file_desc);


/* Custom prototypes for memory functions */
void free_str(char **str);
void *shell_realloc(void *prev_mem_ptr, unsigned int prev_size,
					unsigned int curr_size);
char *memory_fill(char *mem_address, char content, unsigned int bytes);

/* Custom prototypes for environment variables functions */
int shell_setenv(const char *var_name, char *value, int flag);
char **shell_env(void);
char *shell_getenv(const char *var_name);
int add_shell_env(const char *var_name, char *value);
int check_env_exist(const char *var_name);
char *create_env_string(const char *var_name, char *value);
int shell_unsetenv(const char *var_name);


/* MACROS */
#define READ_BUFFER		1024
#define TOKEN_BUFFER	512
#define DELIMITERS		" \t\r\n\a"


#endif
