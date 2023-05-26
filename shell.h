#ifndef _ZACK_SHELL_H_
#define _ZACK_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

/* ERRORS */
#define BUFSIZE 256
#define ENOSTRING 1106
#define EILLEGAL 227
#define EWSIZE 410
#define ENOBUILTIN 415
#define EBADCD 726

extern char **environ;

/**
 * struct linkedList - linked list data structure
 * @string: environ variable path name
 * @next: pointer to next node
 */
typedef struct linkedList
{
	char *string;
	struct linkedList *next;
} linked_l;

/**
 * struct configurations - configuration of info settings
 * @env: linked list of local env variables
 * @envList: array of env variables to put into execve
 * @args: array of argument strings
 * @buffer: string buffer of user input
 * @path: array of $PATH locations
 * @fullPath: string of path with correct prepended $PATH
 * @shellName: name of shell (argv[0])
 * @lineCounter: counter of lines users have entered
 * @errorStatus: error status of last child process
 */
typedef struct configurations
{
	linked_l *env;
	char **envList;
	char **args;
	char *buffer;
	char *path;
	char *fullPath;
	char *shellName;
	unsigned int lineCounter;
	int errorStatus;
} config;

/**
 * struct builtInCommands - commands and functions associated with it
 * @command: input command
 * @func: output function
 */
typedef struct builtInCommands
{
	char *command;
	int (*func)(config *info);
} type_b;

/* main */
config *configInit(config *info);

/* built_ins */
bool findBuiltIns(config *info);
int my_exitfunc(config *info);
int my_storyfunc(config *info);
int my_aliasfunc(config *info);

/* cd */
int my_cdfunc(config *);
bool cdToHome(config *info);
bool cdToPrevious(config *info);
bool cdToCustom(config *info);
bool updateEnviron(config *info);

/* cd2 */
int updateOld(config *info);
bool updateCur(config *info, int index);

/* env */
int m_envfunc(config *info);
int set_envfunc(config *info);
int unset_envfunc(config *info);
int _isalpha(int c);

/* help */
int my_helpfunc(config *info);
int dis_helpmenu(void);
int exit_help(config *info);
int env_help(config *info);
int story_help(config *info);

/* help2 */
int alias_help(config *info);
int cd_help(config *biuld);
int setenv_help(config *info);
int unsetenv_help(config *info);
int my_helphelp(config *info);

/* built_in_helpers*/
int countArgs(char **args);
int _atoi(char *s);

/* shell */
void shell(config *info);
void check_getline(config *info);
void fork_exect(config *info);
void strp_comments(char *str);
void cvrt_lltoarr(config *info);

/* _getenv */
char *_getenv(char *input, char **environ);

/* error_handler */
void error_handler(config *info);
unsigned int counter_dgt(int num);
char *itoa(unsigned int num);
char *geterror_msg();

/* shell_helpers */
void insert_nullbyte(char *str, unsigned int index);
void dsly_Prp(void);
void dsly_newline(void);
void sigint_handler(int sigint);

/* check_path */
bool check_path(config *);
bool check_cases(config *info);

/* split_string */
bool split_string(config *info);
unsigned int counter_words(char *s);
bool its_space(char c);

/* string_helpers1 */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);

/* string_helpers2 */
char *_strtok(char *str, char *delim);
int _strcspn(char *string, char *chars);
char *_strchr(char *s, char c);

/* llfuncs1 */
linked_l *addnode(linked_l **head, char *str);
linked_l *addnode_end(linked_l **head, char *str);
size_t showlist(const linked_l *h);
int sear_node(linked_l *head, char *str);
size_t list_lenght(linked_l *h);

/* llfuncs2 */
int delnode_ndex(linked_l **head, unsigned int index);
linked_l *gen_linkedlist(char **array);
linked_l *addnode_index(linked_l **head, int index, char *str);
char *getnode_Index(linked_l *head, unsigned int index);

/* _realloc */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memor_cpy(char *dest, char *src, unsigned int n);

/* free */
void free_memb(config *info);
void free_args_buffer(config *info);
void free_args(char **args);
void free_list(linked_l *head);

#endif
