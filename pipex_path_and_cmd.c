/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path_and_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:51:11 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/03 16:59:40 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prototypes of the functions in this file
void		set_cmds(char **argv, t_pipex *p_struct);
int			find_cmd1_path(t_pipex *p_struct);
int			find_cmd2_path(t_pipex *p_struct);
char		*get_envp_path(char **envp);
static char	*find_correct_path(char *command, t_pipex *p_struct);
//

void	set_cmds(char **argv, t_pipex *p_struct)
{
	p_struct->cmd1 = argv[2];
	p_struct->cmd2 = argv[3];
}

int	find_cmd1_path(t_pipex *p_struct)
{
	p_struct->cmd1_parts = ft_split(p_struct->cmd1, ' ');
	if (access(p_struct->cmd1_parts[0], F_OK) == 0)
		p_struct->cmd1_path = ft_strdup(p_struct->cmd1_parts[0]);
	else
		p_struct->cmd1_path = find_correct_path(*p_struct->cmd1_parts,
				p_struct);
	if (p_struct->cmd1_path != NULL)
		return (0);
	else
		return (1);
}

int	find_cmd2_path(t_pipex *p_struct)
{
	p_struct->cmd2_parts = ft_split(p_struct->cmd2, ' ');
	if (access(p_struct->cmd2_parts[0], F_OK) == 0)
		p_struct->cmd2_path = ft_strdup(p_struct->cmd2_parts[0]);
	else
		p_struct->cmd2_path = find_correct_path(p_struct->cmd2_parts[0],
				p_struct);
	if (p_struct->cmd2_path != NULL)
		return (0);
	else
		return (1);
}

char	*get_envp_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static char	*find_correct_path(char *command, t_pipex *p_struct)
{
	char	*cmd_path_tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (p_struct->all_paths[i] != NULL)
	{
		cmd_path_tmp = ft_strjoin(p_struct->all_paths[i], "/");
		cmd_path = ft_strjoin(cmd_path_tmp, command);
		free(cmd_path_tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
