/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:35:29 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/04 16:24:44 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prototypes of the functions in this file
void	process1(char **argv, char **envp, t_pipex *p_struct);
void	process2(char **argv, char **envp, t_pipex *p_struct);
//

void	process1(char **argv, char **envp, t_pipex *p_struct)
{
	close(p_struct->pipe[0]);
	p_struct->infile = open(argv[1], O_RDONLY);
	if (p_struct->infile < 0)
		perror_msg("infile");
	dup2(p_struct->pipe[1], STDOUT_FILENO);
	dup2(p_struct->infile, STDIN_FILENO);
	if (find_cmd1_path(p_struct) == 1)
	{
		error_msg("Command not found (pid1)\n");
		free_child_struct(p_struct);
		exit(127);
	}
	if (execve(p_struct->cmd1_path, p_struct->cmd1_parts, envp) < 0)
	{
		error_msg("the execve failed (pid1)\n");
		free_child_struct(p_struct);
		exit(1);
	}
}

void	process2(char **argv, char **envp, t_pipex *p_struct)
{
	close(p_struct->pipe[1]);
	p_struct->outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (p_struct->outfile < 0)
		perror_msg("Failed to find or create an outfile");
	dup2(p_struct->pipe[0], STDIN_FILENO);
	dup2(p_struct->outfile, STDOUT_FILENO);
	if (find_cmd2_path(p_struct) == 1)
	{
		error_msg("Command not found (pid2)\n");
		free_child_struct(p_struct);
		exit(127);
	}
	if (execve(p_struct->cmd2_path, p_struct->cmd2_parts, envp) < 0)
	{
		error_msg("the execve failed (pid2)\n");
		free_child_struct(p_struct);
		exit(1);
	}
}
