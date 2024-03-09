/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:03:07 by oussama           #+#    #+#             */
/*   Updated: 2024/03/08 17:04:02 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_str2int(char *str)
{
    int n;
    int i;
    int s;

    n = 0;
    i = 0;
    s = 0;
    while (str[i] && ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
        i++;
    while (str[i] && (str[i] == '-' || str[i] == '+'))
    {
        if (str[i] == '-')
            s++;
        i++;
    }
    while (str[i])
    {
        if (ft_isalnum(str[i]) == 0 && !((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
            return (ft_putendl_fd("minishell: exit: A: numeric argument required", 2), 2);
        if (ft_isalnum(str[i]))
            n = (n * 10) + (str[i] - '0');
        i++;
    }
    if (s % 2)
        return (-n);
    return (n);
}

void    ft_exit(char **cmd)
{
    int i;
    int ps;

    i = 0;
    while (cmd[i])
        i++;
    printf("exit\n");
    if (i == 1)
    {
        exit(ptr.pstatus);
    }
    else if (i >= 2)
    {
        if (i > 2)
        {
            ft_putendl_fd("minishell: exit: too many arguments", 2);
            ptr.pstatus = 1;
            return ;
        }
        ps = ft_str2int(cmd[1]);
        exit(ps);
    }    
}

