/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:11:56 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/26 13:27:29 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

# include "libft/libft.h"

void	ft_free_data(char **data);

char	*ft_command_path(char *cmd, char **envpath);

char	**ft_envpath(char **envp);
char	**ft_format_argv(int argc, char **argv);

#endif
