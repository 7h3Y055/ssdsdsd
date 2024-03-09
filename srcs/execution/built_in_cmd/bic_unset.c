/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:09:18 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/08 17:01:38 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void delete_var(t_env tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ptr.envp[i] != NULL)
	{
		if (i == tmp.i)
			free(ptr.envp[i]);
		else
			ptr.envp[j++] = ptr.envp[i];
		i++;
	}
	ptr.envp[j] = NULL;
}

void	unset_var(char **cmd)
{
	int	i;
	t_env	tmp;

	i = 1;
	while (cmd[i] != NULL)
	{
		tmp.i = 0;
		tmp.value = NULL;
		tmp = get_env_value(ptr.envp, cmd[i]);
		if (tmp.value != NULL)
		{
			printf("%s\n", tmp.value);
			delete_var(tmp);
		}
		i++;
	}
	ptr.pstatus = 0;
}
