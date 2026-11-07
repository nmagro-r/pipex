/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:39:12 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/21 12:43:19 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fun_error(int i)
{
	if (i == 1)
		write(2, "Error. No hay suficientes argumentos.\n", 38);
	if (i == 2)
		write(2, "Error. Archivos inválidos.\n", 28);
	return (1);
}

int	ft_error_msg(const char *msg)
{
	perror(msg);
	return (1);
}

int	empty_command(char **command_1, char **command_2, int *fd)
{
	if ((!command_1 || !command_1[0] || command_1[0][0] == '\0') && (!command_2
			|| !command_2[0] || command_2[0][0] == '\0'))
	{
		write(2, "Error: command not found\n", 25);
		ft_free_child(command_1);
		ft_free_child(command_2);
		close(fd[0]);
		close(fd[1]);
		return (127);
	}
	return (0);
}

void	ft_free_child(char **child)
{
	int	i;

	i = 0;
	if (!child)
		return ;
	while (child[i])
	{
		free(child[i]);
		i++;
	}
	free(child);
}

void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	if (!path_list)
		return ;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
}
