#ifndef SHELL_H
#define SHELL_H

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
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environment;


/**
 * struct liststring - singly linked list
 * @xn: the number field
 * @strng: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int xn;
	char *strng;
	struct liststring *next;
} list_v;

/**
 *struct passinformation - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arga: a string generated from getline containing arguements
 *@argb: an array of strings generated from arg
 *@pth: a string path for the current command
 *@argc: the argument count
 *@line_c: the error count
 *@error_num: the error code for exit()s
 *@linec_f: if on count this line of input
 *@filename: the program filename
 *@enva: linked list local copy of environment
 *@environment: custom modified copy of environment from LL env
 *@hist: the history node
 *@alias_n: the alias node
 *@env_ch: on if environment was changed
 *@stat: the return status of the last exec'd command
 *@cmdbuf: address of pointer to cmd_buf, on if chaining
 *@cmdbuf_t: CMD_type ||, &&, ;
 *@read_fd: the fd from which to read line input
 *@histc: the history line number count
 */
typedef struct passinformation
{
	char *arga;
	char **argb;
	char *pth;
	int argc;
	unsigned int line_c;
	int error_num;
	int linec_f;
	char *filename;
	list_v *enva;
	list_v *hist;
	list_v *alias_n;
	char **environment;
	int env_ch;
	int stat;
	char **cmdbuf;
	int cmdbuf_t;
	int read_fd;
	int histc;
} info_v;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct bltin - contains a builtin string and related function
 *@type: the builtin command flag
 *@fun: the function
 */
typedef struct bltin
{
	char *type;
	int (*fun)(info_v *);
} bltin_v;


/* hosht.c */
int hosht(info_v *, char **);
int find_blt(info_v *);
void findcmd(info_v *);
void forkcmd(info_v *);

/* path.c */
int iscmd(info_v *, char *);
char *dp_char(char *, int, int);
char *findpth(info_v *, char *, char *);

/* loophsh.c */
int loophosht(char **);

/* error_fun.c */
void _heputs(char *);
int _heputchar(char);
int _putfed(char c, int fed);
int _putsfed(char *strng, int fed);

/* string_functions.c */
int _strlength(char *);
int _strcompare(char *, char *);
char *startswith(const char *, const char *);
char *_strdog(char *, char *);

/* string_functions2.c */
char *_strcopy(char *, char *);
char *_strdp(const char *);
void _putsa(char *);
int _putchar(char);

/* string_functions3.c */
char *_strncopy(char *, char *, int);
char *_strndog(char *, char *, int);
char *_strchar(char *, char);

/* str_fun4.c */
char **strtw(char *, char *);
char **strtw2(char *, char);

/* mem_fun */
char *_memoryset(char *, char, unsigned int);
void f_free(char **);
void *_realoc(void *, unsigned int, unsigned int);

/* mem_fun2.c */
int b_free(void **);

/* more_fun.c */
int interact(info_v *);
int is_dell(char, char *);
int _isalph(int);
int _atoia(char *);

/* more_functions2.c */
int _erratoia(char *);
void print_err(info_v *, char *);
int print_dd(int, int);
char *convert_num(long int, int, int);
void remove_comm(char *);

/* emul.c */
int _myex(info_v *);
int _mycmd(info_v *);
int _myhelpo(info_v *);

/* emul2.c */
int _myhist(info_v *);
int _myaliasa(info_v *);

/* have_line.c module */
ssize_t have_input(info_v *);
int _haveline(info_v *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void clear_inf(info_v *);
void set_inf(info_v *, char **);
void free_inf(info_v *, int);

/* env.c module */
char *_getenva(info_v *, const char *);
int _myenva(info_v *);
int _mysetenva(info_v *);
int _myunsetenva(info_v *);
int populate_enva_list(info_v *);

/* env2.c module */
char **get_environa(info_v *);
int _unsetenva(info_v *, char *);
int _setenva(info_v *, char *, char *);

/* io_file_fun.c */
char *get_hist_file(info_v *info);
int write_hist(info_v *info);
int read_hist(info_v *info);
int build_hist_list(info_v *info, char *buf, int linecount);
int renumber_hist(info_v *info);

/* list_string.c module */
list_v *add_node(list_v **, const char *, int);
list_v *add_node_end(list_v **, const char *, int);
size_t print_list_str(const list_v *);
int delete_node_at_index(list_v **, unsigned int);
void free_list(list_v **);

/* list_string2.c module */
size_t list_len(const list_v *);
char **list_to_strings(list_v *);
size_t print_list(const list_v *);
list_v *node_starts_with(list_v *, char *, char);
ssize_t get_node_index(list_v *, list_v *);

/* chn.c */
int is_chn(info_v *, char *, size_t *);
void check_chn(info_v *, char *, size_t *, size_t, size_t);
int replace_aliasa(info_v *);
int replace_varsa(info_v *);
int replace_string(char **, char *);

#endif

