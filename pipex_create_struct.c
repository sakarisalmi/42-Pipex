/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_create_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:24:06 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/04 15:36:50 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prototypes of the functions in this file
t_pipex	*create_p_struct(void);
//

t_pipex	*create_p_struct(void)
{
	t_pipex	*p_struct;

	p_struct = ft_calloc(1, sizeof(t_pipex));
	if (p_struct)
	{
		p_struct->pipe[0] = -1;
		p_struct->pipe[1] = -1;
		p_struct->pid1 = -1;
		p_struct->pid2 = -1;
		p_struct->infile = -1;
		p_struct->outfile = -1;
		p_struct->all_paths = NULL;
		p_struct->cmd1 = NULL;
		p_struct->cmd1_path = NULL;
		p_struct->cmd2 = NULL;
		p_struct->cmd2_path = NULL;
	}
	return (p_struct);
}
