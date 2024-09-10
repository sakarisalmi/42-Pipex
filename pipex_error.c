/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:54:05 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/03 16:57:40 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//prototypes of the functions in this file
int		error_msg(char *str);
void	perror_msg(char *str);
//

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	perror_msg(char *str)
{
	perror(str);
	exit(1);
}
