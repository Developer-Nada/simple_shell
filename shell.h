#ifndef INF_H
#define INF_H

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

/* for read/write buffers */
#define INF_READ_BUF_SIZE 1024
#define INF_WRITE_BUF_SIZE 1024
#define INF_BUF_FLUSH -1

/* for command chaining */
#define INF_CMD_NORM	0
#define INF_CMD_OR		1
#define INF_CMD_AND		2
#define INF_CMD_CHAIN	3

/* for convert_number() */
#define INF_CONVERT_LOWERCASE	1
#define INF_CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define INF_USE_GETLINE 0
#define INF_USE_STRTOK 0

#define INF_HIST_FILE	".simple_shell_history"
#define INF_HIST_MAX	4096

extern char **environ;

/**
 * struct inf_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct inf_liststr
{
	int num;
	char *str;
	struct inf_liststr *next;
} inf_list_t;

/**
 *struct inf_passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct inf_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	inf_list_t *env;
	inf_list_t *history;
	inf_list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char *cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
		int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} inf_t;

#define INF_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct inf_builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct inf_builtin
{
	char *type;
	int (*func)(inf_t *);
} inf_builtin_table;
/* toem_shloop.c */
int inf_hsh(inf_t, char *);
int inf_find_builtin(inf_t *);
void inf_find_cmd(inf_t *);
void inf_fork_cmd(inf_t *);

/* toem_parser.c */
int inf_is_cmd(inf_t *, char *);
char *inf_dup_chars(char *, int, int);
char *inf_find_path(inf_t *, char *, char *);

/* loophsh.c */
int inf_loophsh(char **);

/* toem_errors.c */
void inf_eputs(char *);
int inf_eputchar(char);
int inf_putfd(char c, int fd);
int inf_putsfd(char *str, int fd);

/* toem_string.c */
int inf_strlen(char *);
int inf_strcmp(char *, char *);
char *inf_starts_with(const char *, const char *);
char *inf_strcat(char *, char *);

/* toem_string1.c */
char *inf_strcpy(char *, char *);
char *inf_strdup(const char *);
void inf_puts(char *);
int inf_putchar(char);

/* toem_exits.c */
char *inf_strncpy(char *, char *, int);
char *inf_strncat(char *, char *, int);
char *inf_strchr(char *, char);

/* toem_tokenizer.c */
char **inf_strtow(char *, char *);
char **inf_strtow2(char *, char);

/* toem_realloc.c */
char *inf_memset(char *, char, unsigned int);
void inf_ffree(char **);
void *inf_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int inf_bfree(void **);

/* toem_atoi.c */
int inf_interactive(inf_t *);
int inf_is_delim(char, char *);
int inf_isalpha(int);
int inf_atoi(char *);

/* toem_errors1.c */
int inf_erratoi(char *);
void inf_print_error(inf_t *, char *);
int inf_print_d(int, int);
char *inf_convert_number(long int, int, int);
void inf_remove_comments(char *);

/* toem_builtin.c */
int inf_myexit(inf_t *);
int inf_mycd(inf_t *);
int inf_myhelp(inf_t *);

/* toem_builtin1.c */
int inf_myhistory(inf_t *);
int inf_myalias(inf_t *);

/*toem_getline.c */
ssize_t inf_get_input(inf_t *);
int inf_getline(inf_t, char *, size_t *);
void inf_sigintHandler(int);

/* toem_getinfo.c */
void inf_clear_info(inf_t *);
void inf_set_info(inf_t, char *);
void inf_free_info(inf_t *, int);

/* toem_environ.c */
char *inf_getenv(inf_t *, const char *);
int inf_myenv(inf_t *);
int inf_mysetenv(inf_t *);
int inf_myunsetenv(inf_t *);
int inf_populate_env_list(inf_t *);

/* toem_getenv.c */
char **inf_get_environ(inf_t *);
int inf_unsetenv(inf_t *, char *);
int inf_setenv(inf_t *, char *, char *);

/* toem_history.c */
char *inf_get_history_file(inf_t *info);
int inf_write_history(inf_t *info);
int inf_read_history(inf_t *info);
int inf_build_history_list(inf_t *info, char *buf, int linecount);
int inf_renumber_history(inf_t *info);

/* toem_lists.c */
inf_list_t inf_add_node(inf_list_t *, const char *, int);
inf_list_t inf_add_node_end(inf_list_t *, const char *, int);
size_t inf_print_list_str(const inf_list_t *);
int inf_delete_node_at_index(inf_list_t **, unsigned int);
void inf_free_list(inf_list_t **);

/* toem_lists1.c */
size_t inf_list_len(const inf_list_t *);
char **inf_list_to_strings(inf_list_t *);
size_t inf_print_list(const inf_list_t *);
inf_list_t *inf_node_starts_with(inf_list_t *, char *, char);
ssize_t inf_get_node_index(inf_list_t *, inf_list_t *);

/* toem_vars.c */
int inf_is_chain(inf_t *, char *, size_t *);
void inf_check_chain(inf_t *, char *, size_t *, size_t, size_t);
int inf_replace_alias(inf_t *);
int inf_replace_vars(inf_t *);
int inf_replace_string(char **, char *);

#endif
