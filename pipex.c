/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:25:46 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/04 16:28:47 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prototypes of the functions in this file
int	main(int argc, char **argv, char **envp);
int	main_continued(char **argv, char **envp, t_pipex *pipex_struct);
//

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex_struct;
	char	*envp_path;

	if (argc != 5)
		return (error_msg("Invalid amount of arguments\n"));
	pipex_struct = create_p_struct();
	if (!pipex_struct)
		return (error_msg("Failed to create pipex_structure\n"));
	if (pipe(pipex_struct->pipe) == -1)
	{
		free_parent_struct(pipex_struct);
		perror_msg("Failed to pipe");
	}
	set_cmds(argv, pipex_struct);
	envp_path = get_envp_path(envp);
	if (!envp_path)
		return (error_msg("Failed to find envp_path\n"));
	pipex_struct->all_paths = ft_split(&envp_path[5], ':');
	return (main_continued(argv, envp, pipex_struct));
}

int	main_continued(char **argv, char **envp, t_pipex *pipex_struct)
{
	pipex_struct->pid1 = fork();
	if (pipex_struct->pid1 < 0)
	{
		free_parent_struct(pipex_struct);
		perror_msg("Failed to fork (pid1)");
	}
	if (pipex_struct->pid1 == 0)
		process1(argv, envp, pipex_struct);
	pipex_struct->pid2 = fork();
	if (pipex_struct->pid2 < 0)
	{
		free_parent_struct(pipex_struct);
		perror_msg("Failed to fork (pid2)");
	}
	if (pipex_struct->pid2 == 0)
		process2(argv, envp, pipex_struct);
	close(pipex_struct->pipe[1]);
	close(pipex_struct->pipe[0]);
	waitpid(pipex_struct->pid1, NULL, 0);
	waitpid(pipex_struct->pid2, NULL, 0);
	free_parent_struct(pipex_struct);
	return (0);
}
