/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:46:53 by orhaddao          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:25 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1
# endif

char	*get_file_G(int fd, char *tmp);
char	*get_line_file_G(char *buffer);
char	*get_next_G(char *buffer);
char	*get_next_line_G(int fd);
void	*ft_calloc_G(size_t n, size_t size);
char	*ft_strchr_G(const char *s, int c);
char	*ft_strjoin_G(char const *s1, char const *s2);
size_t	ft_strlen_G(const char *s);


#endif