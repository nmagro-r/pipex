/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:29:55 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/21 14:29:01 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	char	**command_1;
	char	**command_2;
	int		status;

	if (argc != 5)
		return (fun_error(1));
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
		return (fun_error(2));
	fd[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
		return (close(fd[0]), fun_error(2));
	command_1 = ft_split(argv[2], ' ');
	command_2 = ft_split(argv[3], ' ');
	if (empty_command(command_1, command_2, fd))
		return (127);
	status = ft_fork(fd, command_1, command_2, env);
	close(fd[0]);
	close(fd[1]);
	ft_free_child(command_1);
	ft_free_child(command_2);
	return (status);
}
