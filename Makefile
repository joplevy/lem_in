# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:21:18 by jplevy            #+#    #+#              #
#    Updated: 2016/10/22 19:04:25 by joeyplevy        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BO = graphical_view
NAME_LI = lem_in
CC = gcc
CFLAG = -Wall -Werror -Wextra
BO_NAME = bonus_files/main_bo.c \
			bonus_files/print_rooms.c \
			bonus_files/map.c \
			bonus_files/graphical.c \
			bonus_files/moves.c
LI_NAME = lem_in_files/main_li.c
COM_NAME = common_files/parse.c \
			common_files/room.c \
			common_files/link_comm.c \
			common_files/tools.c
OBJ_NAME_BO = $(BO_NAME:.c=.o)
OBJ_NAME = $(COM_NAME:.c=.o)
OBJ_NAME_LI = $(LI_NAME:.c=.o)
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
MLX_PATH = ./minilibx_macos/
MLX_NAME = libmlx.a
RM = rm -f

all: $(NAME_LI)

$(NAME_LI): $(OBJ_NAME) $(OBJ_NAME_LI) $(OBJ_NAME_BO)
	@echo "Creating libft"
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null
	@echo "Creating mlx"
	@$(MAKE) -C $(MLX_PATH) > /dev/null
	@echo "Creating lem_in"
	@$(CC) -o $(NAME_LI) $(OBJ_NAME) $(OBJ_NAME_LI) -L. $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "  Well done"
	@echo "Creating bonus"
	@$(CC) -o $(NAME_BO) $(OBJ_NAME) $(OBJ_NAME_BO) -L. $(LIBFT_PATH)$(LIBFT_NAME) $(MLX_PATH)$(MLX_NAME) -framework OpenGL -framework AppKit #-L. $(MLX_PATH)$(MLX_NAME)
	@echo "  Well done"

%.o: %.c
	@echo $@
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo "  Well done"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean  > /dev/null
	@$(RM) $(OBJ_NAME) $(OBJ_NAME_LI) $(OBJ_NAME_BO)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME_BO) $(NAME_LI)

re: fclean all
