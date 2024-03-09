#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include "parse.h"
# include "execution.h"
# include "libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_ptr
{
    t_parse parse;
    char **envp;
    int pstatus;
    int *arr;
}   t_ptr;

extern t_ptr   ptr;

// typedef struct s_aolist
// {
//     char type;  
// }   t_aolist;

typedef struct s_env
{
	int	i;
	char	*value;
} t_env;



void    parse();
void    execution();
int 	ft_print_error(char *str, char *error, int n);
void	free_split(char **arr);
char	**get_path(char **envp);








///////////////BUILT/////////////


void cd_handle_home(t_env tmp_env, char *oldpwd);
void	cd_handle_path(char **cmd, char *oldpwd);
void	update_curent_pwd(void);
t_env	get_env_value(char **envp, char *to);
void var_not_found_cd(char *old_pwd, int i);
void update_cwd(char *old_pwd);
void cd_handler(char **cmd);

void echo_handler(char **cmd);
void printf_env(void);
void export_var(char **cmd);
void	unset_var(char **cmd);
void    ft_exit(char **cmd);
#endif