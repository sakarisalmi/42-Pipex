/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:48:54 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/03 17:06:44 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prototypes of the functions in this file
static void	free_string_array(char **array);
void		free_parent_struct(t_pipex *p_struct);
void		free_child_struct(t_pipex *p_struct);
//

static void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_parent_struct(t_pipex *p_struct)
{
	if (p_struct->all_paths != NULL)
		free_string_array(p_struct->all_paths);
	free(p_struct);
}

void	free_child_struct(t_pipex *p_struct)
{
	free_string_array(p_struct->all_paths);
	if (p_struct->cmd1_parts)
		free_string_array(p_struct->cmd1_parts);
	if (p_struct->cmd2_parts)
		free_string_array(p_struct->cmd2_parts);
	free(p_struct);
}
