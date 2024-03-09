/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:33:47 by oussama           #+#    #+#             */
/*   Updated: 2024/03/06 19:05:16 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"


int get_type_v0(char *str)
{
	while (str && *str != '\0')
	{
		if (*str == '\"' || *str == '\'')
			skip_quotes(&str);
		else if (*str == '<' || *str == '>')
			return (REDIRICTION);
		else if (*str == '|' || *str == '&')
			return (OPERATOR);
		else if (*str == '(')
			return (P_OPEN);
		else if (*str == ')')
			return (P_CLOSE);
		else
			str++;
	}
	return (STRING);
}

int check_operator_syntax(char **arr, int i)
{
	if (i == 0 || arr[i + 1] == NULL)
		return (false);
	
	if (get_type_v0(arr[i - 1]) != STRING &&\
	     get_type_v0(arr[i - 1]) != P_CLOSE)
		return (false);
	if (get_type_v0(arr[i + 1]) != STRING &&\
			get_type_v0(arr[i + 1]) != P_OPEN &&\
			get_type_v0(arr[i + 1]) != REDIRICTION)
		return (false);
	return (true);
}

int check_par_syntax(char **arr, int i)
{
	if (get_type_v0(arr[i]) == P_OPEN)
	{
		if (get_type_v0(arr[i + 1]) == OPERATOR || get_type_v0(arr[i + 1]) == P_CLOSE)
			return (false);
		if (i != 0 && (get_type_v0(arr[i - 1]) != OPERATOR && get_type_v0(arr[i - 1]) != P_OPEN))
			return (false);
	}
	else
	{
		if (arr[i + 1] != NULL && get_type_v0(arr[i + 1]) != OPERATOR && get_type_v0(arr[i + 1]) != P_CLOSE)
			return (false);
		if (get_type_v0(arr[i - 1]) != STRING && get_type_v0(arr[i - 1]) != P_CLOSE)
			return (false);
	}
	return (true);
}
int check_syntax_v2(char *str)
{
	int		i;
	char	**arr;

	arr = split_tokenize(str);
	i = 0;
	while (arr[i])
	{
		if (get_type_v0(arr[i]) == REDIRICTION)
		{
			if (arr[i + 1] == NULL || get_type_v0(arr[i + 1]) != STRING)
				return (false);
		}
		else if (get_type_v0(arr[i]) == OPERATOR)
		{
			if (check_operator_syntax(arr, i) == false)
				return (false);
		}
		else if (get_type_v0(arr[i]) == P_OPEN || get_type_v0(arr[i]) == P_CLOSE)
		{
			if (check_par_syntax(arr, i) == false)
				return (false);
		}
		i++;
	}
	return (true);
}
