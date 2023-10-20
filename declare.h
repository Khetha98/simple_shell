#ifndef DECLARE_H
#define DECLARE_H


#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>



#define READ_BUF_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1



#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096



extern char **environ;


/**
 * struct liststr - is the singly linked list
 * @num: is the number field
 * @str: it a string
 * @next: it points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;



/**
 * struct passinfo - Structure containing pseudo-arguments to be passed
 *                   into a function, enabling a consistent prototype for
 *                   a function pointer structure.
 *
 * @arg: A string obtained from getline that contains arguments.
 * @argv: An array of strings generated from the 'arg' field.
 * @path: A string representing the path to the current command.
 * @argc: The count of arguments.
 * @line_count: The count of errors.
 * @error_code: The error code for exit() calls.
 * @linecount_flag: Flag indicating whether to count this line of input.
 * @program_name: The program filename.
 * @env: A linked list that is a local copy of the 'environ' variable.
 * @environ: A custom modified copy of the 'environ' variable from the linked list 'env'.
 * @history: A node representing command history.
 * @alias: A node representing aliases.
 * @env_changed: Flag indicating if 'environ' was changed.
 * @status: The return status of the last executed command.
 * @cmd_buf: Address of a pointer to 'cmd_buf'; used for command chaining.
 * @cmd_buf_type: Type of command ('CMD_type'): ||, &&, or ;
 * @read_fd: The file descriptor from which to read line input.
 * @histcount: The count of history line numbers.
 */


typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int error_code;
    int line_count_flag;
    char *program_name;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf;
    int cmd_buf_type;
    int read_fd;
    int histCount;
} info_t;





#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}



/**
 * struct builtin - Structure representing a built-in command along with its
 *                 associated function.
 *
 * @type: Flag indicating the type of the built-in command.
 * @func: Pointer to the function that implements the built-in command.
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



/* toem_errors.c */
void _print_error_string(char *);
int _write_error_char(char);
int _write_to_fd(char c, int fd);
int _print_to_fd(char *str, int fd);





/* loopshell_loop.c */
int loopshell_loop(char **);

/* toem_atoi.c */
int is_shell_interactive(info_t *);
int is_character_delimiter(char, char *);
int is_alphabetic(int);
int string_to_integer(char *);


/* toem_parser.c */
int isExecutableCommand(info_t *, char *);
char *duplicateSubstring(char *, int, int);
char *findCommandInPath(info_t *, char *, char *);

/* toem_errors1.c */
int print_decimal(int, int);
char *convert_to_string(long int, int, int);
void remove_first_comment(char *);
int _erratoi(char *);
void print_error_message(info_t *, char *);



/* toem_shloop.c */
int shell_loop(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* toem_memory.c */
int freeAndNull(void **);

/* toem_getenv.c */
char **get_environment(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* toem_exits.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void signal_handler(int);

/* toem_getinfo.c */
void initialize_info(info_t *);
void setupInfo(info_t *, char **);
void cleanupInfo(info_t *, int);


/* toem_history.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* toem_environ.c */
char *get_environment_variable(info_t *, const char *);
int my_environment(info_t *);
int my_set_environment_variable(info_t *);
int my_unset_environment_variable(info_t *);
int populate_environment_list(info_t *);

/* toem_builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* toem_realloc.c */
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);


/* toem_string.c */
int str_length(char *);
int str_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *string_concatenate(char *, char *);

/* toem_builtin1.c */
int my_history(info_t *);
int my_alias(info_t *);


/* toem_tokenizer.c */
char **string_split(char *, char *);
char **string_split2(char *, char);

/* toem_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int write_character(char);


/* toem_vars.c */
int is_chain_delimiter(info_t *, char *, size_t *);
void check_chain_continuation(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* toem_lists1.c */
size_t listLength(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* toem_lists.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNode_end(list_t **, const char *, int);
size_t printListStr(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);



#endif 

