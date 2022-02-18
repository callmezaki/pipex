/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:54:47 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/18 02:49:36 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	first_cmd(char *arg, char **envp, t_data vars)
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
	dup2(vars.p[0], STDIN_FILENO);
	dup2(vars.p1[1], STDOUT_FILENO);
	execve(cammand_path, cmd, envp);
	close(vars.p[0]);
	close(vars.p1[1]);
}

void	second_cmd(char **argv, char **envp, t_data vars)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	vars.fd = open(argv[5], O_CREAT | O_RDWR, 0666);
	paths = get_paths(envp);
	cmd = ft_split(argv[4], ' ');
	cammand_path = get_cammand_path(paths, cmd[0]);
	if (cammand_path == NULL)
	{
		write(1, "command not found", 18);
		exit (EXIT_FAILURE);
	}
	dup2(vars.p1[0], STDIN_FILENO);
	dup2(vars.fd, STDOUT_FILENO);
	if (execve(cammand_path, cmd, envp) == -1)
		strerror(errno);
	close(vars.p1[0]);
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
	t_data	vars;

	vars.a = 2;
	vars.fd = 0;
	pipe(vars.p);
	pipe(vars.p1);
	take_input(argv[2], vars.p);
	while (vars.a != 0)
	{
		vars.id = fork();
		if (vars.id == 0)
		{
			if (vars.a == 2)
				first_cmd(argv[3], envp, vars);
			else if (vars.a == 1)
				second_cmd(argv, envp, vars);
			exit(EXIT_FAILURE);
		}
		vars.a--;
	}
	close(vars.fd);
	waitpid(vars.id, NULL, -1);
}
