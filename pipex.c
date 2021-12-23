/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:36:30 by zait-sli          #+#    #+#             */
/*   Updated: 2021/12/23 21:06:09 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include <fcntl.h>
#include"pipex.h"

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	int j = 0;
	int a = 0;
	int fd[2];
	pipe(fd);
	char *cammand_path;
	if (access(argv[1], F_OK) != 0)
		exit (0);
	while(envp[a])
	{
		if(ft_strncmp(envp[a], "PATH=", 5) == 0)
			break ;
		a++;
	}
	while(envp[a][i] != '=')
		i++;
	i++;
	char * temp = &envp[a][i];
	char **paths = ft_split(temp, ':');
	char **cmd = ft_split(argv[2], ' ');
	int id = fork();
	if(id == 0)
	{
		while(paths[j] != NULL)
		{
			cammand_path = ft_strjoin_beta(paths[j], cmd[0]);
			if(access(cammand_path, X_OK) == 0)
				break ;
			free (cammand_path);
			j++;
		}
		if (access(cammand_path, X_OK))
			exit (0);
		fd[0] = open(argv[1], O_RDONLY);
		dup2(fd[0], 0);
		close(fd[1]);
		execve(cammand_path, cmd, envp);
	}
	return(0);
}
