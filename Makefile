# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chon <chon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 12:58:35 by chon              #+#    #+#              #
#    Updated: 2024/04/08 15:08:41 by chon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIBFT_DIR = ./libft
MLX_DIR = ./mlx
LIBS = ./libft/libft.a ./mlx/libmlx.a
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
MLX_FLAGS = -framework OpenGL -framework AppKit
OBJS = $(SRCS:.c=.o)
SRCS = fdf.c check_map.c collect_data_points.c create_img.c \
color.c utils1.c utils2.c set_controls.c
OBJS_B = $(BONUS:.c=.o)
BONUS = ./bonus/fdf_bonus.c ./bonus/check_map_bonus.c \
./bonus/collect_data_points_bonus.c ./bonus/create_img_bonus.c \
./bonus/utils1_bonus.c ./bonus/utils2_bonus.c \
./bonus/set_controls_bonus.c ./bonus/set_controls2_bonus.c ./bonus/color_bonus.c

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR) 
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBS) $(OBJS) -o $(NAME)
	
all: $(NAME)

bonus: $(NAME) $(OBJS_B)
	make -C $(LIBFT_DIR) 
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBS) $(OBJS_B) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -f $(OBJS_B)

re: fclean all

.PHONY = all clean fclean re
