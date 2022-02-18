/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:15:02 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/18 02:57:18 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	beginning(char *arg, int fd[2], int p[2], char **envp)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	paths = get_paths(envp);
	cmd = ft_split(arg, ' ');
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

void	midle_cmd(char *arg, int p[2], char **envp)
{
	char	*cammand_path;
	char	**cmd;
	char	**paths;

	paths = get_paths(envp);
	cmd = ft_split(arg, ' ');
	cammand_path = get_cammand_path(paths, cmd[0]);
	if (cammand_path == NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, " : cammand not found.\n", 23);
		exit (EXIT_FAILURE);
	}
	close(p[0]);
	dup2(p[1], STDOUT_FILENO);
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
		write(2, arg, ft_strlen(arg));
		write(2, " : cammand not found.\n", 23);
		exit (EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	cmd[0] = ft_strdup(cammand_path);
	if (execve(cammand_path, cmd, envp) == -1)
		strerror(errno);
	exit(EXIT_FAILURE);
}

void	treat_pipex(int argc, char **argv, t_vars vars, char **envp)
{
	vars.a = argc - 3;
	vars.b = 2;
	while (vars.a != 0)
	{
		pipe(vars.p);
		vars.id = fork();
		if (vars.id == 0)
		{
			if (vars.a == argc - 3)
				beginning(argv[2], vars.fd, vars.p, envp);
			else if (vars.a == 1)
				ft_end(argv[argc -2], vars.fd, envp);
			else
				midle_cmd(argv[vars.b], vars.p, envp);
		}
		dup2(vars.p[0], STDIN_FILENO);
		close(vars.p[1]);
		vars.a--;
		vars.b++;
	}
	while (vars.a < argc -3)
	{
		waitpid (vars.id, NULL, 0);
		vars.a++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	vars.a = argc - 3;
	vars.b = 2;
	if (argc < 5)
	{
		write (2, "USAGE : ./pipex infile cmd1 ... cmdn outfile\n", 46);
		exit(EXIT_FAILURE);
	}
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		treat_heredoc(argv, envp);
		exit(EXIT_SUCCESS);
	}
	if (access(argv[1], F_OK) == -1)
	{
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, " : file does not exist.\n", 25);
		exit(EXIT_FAILURE);
	}
	vars.fd[0] = open(argv[1], O_RDONLY);
	vars.fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	treat_pipex(argc, argv, vars, envp);
	exit(EXIT_SUCCESS);
}
