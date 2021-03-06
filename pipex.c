/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:36:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/18 02:53:37 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	beginning(char *arg, int fd[2], int p[2], char **envp)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	cmd = ft_split(arg, ' ');
	paths = get_paths(envp);
	cammand_path = get_cammand_path(paths, cmd[0]);
	if (cammand_path == NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, " : cammand not found.\n", 23);
		exit (EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(p[1], STDOUT_FILENO);
	cmd[0] = ft_strdup(cammand_path);
	execve(cammand_path, cmd, envp);
	exit(EXIT_FAILURE);
}

void	ft_end(char *arg, int fd[2], char **envp)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	paths = get_paths(envp);
	cmd = ft_split(arg, ' ');
	cammand_path = get_cammand_path(paths, cmd[0]);
	if (cammand_path == NULL)
	{
		write(1, arg, ft_strlen(arg));
		write(1, " : cammand not found.\n", 23);
		exit (EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	cmd[0] = ft_strdup(cammand_path);
	if (execve(cammand_path, cmd, envp) == -1)
		strerror(errno);
	exit(EXIT_FAILURE);
}

void	treat_pipex(char **argv, t_vars vars, char **envp)
{
	vars.a = 2;
	while (vars.a != 0)
	{
		pipe(vars.p);
		vars.id = fork();
		if (vars.id == 0)
		{
			if (vars.a == 2)
				beginning(argv[2], vars.fd, vars.p, envp);
			else if (vars.a == 1)
				ft_end(argv[3], vars.fd, envp);
		}
		dup2(vars.p[0], STDIN_FILENO);
		close(vars.p[1]);
		vars.a--;
	}
	while (vars.a < 2)
	{
		waitpid (vars.id, NULL, 0);
		vars.a++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	if (argc != 5)
	{
		write (2, "USAGE : pipex file1 cmd1 cmd2 file2", 36);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1)
	{
		write(2, argv[1], ft_strlen(argv[1]));
		write (2, " : file does not exist.\n", 25);
		exit(EXIT_FAILURE);
	}
	vars.a = 2;
	vars.fd[0] = open(argv[1], O_RDONLY);
	vars.fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	treat_pipex(argv, vars, envp);
	exit(EXIT_SUCCESS);
}
