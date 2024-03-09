/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:37:16 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/08 16:54:40 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void echo_handler(char **cmd)
{
	int i;

	i = 1;
	if (ft_strcmp(cmd[1], "-n") == 0)
		i++;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			printf(" ");
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		printf("\n");
	ptr.pstatus = 0;
}


