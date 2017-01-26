# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/23 15:43:55 by abarriel          #+#    #+#              #
#    Updated: 2017/01/26 15:30:30 by abarriel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls

SRC		=	ft_ls.c get_arg.c del_list.c get_long_format.c \
			print_.c recur_.c sort.c sort_.c \
			stock_.c tools.c get_long_format_.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -Iincludes/ -Ilibft/includes/

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) -L libft/ -lft -Ilibft/includes/

all: $(NAME)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)
	@make -C libft/ fclean

re: fclean $(NAME)
