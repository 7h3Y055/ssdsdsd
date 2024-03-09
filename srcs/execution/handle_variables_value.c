#include "minishell.h"


char    *add_char_to_str(char *str, char c);
void    handle_single_quot(char **new_str, char *str, int *index);
void    handle_double_quot(char **new_str, char *str, int *index);
char *quot_value(char *str);
void    handle_value(char **new_str, char *str, int *index);

char    *ft_get_envkey(char *str)
{
    int i;
    char *key;

    i = 1;
    while (str[i] && ft_isalnum(str[i]))
        i++;
    key = malloc(sizeof(char) * i + 1);
    i = 1;
    while (str[i] && ft_isalnum(str[i]))
    {
        key[i - 1] = str[i];
        key[++i - 1] = '\0';
    }
    return (key);
}

void    handle_quots_value(t_cmd *cmd)
{
    int     i;

    i = 0;
    while (cmd->args[i])
    {
        cmd->args[i] = quot_value(cmd->args[i]);
        i++;
    }
}

char *quot_value(char *str)
{
    char    *new_str;
    int     i;

    i = 0;
    new_str = ft_calloc(sizeof(char) , 30);
    while (str[i])
    {
        if (str[i] == '\'')
            handle_single_quot(&new_str, &str[i], &i);
        else if (str[i] == '"')
            handle_double_quot(&new_str, &str[i], &i);
        else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
            handle_value(&new_str, &str[i], &i);
        else
            new_str = add_char_to_str(new_str, str[i]);
        i++;
    }
    free(str);
    return (new_str);
}

t_env	get_env_value(char **envp, char *to)
{
	int		i;
	int		j;
	char	*tmp;
	t_env	tmp_env;

	i = 0;
	j = 0;
	j = ft_strlen(to) + 1;
	tmp = ft_strjoin(to, "=");
	tmp_env.i = 0;
	tmp_env.value = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], tmp, j) == 0)
		{
			free(tmp);
			tmp_env.i = i;
			tmp_env.value = envp[i] + j;
			break ;
		}
		i++;
	}
	return (tmp_env);
}

void    handle_value(char **new_str, char *str, int *index)
{
    char    *key;
    char    *pstatus;
    t_env  env;
    int i;

    i = 0;
    if (str[i] == '$')
    {
        i++;
        if (str[i] != '?')
        {
            key = ft_get_envkey(str);
            env = get_env_value(ptr.envp, key);
            if (env.value)
                *new_str = ft_strjoin(*new_str, env.value);
            if (index)
                *index += ft_strlen(key);
        }
        else
        {
            pstatus = ft_itoa(ptr.pstatus / 256);
            *new_str = ft_strjoin(*new_str, pstatus);
            *index += 1;
            free(pstatus);
        }
    }
}

void    handle_single_quot(char **new_str, char *str, int *index)
{
    char *tmp;
    int i;
    int len;
    int j;

    (*index) += 1;
    len = 0;
    while (str[len] && str[len] != '\'')
        len++;
    tmp = malloc(sizeof(char) * (ft_strlen(*new_str) + len + 2));
    i = 0;
    while ((*new_str)[i])
    {
        tmp[i] = (*new_str)[i];
        i++;
    }
    j = 1;
    while (str[j])
    {
        if (str[j] == '\'')
            break ;
        tmp[i++] = str[j++];
        (*index)++;
    }
    tmp[i] = 0;
    *new_str = tmp;
}


// char    *ft_get_envkey(char *str)
// {
//     int i;
//     char *key;

//     i = 1;
//     while (str[i] && ft_isalnum(str[i]))
//         i++;
//     key = malloc(sizeof(char) * i + 1);
//     i = 1;
//     while (str[i] && ft_isalnum(str[i]))
//     {
//         key[i - 1] = str[i];
//         key[++i - 1] = '\0';
//     }
//     return (key);
// }

void    handle_double_quot(char **new_str, char *str, int *index)
{
    char *tmp;
    int i;
    int len;
    int j;
    char *s;

    (*index) += 1;
    len = 0;
    while (str[len] && str[len] != '"')
        len++;
    tmp = malloc(sizeof(char) * (ft_strlen(*new_str) + len + 2));
    i = 0;
    while ((*new_str)[i])
    {
        tmp[i] = (*new_str)[i];
        i++;
    }
    j = 1;
    while (str[j])
    {
        if (str[j] == '"')
            break ;
        tmp[i++] = str[j++];
        (*index)++;
    }
    tmp[i] = 0;
    (*new_str)[0] = 0;
    i = 0;
    s = malloc(sizeof(char) * 30);
    s[0] = 0;
    while (tmp[i])
    {
        if (tmp[i] == '$')
            handle_value(&s, &tmp[i], &i);
        else
            s = add_char_to_str(s, tmp[i]);
        i++;
    }
    *new_str = s;
}

char    *add_char_to_str(char *str, char c)
{
    char *new_str;
    char s[2];
    int len;

    if (!str)
    {
        s[0] = c;
        s[1] = 0;
        return (ft_strdup(s));
    }
    new_str = ft_strdup(str);
    len = ft_strlen(new_str);
    new_str[len] = c;
    new_str[len + 1] = 0;
    return (new_str);
}