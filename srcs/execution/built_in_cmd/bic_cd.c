/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:56:03 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/08 16:54:10 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_curent_pwd(void)
{
	t_env	tmp_env;
	char	*cu;
	char	*new_pwd;

	cu = getcwd(NULL, 0);
	tmp_env = get_env_value(ptr.envp, "PWD");
	if (tmp_env.value == NULL)
		return ;
	new_pwd = ft_strjoin("PWD=", cu);
	free(ptr.envp[tmp_env.i]);
	ptr.envp[tmp_env.i] = new_pwd;	
}

void var_not_found_cd(char *old_pwd, int i)
{
	char **tmp;
	int	j;

	j = 0;
	tmp = (char **) malloc(sizeof(char *) * (i + 2));
	tmp[0] = ft_strjoin("OLDPWD=", old_pwd);
	while (j < i)
	{
		tmp[j + 1] = ptr.envp[j];
		j++;
	}
	tmp[j + 1] = NULL;
	free(ptr.envp);
	ptr.envp = tmp;

}

void update_cwd(char *old_pwd)
{
	t_env	tmp_env;
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (ptr.envp[i] != NULL)
		i++;
	tmp_env = get_env_value(ptr.envp, "OLDPWD");
	if (tmp_env.value == NULL)
		var_not_found_cd(old_pwd, i);
	else
	{
		free(ptr.envp[tmp_env.i]);
		ptr.envp[tmp_env.i] = ft_strjoin("OLDPWD=", old_pwd);
	}
}

void cd_handler(char **cmd)
{
	t_env	tmp_env;
	char	*oldcwd;
	int		i;

	i = 0;
	tmp_env = get_env_value(ptr.envp, "HOME");
	oldcwd = ft_strdup(getcwd(NULL, 0));
	while (cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		ptr.pstatus = 256;
		return ;
	}
	else if (i == 1)
		cd_handle_home(tmp_env, oldcwd);
	else if (i == 2)
		cd_handle_path(cmd, oldcwd);
	free(oldcwd);
}
