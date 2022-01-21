/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:36 by zait-sli          #+#    #+#             */
/*   Updated: 2022/01/20 01:00:24 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	**get_paths(char **envp)
{
	int	a;

	a = 0;
	while (envp[a])
	{
		if (ft_strncmp(envp[a], "PATH=", 5) == 0)
			return (ft_split(&envp[a][5], ':'));
		a++;
	}
	return (NULL);
}

char	*get_cammand_path(char **paths, char *cmd)
{
	int		j;
	char	*cammand_path;

	j = 0;
	while (paths[j] != NULL)
	{
		cammand_path = ft_strjoin_beta(paths[j], cmd);
		if (access(cammand_path, X_OK) == 0)
			return (cammand_path);
		free (cammand_path);
		j++;
	}
	return (NULL);
}

void	ft_free_double(char **p)
{
	int	a;

	a = 0;
	while (a)
		free(p[a++]);
	free(p);
}
