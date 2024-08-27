/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split com.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:08:22 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/08/08 17:39:59 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	cont_word2(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while(s[i] != '\'' && s[i] != '\0')
				i++;
		}
		if ((s[i + 1] == '\0' || s[i + 1] == c) && s[i] != c)
			j++;
		i++;
	}
	return (j);
}

int	ft_free2(const char *sub_s, char **ptr, char c, int *k)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if (sub_s[j] == '\'')
	{
		flag = 1;
		j++;
		while(sub_s[j] != '\'' && sub_s[j] != '\0')
			j++;
	}
	while (sub_s[j] != c && sub_s[j])
		j++;
	ptr[*k] = ft_substr(sub_s, flag, j - 2 * flag);
	if (!ptr[*k])
	{
		while (*k >= 0)
			free(ptr[(*k)--]);
		free(ptr);
		return (-1);
	}
	(*k)++;
	return (*k);
}

void iteri(int i, int *j, char *s, char c)
{
		if (s[i] == '\'')
		{
			(*j)++;
			while(s[i + *j] != '\'' && s[i + *j] != '\0')
				(*j)++;
		}
	while (s[i + *j] != c && s[i + *j])
		(*j)++;
}

char	**ft_split_com(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = -1;
	k = 0;
	ptr = malloc (sizeof(char *) * (cont_word2(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[++i])
	{
		j = 0;
		if (s[i] != c)
		{
			iteri(i, &j, s, c);
			k = ft_free2(&s[i], ptr, c, &k);
			if (k == -1)
				return (NULL);
			i += j -1;
		}
	}
	ptr[k] = 0;
	return (ptr);
}
