/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_beta_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:24:11 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/16 10:30:44 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_beta(char *s1, char *s2)
{
	int		i;
	char	*s;
	int		a;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	s = (char *)malloc(a + ft_strlen(s2) + 2);
	if (s == NULL)
		return (NULL);
	s[a++] = '/';
	i = 0;
	s = ft_copy(s, s1);
	i = 0;
	while (s2[i])
	{
		s[a] = s2[i];
		a++;
		i++;
	}
	s[a] = '\0';
	return (s);
}

char	*ft_copy(char *s, char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	return (s);
}
