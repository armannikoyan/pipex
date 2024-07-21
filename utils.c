/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:44:44 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/21 13:16:30 by anikoyan         ###   ########.fr       */
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
