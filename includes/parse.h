#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include "get_next_line.h"
# include <sys/wait.h>

// replace exit_code to main exit code in ptr




typedef struct s_io
{
    char type;
    int fd;
    char *file;
    struct s_io *next;
}   t_io;

typedef struct s_cmd
{
    char **args;
    t_io    *in_red;
    t_io    *out_red;
}   t_cmd;

typedef struct s_plist
{
    char type;
    int pid;
    void *data;
    struct s_plist  *next;
}   t_plist;

typedef struct s_aolist
{
    int in;
    int out;
    char    type;// C O P T
    void    *data;// address
    struct s_aolist *next;
    struct s_aolist *prev;
}   t_aolist;

typedef struct s_parse
{
    char *row_data;
    char **data;
    int tmp_flag;
    t_aolist    *aolist;
}   t_parse;

char **split_and_or(char *row_data);
int     split_and_or_len( char *row_data);
int     check_input(char *row_data);
char *get_split_line(char *row_data, int *index);
int split_line_len(char *row_data);
void    create_aolist();
t_plist *create_plist(char *data);
// int     split_pipe_len(char *data);
int pipe_line_len(char *data);
char *get_pipe_line(char *data, int *index);
t_aolist *new_node_aolist(char *data, t_aolist *prev);
char get_type(char *data);
int is_operator(char *data, int index);
t_plist *new_node_plist(char *data);
t_aolist    *last_node_aolist(t_aolist *head);
int is_a_parenthesis(char *data);
t_aolist *create_tree(char *dtaa);
void    print_tree(t_aolist *tree);
t_cmd   *create_command(char *data);
t_io    *fill_inred(char **args);
t_io    *fill_outred(char **args);
char *get_file(char *data);
t_io    *new_io_node(char *data, char type);
void    add_back_io(t_io **head, t_io *new);
int skip_quotation(char *data, int index);
// char	**ft_split_v2(char *data);
char **ft_split_own(char *str);
char *remove_quotation(char *str);
int skip_quotes(char *str, int *i);
void    print_all();
int		check_syntax_validity(char	*str);

#endif


