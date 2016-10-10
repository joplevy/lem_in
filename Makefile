# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:21:18 by jplevy            #+#    #+#              #
#    Updated: 2016/05/10 23:34:55 by joeyplevy        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CH = checker
NAME_PS = push_swap
CC = gcc
CFLAG = -Wall -Werror -Wextra
CH_NAME = checker_files/main_ch.c checker_files/check.c
PS_NAME = push_swap_files/main_ps.c push_swap_files/sort.c\
			push_swap_files/doubles.c
COM_NAME = commun_files/list.c commun_files/read.c commun_files/oper.c
OBJ_NAME_CH = $(CH_NAME:.c=.o)
OBJ_NAME = $(COM_NAME:.c=.o)
OBJ_NAME_PS = $(PS_NAME:.c=.o)
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
RM = rm -f

all: $(NAME_PS)

$(NAME_PS): $(OBJ_NAME) $(OBJ_NAME_PS) $(OBJ_NAME_CH)
	@echo "Creating libft"
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "  Well done"
	@echo "Creating push_swap"
	@$(CC) -o $(NAME_PS) $(OBJ_NAME) $(OBJ_NAME_PS) -L. $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "  Well done"
	@echo "Creating checker"
	@$(CC) -o $(NAME_CH) $(OBJ_NAME) $(OBJ_NAME_CH) -L. $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "  Well done"

%.o: %.c
	@echo $@
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo "  Well done"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_NAME) $(OBJ_NAME_PS) $(OBJ_NAME_CH)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME_CH) $(NAME_PS)

re: fclean all
