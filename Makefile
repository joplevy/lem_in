# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:21:18 by jplevy            #+#    #+#              #
#    Updated: 2016/10/10 16:28:53 by jplevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BO = graphical_view
NAME_LI = lem_in
CC = gcc
CFLAG = -Wall -Werror -Wextra
BO_NAME = bonus_files/main_bo.c
LI_NAME = lem_in_files/main_li.c
COM_NAME = 
OBJ_NAME_BO = $(BO_NAME:.c=.o)
OBJ_NAME = $(COM_NAME:.c=.o)
OBJ_NAME_LI = $(LI_NAME:.c=.o)
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
RM = rm -f

all: $(NAME_LI)

$(NAME_LI): $(OBJ_NAME) $(OBJ_NAME_LI) $(OBJ_NAME_BO)
	@echo "Creating libft"
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "  Well done"
	@echo "Creating lem_in"
	@$(CC) -o $(NAME_LI) $(OBJ_NAME) $(OBJ_NAME_LI) -L. $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "  Well done"
	@echo "Creating bonus"
	@$(CC) -o $(NAME_BO) $(OBJ_NAME) $(OBJ_NAME_BO) -L. $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "  Well done"

%.o: %.c
	@echo $@
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo "  Well done"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_NAME) $(OBJ_NAME_LI) $(OBJ_NAME_BO)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME_BO) $(NAME_LI)

re: fclean all
