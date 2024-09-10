/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:17:50 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/04 15:44:21 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
// needed for perror()!
# include <stdio.h>

# include "libft/libft.h"

typedef struct s_pipex
{
	int		pipe[2];
	int		pid1;
	int		pid2;
	int		infile;
	int		outfile;
	char	**all_paths;
	char	*cmd1;
	char	**cmd1_parts;
	char	*cmd1_path;
	char	*cmd2;
	char	**cmd2_parts;
	char	*cmd2_path;
}	t_pipex;

//-------------------Functions by file------------------//

//pipex_error.c
int		error_msg(char *str);
void	perror_msg(char *str);

//pipex_create_struct.c
t_pipex	*create_p_struct(void);

// pipex_path_and_cmd.c
void	set_cmds(char **argv, t_pipex *p_struct);
int		find_cmd1_path(t_pipex *p_struct);
int		find_cmd2_path(t_pipex *p_struct);
char	*get_envp_path(char **envp);

//pipex_processes.c
void	process1(char **argv, char **envp, t_pipex *p_struct);
void	process2(char **argv, char **envp, t_pipex *p_struct);

//pipex_free.c
void	free_parent_struct(t_pipex *p_struct);
void	free_child_struct(t_pipex *p_struct);

#endif