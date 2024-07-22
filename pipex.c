/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:15:39 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/22 10:29:47 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_envpath(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*ft_path(char *cmd, char **envpath)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	while (envpath[i])
	{
		tmp = ft_strjoin("/", cmd);
		line = ft_strjoin(envpath[i], tmp);
		if (access(line, F_OK) == 0)
		{
			free(tmp);
			return (line);
		}
		free(line);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_child_process(char **data, int *fd, char **envpath)
{
	char	**envp;
	char	**cmd;

	dup2(fd[2], STDIN_FILENO);
	close(fd[2]);
	close(fd[3]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(data[1], ' ');
	envp = ft_envpath(envpath);
	cmd[0] = ft_path(cmd[0], envp);
	if (execve(cmd[0], cmd, envp) == -1)
		exit(EXIT_FAILURE);
}

void	ft_parent_process(char **data, int *fd, char **envpath, pid_t pid)
{
	char	**envp;
	char	**cmd;

	waitpid(pid, NULL, 0);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	cmd = ft_split(data[2], ' ');
	envp = ft_envpath(envpath);
	cmd[0] = ft_path(cmd[0], envp);
	if (execve(cmd[0], cmd, envp) == -1)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	**data;
	int		fd[4];
	pid_t	pid;

	if (argc != 5 || pipe(fd) == -1)
		return (EXIT_FAILURE);
	data = ft_format_argv(argc, argv);
	fd[2] = open(data[0], O_RDONLY);
	fd[3] = open(data[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[2] == -1 || fd[3] == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		ft_child_process(data, fd, envp);
	else
		ft_parent_process(data, fd, envp, pid);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	ft_free_data(data);
	return (EXIT_SUCCESS);
}
