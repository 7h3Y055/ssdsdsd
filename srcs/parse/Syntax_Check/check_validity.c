/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:03 by oussama           #+#    #+#             */
/*   Updated: 2024/03/06 19:05:43 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"

void skip_quotes(char **str)
{
    char quote = **str;
    (*str)++;
    while (**str != quote && **str != '\0')
        (*str)++;
    if (**str == quote)
        (*str)++;
}

int check_parentheses_validity_3(char **str)
{
    int	i;
    char	c;

    i = 0;
    c = **str;
    while (*str && **str == c)
    {
        i++;
        (*str)++;
    }
    (*str)--;
    if (c == '&' && i != 2)
        return (false);
    if (c == '|' && i > 2)
        return (false);
    return (true);
}

int check_parentheses_validity_2(char **str)
{
    while (**str)
    {
        if (**str == '\'' || **str == '\"')
            skip_quotes(str);
        else if (**str == '|' || **str == '&')
        {
            if (check_parentheses_validity_3(str) == 0)
                return (false);
        }
        (*str) ++;
    }
    return (true);
}

int check_parentheses_validity(char *str)
{
    char *str1;
    int open;
    int close;

    str1 = str;
    open = 0;
    close = 0;
    while (*str)
    {
        if (*str == '\'' || *str == '\"')
            skip_quotes(&str);
        else if (*str == '(')
            open++;
        else if (*str == ')')
            close++;
        if (close > open)
            return (0);
        str++;
    }
    if (open != close)
        return (false);
    if (check_parentheses_validity_2(&str1) == false)
        return (false);
    return (true);
}

void	check_quotes_validity_2(char **str, int *sing, int *doub)
{
    char	c;

    c = **str;
    if (c == '\'')
        (*sing)++;
    else if (c == '\"')
        (*doub)++;
    (*str)++;
    while (**str != '\0')
    {
        if (**str == c)
        {
            if (c == '\'')
                (*sing)++;
            else if (c == '\"')
                (*doub)++;
            (*str)++;
            return ;
        }
        (*str)++;
    }
}

int	check_quotes_validity(char *str)
{
    int	sing;
    int	doub;

    sing = 0;
    doub = 0;
    while (*str)
    {
        if (*str == '\'' || *str == '\"')
            check_quotes_validity_2(&str, &sing, &doub);
        else
            str++;
    }
    if (sing % 2 == 0 && doub % 2 == 0)
        return (true);
    return (false);
}

int	check_syntax_validity(char	*str)
{
    if (!str)
        return (0);
   if (!check_quotes_validity(str))
     	return (1);
   if (!check_parentheses_validity(str))
     	return (1);
	if (!check_syntax_v2(str))
		return (1);
   return (0);
}