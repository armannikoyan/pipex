/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:15:39 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/26 13:29:01 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_process_input(char *data, int *fd, int *fd_file, char **envpath)
{
	char	**envp;
	char	**cmd;

	close(fd_file[1]);
	dup2(fd_file[0], STDIN_FILENO);
	close(fd_file[0]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(data, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	envp = ft_envpath(envpath);
	if (!envp)
		exit(EXIT_FAILURE);
	cmd[0] = ft_command_path(cmd[0], envp);
	if (!cmd[0])
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, envp) == -1)
		exit(EXIT_FAILURE);
	ft_free_data(cmd);
}

static void	ft_process_output(char *data, int *fd, int *fd_file, char **envpath)
{
	char	**envp;
	char	**cmd;

	close(fd_file[0]);
	dup2(fd_file[1], STDOUT_FILENO);
	close(fd_file[1]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	cmd = ft_split(data, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	envp = ft_envpath(envpath);
	if (!envp)
		exit(EXIT_FAILURE);
	cmd[0] = ft_command_path(cmd[0], envp);
	if (!cmd[0])
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, envp) == -1)
		exit(EXIT_FAILURE);
	ft_free_data(cmd);
}

static void	ft_25_line_rule(int *fd, int *fd_file, pid_t *pid, char **data)
{
	close(fd[0]);
	close(fd[1]);
	close(fd_file[0]);
	close(fd_file[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	ft_free_data(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	**data;
	int		fd[2];
	int		fd_file[2];
	pid_t	pid[2];

	if (argc != 5 || pipe(fd) == -1)
		return (EXIT_FAILURE);
	data = ft_format_argv(argc, argv);
	fd_file[0] = open(data[0], O_RDONLY);
	fd_file[1] = open(data[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file[0] == -1 || fd_file[1] == -1)
		exit(EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] == -1)
		return (EXIT_FAILURE);
	if (pid[0] > 0)
		pid[1] = fork();
	if (pid[1] == -1)
		return (EXIT_FAILURE);
	if (pid[0] == 0)
		ft_process_input(data[1], fd, fd_file, envp);
	if (pid[1] == 0)
		ft_process_output(data[2], fd, fd_file, envp);
	ft_25_line_rule(fd, fd_file, pid, data);
	return (EXIT_SUCCESS);
}
