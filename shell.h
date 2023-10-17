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
#include <termios.h>
#include <limits.h>


/* Global Variables */
extern char **environ; /* For environment variable */

/**
 * struct term_settings - Struct to store the terminal settings
 * @original: Original terminal settings
*/
typedef struct term_settings
{
	struct termios original;
} terminal_set;


/* Custom prototype for Loop function */
int shell_loop(char **argv);
char *shell_getline(void);
char **parse_line1(char *cli_arg);
char **parse_line2(char *cli_arg);
int shell_exec(char **argv_tkn1, char **argv_tkn2, char **argv, char *cli_arg3,
				int line_count);
int fork_cmd(char **argv_tkn, char **argv, int line_count);
int shell_exit(char **argv, char **argv_tkn, int line_count);
int shell_cd(char **argv, char **argv_tkn, int line_count);
int child_process(char **argv_tkn, char **argv,
					char *fullpath, int line_count);
int interactive(char **argv);
int non_interactive(char **argv);

/* Custom prototypes for string functions */
char *stringcopy(char *target, char *source);
int stringcompare(char *string1, char *string2);
int stringlength(char *str);
char *stringconcat(char *target, char *source);
char *stringdup(const char *source);
char *delim_checker(char *string, int delimiter);
char *strtok_delims(char *string, char *delim);
char *string_n_copy(char *target, char *source, int bytes);
char *string_n_concat(char *target, char *source, int bytes);
int string_n_cmp(const char *string1, const char *string2, int n);
int sh_getchar(void);
char *find_char(char *string, char ch);
char *itostr(int num);
int atoi_(char *string);
int is_digit(int ch);


/* Custom prototypes for print functions */
int put_char(char ch);
int e_put_char(char ch);
void cust_puts(char *string);
void e_cust_puts(char *string);
void error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no);
void exit_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no);
void cd_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no);
int print_numbers(int num_to_print, int file_desc);


/* Custom prototypes for memory functions */
void free_str(char **str);
void *shell_realloc(void *prev_mem_ptr, unsigned int prev_size,
					unsigned int curr_size);
void free_loop(char *cli_arg1, char *cli_arg2, char *clin_arg3,
				char **arg_parse1, char **arg_parse2);


/* Custom prototypes for environment variables functions */
int shell_setenv(char *var_name, char *value, int flag);
char **shell_env(void);
char *shell_getenv(char *var_name);
char *create_env_string(char *var_name, char *value);
int shell_unsetenv(char *var_name);
char *find_command(char **argv_tkn);
char *find_exec_in_path(char *dir, char *command);
int env_builtin(char **argv, char **argv_tkn, int line_count);
int find_env_idx(char *var_name);
int add_shell_env(char *var_name, char *value);
int check_env_exist(char *var_name);


/* Custom prototypes for functions that handle terminal settings*/
void set_terminal_mode(terminal_set *term);
void reset_terminal_mode(struct term_settings *term);


/* MACROS */
#define READ_BUFFER		1024
#define TOKEN_BUFFER	512
#define DELIMITERS		" \t\r\n\a"
#define BUFFER_SIZE_W	1024
#define EMPTY_BUFFER	-1

#endif
