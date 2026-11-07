/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:15:09 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/21 13:03:50 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_command_error(char *command)
{
	write(2, "command not found: ", 19);
	if (command)
		write(2, command, ft_strlen(command));
	write(2, "\n", 1);
}

char	*ft_check_command(char **path_list, char *path_mid, char *command)
{
	int		i;
	char	*path_end;

	i = -1;
	if (!command || command[0] == '\0')
	{
		write(2, "Error: command not found\n", 25);
		return (NULL);
	}
	while (path_list[++i])
	{
		path_mid = ft_strjoin(path_list[i], "/");
		path_end = ft_strjoin(path_mid, command);
		free(path_mid);
		if (access(path_end, X_OK) == 0)
		{
			free_path_list(path_list);
			return (path_end);
		}
		free(path_end);
	}
	return (NULL);
}

char	*ft_get_path_command(char **command, char **env, char *path_mid)
{
	int		i;
	char	*path;
	char	**path_list;

	if (!command[0])
		return (NULL);
	path_list = NULL;
	if (ft_strchr(command[0], '/'))
		if (access(command[0], X_OK) == 0)
			return (ft_strdup(command[0]));
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path_list = ft_split(env[i] + 5, ':');
			path = ft_check_command(path_list, path_mid, command[0]);
			if (path)
				return (path);
		}
	}
	free_path_list(path_list);
	return (NULL);
}
