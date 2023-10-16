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

/**
 * struct env_list - Handles the environment variables
 * @var_name: Envionment variable name
 * @var_value: Environment variable value
 * @next: Pointer to next node or NULL
*/
typedef struct env_list
{
	char *var_name;
	char *var_value;
	struct env_list *next;
} env_list;


/* Custom prototype for Loop function */
int shell_loop(char **argv, env_list **head);
char *shell_getline(void);
char **parse_line(char *cli_arg);
int shell_exec(char **argv_tkn, char **argv, int line_count, env_list **head);
int fork_cmd(char **argv_tkn, char **argv, int line_count, env_list **head);
int shell_exit(char **argv, char **argv_tkn, int line_count);
int shell_cd(char **argv, char **argv_tkn, int line_count, env_list **head);
int child_process(char **argv_tkn, char **argv,
					char *fullpath, int line_count);


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

/* int word_counter(char *string, char *delim); */


/* Custom prototypes for print functions */
int put_char(char ch);
void cust_puts(char *string);
void error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no);
void exit_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no);
void cd_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no);
int print_numbers(int num_to_print);


/* Custom prototypes for memory functions */
void free_str(char **str);
void *shell_realloc(void *prev_mem_ptr, unsigned int prev_size,
					unsigned int curr_size);


/* Custom prototypes for environment variables functions */
env_list *env_list_init(char **environ);
int shell_setenv(env_list **head, char *var_name, char *value, int flag);
char **shell_env(env_list **head);
char *shell_getenv(env_list **head, char *var_name);
char *create_env_string(char *var_name, char *value);
int shell_unsetenv(char *var_name);
char *find_command(char **argv_tkn, env_list **head);
char *find_exec_in_path(char *dir, char *command);
int env_builtin(char **argv, char **argv_tkn, int line_count, env_list **head);
int find_env_idx(char *var_name);


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
