/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:43 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/08 16:51:29 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void cd_handle_home(t_env tmp_env, char *oldpwd)
{
	if (tmp_env.value == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	ptr.pstatus = 256;
		return ;
	}
	if (chdir(tmp_env.value) == -1)
	{
		
		perror("minishell: cd: ");
		ptr.pstatus = 256;
		return ;
	}
	else
	{
		update_curent_pwd();
		update_cwd(oldpwd);
		ptr.pstatus = 0;
	}
}

void	cd_handle_path(char **cmd, char *oldpwd)
{
	if (chdir(cmd[1]) == -1)
		{
			perror("minishell: cd: ");
			ptr.pstatus = 256;
			return ;
		}
		else
		{
			update_curent_pwd();
			update_cwd(oldpwd);
			ptr.pstatus = 0;
		}	
}