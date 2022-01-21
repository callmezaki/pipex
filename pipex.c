/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:36:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/01/21 17:59:48 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

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
		perror("ERROR ");
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
		perror("ERROR ");
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
		write(1, "command not found", 18);
		exit (EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	cmd[0] = ft_strdup(cammand_path);
	if (execve(cammand_path, cmd, envp) == -1)
		strerror(errno);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		p[2];
	int		fd[2];
	int		id;
	char	**paths;
	int		a;
	int		b;

	a = argc - 3;
	b = 2;
	paths = get_paths(envp);
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		treat_heredoc(argv, envp);
		exit(EXIT_SUCCESS);
	}
	if (access(argv[1], F_OK) == -1)
	{
		perror("ERROR ");
		exit(EXIT_FAILURE);
	}
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (a != 0)
	{
		pipe(p);
		id = fork();
		if (id == 0)
		{
			if (a == argc - 3)
				beginning(argv[2], fd, p, envp);
			else if (a == 1)
				ft_end(argv[argc -2], fd, envp);
			else
				midle_cmd(argv[b], p, envp);
		}
		dup2(p[0], STDIN_FILENO);
		close(p[1]);
		a--;
		b++;
	}
	while (a < argc -3)
	{
		waitpid (id, NULL, 0);
		a++;
	}
	ft_free_double(paths);
	exit(EXIT_SUCCESS);
}
