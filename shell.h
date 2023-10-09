#ifndef SHELL_H
#define SHELL_H

/* Standard Library Headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* External environmental variable (Global Variable) */
extern char **environ; /* Standard library variable */


/* Structs */

/**
 * struct shell_list - A singly linked list generated for
 *                     the shell program
 * @n: Integer input
 * @string: String input
 * @link_node: A pointer to the next node or NULL.
*/
typedef struct shell_list
{
	int n;
	char *string;
	struct shell_list *link_node;
} shell_lst;



/**
 * struct data_hub - this struct holds various important arguments
 * @argv: Array of strings from cli_argv
 * @argc: Argument counter
 * @path_name: The path string for the command to execute
 * @err_counter: Number of error counts
 * @file_name_: A pointer to the string of the program's name
 * @child_env: Environment variables for child to use
 * @shell_env: A node to contain the copy of environment variable
 * @env_flag: This tracks any changes in the environment variables
 * @file_desc_value: Value of file descriptor
 * @arguments_delim: Pointer to user input to check
 * @line_counter_: Counts the number of lines processed or encountered by shell
 * @line_flagger: Flag to update line_counter_
 * @check_file_desc: Checks file descriptor to see if it is 0,1 or 2.
 * @cli_argv: Command line strings
 * @cmd_mode: The command type
 * @shell_history: A node to contain the history of the shell
 * @history_line_count: Keeps count of the history line
 * @return_stats: The return status of the previously executed command
 * @exiterr_no: The exit function error number
 * @command_buffer: A string of arrays of commands
*/

typedef struct data_hub
{
	char **argv;
	int argc;
	char *path_name;
	unsigned int err_counter;
	char *file_name_;
	char **child_env;
	shell_lst *shell_env;
	int env_flag;
	int file_desc_value;
	char *arguments_delim;
	unsigned int line_counter_;
	int line_flagger;
	int check_file_desc;
	char *cli_argv;
	int cmd_mode;
	shell_lst *shell_history;
	int history_line_count;
	int return_stats;
	int exiterr_no;
	char **command_buffer;
} data_hub;

#define DATA_HUB {NULL, 0, NULL, 0, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0, NULL, 0, NULL, 0, 0, 0, NULL}


/**
 * struct builtin_datahub - This struct holds the strings
 *                          for the various built-in commands
 * @builtin_cmd: A pointer to the built-in command string
 * @builtin_func: A pointer to the built-in command function
*/
typedef struct builtin_datahub
{
	char *builtin_cmd;
	int (*builtin_func)(data_hub *);
} builtin;


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


/* Custom prototypes for print functions */
int put_char(char ch);
int e_put_char(char ch);
void cust_puts(char *string);
void e_cust_puts(char *string);
int print_numbers(int num, int file_desc);
void error_output(data_hub *my_data, char *error_message);
int puts_file_desc(char *string, int file_desc);
int put_file_desc(char ch, int file_desc);


/* Custom prototypes for environment variable */
char *get_matching_env_variable(const char *environ_to_use, data_hub *my_data);
char **retrieve_env_var(data_hub *my_data);
int build_env(data_hub *my_data, char *env_prop, char *env_value);
int fetch_env(data_hub *my_data);


/* Custom prototypes for shell_list linked list */
char **shell_list_strings(shell_lst *head);
shell_lst *add_shell_list_end(shell_lst **head, const char *string, int n);
size_t shell_list_len(const shell_lst *head_ptr);


/* Custom prototypes for commands */
int cmd_checker(char *filename, data_hub *my_data);
int builtin_command(data_hub *my_data);
int shell_cd(data_hub *my_data);
void command_search(data_hub *my_data);
char *cmd_in_path(data_hub *my_data, char *stringpath, char *command);


/* Custom prototypes for memory functions */
void free_str(char **str);
void empty_data_hub(int true, data_hub *my_data);
void free_shell_list(shell_lst **ptr_to_head);
char *memory_fill(char *mem_address, char content, unsigned int bytes);
void *shell_realloc(void *prev_mem_ptr, unsigned int prev_size,
						unsigned int curr_size);


/* Custom prototypes for history functions */
int save_history(data_hub *my_data);
char *history_pathname(data_hub *my_data);
int shell_history_list(data_hub *my_data, char *history_buffer,
							int hist_line_counter);

/* Other custom prototypes */
void fork_child(data_hub *my_data);
int interactive_mode(data_hub *my_data);
void dh_init(data_hub *my_data, char **argv);
ssize_t read_cmd_line(data_hub *my_data);
ssize_t chained_cmd_buff(data_hub *my_data, char **chained_buf,
								size_t *buf_length);
void sigint_func(__attribute__((unused))int signal_no);
ssize_t read_stdin(data_hub *my_data, char *buf_to_read, size_t *buf_size);
void comment_handler(char *line_bfr);
void upd_chain(data_hub *my_data, char *buffer, size_t *curr_idx,
					size_t starting_idx, size_t buff_length);
int chain_test(data_hub *my_data, char *ch_buff, size_t *curr_idx);
int shell_loop(data_hub *my_data, char **argv);
int shell_getline(data_hub *my_data, char **line_ptr, size_t *size);


/* MACROS */
#define BUFFER_SIZE_W 1024
#define EMPTY_BUFFER -1
#define DEFAULT_CMD 0
#define HISTORY_FILENAME	"._history"
#define GETLINE_SWITCH 0
#define BUFFER_SIZE_R 1024
#define OR_COMMAND 1
#define AND_COMMAND 2
#define SEPARATOR_COMMAND 3

#endif
