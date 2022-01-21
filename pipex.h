/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:56:59 by zait-sli          #+#    #+#             */
/*   Updated: 2022/01/21 18:00:00 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include<unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin_beta(char *s1, char *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_paths(char **envp);
char	*ft_strdup(const char *src);
char	**get_paths(char **envp);
char	*get_cammand_path(char **paths, char *cmd);
void	beginning(char *arg, int fd[2], int p[2], char **envp);
void	midle_cmd(char *arg, int p[2], char **envp);
void	ft_end(char *arg, int fd[2], char **envp);
void	ft_free_double(char **p);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
void	treat_heredoc(char **argv, char **envp);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_copy(char *s, char *s1);

#endif
