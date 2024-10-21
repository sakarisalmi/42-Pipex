# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 13:54:04 by ssalmi            #+#    #+#              #
#    Updated: 2023/01/04 12:30:32 by ssalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBRARY = libft_pipex.a

LIBFT = libft/

CC = cc
CFLAGS = -Wall -Werror -Wextra -I.
AR = ar rcs

FILES = pipex pipex_create_struct pipex_path_and_cmd pipex_error \
		pipex_processes pipex_free

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(SRCS:.c=.o)

#----------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
			$(MAKE) -C $(LIBFT)
			cp $(LIBFT)libft.a .
			mv libft.a $(LIBRARY)
			$(AR) $(LIBRARY) $(OBJS)
			$(CC) $(CFLAGS) $(SRCS) $(LIBRARY) -o $(NAME)

clean:
			make clean -C $(LIBFT)
			rm -f $(OBJS)

fclean: clean
			rm -f $(NAME)
			rm -f $(LIBRARY)
			rm -f $(LIBFT)libft.a

re: fclean all

.PHONY: 	all clean fclean re