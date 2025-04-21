/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:52:50 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/20 14:09:30 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child_2(int *fd, int *pipe_fd, char **command_2, char **env)
{
	char	*path_command;
	char	*path_mid;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	path_mid = NULL;
	path_command = ft_get_path_command(command_2, env, path_mid);
	if (path_command)
		execve(path_command, command_2, env);
	ft_free_child(command_2);
	exit(127);
}

int	ft_child_1(int *fd, int *pipe_fd, char **command_1, char **env)
{
	char	*path_command;
	char	*path_mid;

	close(pipe_fd[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	path_mid = NULL;
	path_command = ft_get_path_command(command_1, env, path_mid);
	if (path_command)
		execve(path_command, command_1, env);
	ft_free_child(command_1);
	exit(127);
}

int	ft_fork(int *fd, char **command_1, char **command_2, char **env)
{
	int		pipe_fd[2];
	pid_t	fork_1;
	pid_t	fork_2;
	int		status;

	pipe(pipe_fd);
	fork_1 = fork();
	if (fork_1 == 0)
	{
		ft_free_child(command_2);
		ft_child_1(fd, pipe_fd, command_1, env);
	}
	fork_2 = fork();
	if (fork_2 == 0)
	{
		ft_free_child(command_1);
		status = ft_child_2(fd, pipe_fd, command_2, env);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(fork_1, &status, 0);
	waitpid(fork_2, &status, 0);
	return (0);
}
