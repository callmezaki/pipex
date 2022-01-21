/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:54:47 by zait-sli          #+#    #+#             */
/*   Updated: 2022/01/20 17:56:18 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	first_cmd(char *arg, char **envp, int *p, int *p1)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	paths = get_paths(envp);
	cmd = ft_split(arg, ' ');
	cammand_path = get_cammand_path(paths, cmd[0]);
	if (cammand_path == NULL)
	{
		perror("ERROR ");
		exit (EXIT_FAILURE);
	}
	dup2(p[0], STDIN_FILENO);
	dup2(p1[1], STDOUT_FILENO);
	execve(cammand_path, cmd, envp);
	close(p[0]);
	close(p1[1]);
}

void	second_cmd(char **argv, char **envp, int *p1, int fd)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	fd = open(argv[5], O_CREAT | O_RDWR, 0666);
	paths = get_paths(envp);
	cmd = ft_split(argv[4], ' ');
	cammand_path = get_cammand_path(paths, cmd[0]);
	if (cammand_path == NULL)
	{
		write(1, "command not found", 18);
		exit (EXIT_FAILURE);
	}
	dup2(p1[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	if (execve(cammand_path, cmd, envp) == -1)
		strerror(errno);
	close(p1[0]);
}

void	take_input(char *arg, int *p)
{
	char	*line;
	char	*input;

	input = NULL;
	while (ft_strcmp(arg, ft_strtrim(line, "\n")))
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(1);
		if (ft_strcmp(arg, ft_strtrim(line, "\n")) == 0)
		{
			free(line);
			break ;
		}
		write(p[1], line, ft_strlen(line));
		free(line);
	}
	close(p[1]);
}

void	treat_heredoc(char **argv, char **envp)
{
	int		fd;
	int		p[2];
	int		p1[2];
	int		a;
	int		id;

	a = 2;
	pipe(p);
	pipe(p1);
	take_input(argv[2], p);
	while (a != 0)
	{
		id = fork();
		if (id == 0)
		{
			if (a == 2)
				first_cmd(argv[3], envp, p, p1);
			else if (a == 1)
				second_cmd(argv, envp, p1, fd);
			exit(EXIT_FAILURE);
		}
		a--;
	}
	close(fd);
	waitpid(id, NULL, -1);
}
