/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:40:15 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/08 16:59:51 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t str_poi(char *start, char *end)
{
	size_t	i;

	i = 0;
	if (!start || !end)
		return -1;
	while (*start != '\0' && start != end)
	{
		i++;
		start++;
	}
	return (i);
}

void var_not_found(char *cmd, int i)
{
	int	j;
	char **tmp;
	
	j = 0;
	tmp = (char **) malloc(sizeof(char*) * (i + 2));
	tmp[0] = ft_strdup(cmd);
	while (j < i)
	{
		tmp[j + 1] = ptr.envp[j];
		j++;
	}
	tmp[j + 1] = NULL;
	free(ptr.envp);
	ptr.envp = tmp;

}

void assig_value_env(char *cmd, char *var_name)
{
	t_env tmp_env;
	int	i;
	int	j;
	char **tmp;

	i = 0;
	while (ptr.envp[i] != NULL)
		i++;
	tmp_env = get_env_value(ptr.envp, var_name);
	if (tmp_env.value == NULL)
		var_not_found(cmd, i);
	else
	{
		free(ptr.envp[tmp_env.i]);
		ptr.envp[tmp_env.i] = ft_strdup(cmd);
	}
}

int check_validity(char *pos, char *cmd, size_t *var_length)
{
	if (pos == NULL)
	{
		ptr.pstatus = 0;
		return 0;
	}
	*var_length = str_poi(cmd, pos);
	if (*var_length == 0)
	{
		ft_putendl_fd("minishell: export: : not a valid identifier", 2);
		ptr.pstatus = 256;
		return 0;
	}
	return 1;
}

void export_var(char **cmd)
{
	int i = 1;
	char *pos;
	char *var_name;
	size_t var_length;

	while (cmd[i] != NULL)
	{
		var_length = 0;
		pos = ft_strchr(cmd[i], '=');
		if (check_validity(pos, cmd[i], &var_length))
		{
			var_name = malloc(var_length + 1);
			ft_strlcpy(var_name, cmd[i], var_length + 1);
			assig_value_env(cmd[i], var_name);
			free(var_name);
		}
		i++;
	}
}
