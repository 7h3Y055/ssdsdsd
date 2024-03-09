/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:22:19 by oussama           #+#    #+#             */
/*   Updated: 2024/03/06 18:54:07 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_VALIDITY_H
# define CHECK_VALIDITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define STRING -1
#define P_OPEN -2
#define P_CLOSE -3
#define REDIRICTION -4
#define OPERATOR -6

int		check_parentheses_validity_3(char **str);
int		check_parentheses_validity_2(char **str);
int		check_parentheses_validity(char *str);
int		check_quotes_validity(char *str);
int		check_syntax_validity(char	*str);
int		get_type(char *str);
int		check_operator_syntax(char **arr, int i);
int		check_par_syntax(char **arr, int i);
int		check_syntax_v2(char *str);
int		skip_quotes_i(char *str, int *i);
void	skip_quotes(char **str);
void	check_quotes_validity_2(char **str, int *sing, int *doub);
void	join_str(char ***arr, char *str);
void	join_chars(char ***arr, char *str, int *i);
void	join_command(char ***arr, char *str, int *i);
char	**split_tokenize(char *str);

#endif