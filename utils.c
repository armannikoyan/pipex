/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:44:44 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/22 11:01:04 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_format_argv(int argc, char **argv)
{
	char	**data;
	int		i;

	if (argc < 5)
		return (NULL);
	data = malloc(sizeof(char *) * argc);
	i = 0;
	while (argv[i + 1])
	{
		data[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	data[i] = NULL;
	return (data);
}

void	ft_free_data(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

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
