#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_fdbackup
{
    int in;
    int out;
}   t_fdbackup;


int handle_execution(t_aolist *head);
void    all_execution(t_aolist *head);
char **envp_dup(char **envp);
char	*get_final_path(char *command);
void    fdbackup(t_fdbackup *backup);
void    default_io(t_fdbackup backup);
void    apply_outredirections(t_io *io);
void    apply_inredirections(t_io *io);
void    handle_quots_value(t_cmd *cmd);


void    execute_echo(char **args);
void    execute_cd(char **args);
void    execute_pwd(char **args);
void    execute_export(char **args);
void    execute_unset(char **args);
void    execute_env(char **args);
void    execute_exit(char **args);



#endif