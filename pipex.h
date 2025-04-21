/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:39:59 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/20 14:09:59 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_fork(int *fd, char **command_1, char **command_2, char **env);
int		ft_child_1(int *fd, int *pipe_fd, char **command_1, char **env);
void	ft_free_child(char **child);
void	free_path_list(char **path_list);
int		fun_error(int i);
int		ft_error_msg(const char *msg);
char	*ft_get_path_command(char **command, char **env, char *path_mid);
char	*ft_check_command(char **path_list, char *path_mid, char *command);
int		ft_child_2(int *fd, int *pipe_fd, char **command_2, char **env);
int		empty_command(char **command_1, char **command_2, int *fd);
char	**ft_split(const char *s, char c);

#endif