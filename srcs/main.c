#include "minishell.h"

t_ptr   ptr;
void    init_ptr(char **envp);

int main(int argc, char **argv, char **envp)
{
    printf("%d\n", getpid());
    if (argc > 1)
        return (ft_print_error("", "Does not support arguments\n", 1));
    init_ptr(envp);
    while (1)
    {
        parse();
      //   print_all();
        execution();
    }
    return (ptr.pstatus);
}

void    init_ptr(char **envp)
{
    ptr.envp = envp_dup(envp);
}

char **envp_dup(char **envp)
{
	int i;
	char **new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	*get_final_path(char *command)
{
	char	**path;
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	path = get_path(ptr.envp);
	i = 0;
	if (path == NULL)
		return (NULL);
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (free_split(path), full_path);
		free(full_path);
		i++;
	}
	if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
		ptr.pstatus = ft_print_error(command, ": No such file or directory\n", 127);
	else
		ptr.pstatus = ft_print_error(command, ": command not found\n", 127);
	return (free_split(path), NULL);
}

