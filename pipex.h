/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:42:43 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/08/28 21:47:07 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

/*----------pipex----------*/

/*----------utils----------*/
char	*ft_strjoin2(char const *s1, char const *s2);
void free_array(char **array);
/*------------ft_split------------*/
char		**ft_split(char const *s, char c);
int			ft_free(const char *sub_s, char **ptr, char c, int *k);
int			cont_word(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
/*----------ft_split_com-----------*/
char	**ft_split_com(char *s, char c);

#endif