/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:45:42 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/08 16:57:30 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printf_env(void)
{
	char **envp;
	
	envp = ptr.envp;
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
	ptr.pstatus = 0;
}
