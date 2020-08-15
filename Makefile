# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/19 12:14:06 by awerebea          #+#    #+#              #
#    Updated: 2020/08/15 16:36:33 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = cub3D
LIBFT      = Libft/libft.a
MLX_DIR    = minilibx/linux/
MLX_NAME   = libmlx.a
MLX        = $(addprefix $(MLX_DIR),$(MLX_NAME))
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror
LIBFLAGS   = -L Libft -lft -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
OFLAGS     = -O2
DBGFLAGS   = -g
INCLUDES   = -I includes/ -I Libft/includes/ -I $(MLX_DIR)
SRCDIR     = srcs/
OBJDIR     = objs/

FLSDIR_1   = ./
FLS_1      = $(addprefix $(FLSDIR_1), \
				colors \
				main \
				utils )
FLSDIR_2   = error_handling/
FLS_2      = $(addprefix $(FLSDIR_2), \
				error_args_opts \
				error_mlx)
FLSDIR_3   = pars_scene_desc_file/
FLS_3      = $(addprefix $(FLSDIR_3), \
				map_array_preparing \
				pars_args \
				pars_desc_file \
				pars_map \
				pars_options_1 \
				pars_options_2)
FLSDIR_4   = engine/
FLS_4      = $(addprefix $(FLSDIR_4), \
				draw_background \
				draw_sprite \
				draw_vert_line \
				engine_tools \
				game \
				game_init \
				key_press_n_release \
				key_process \
				raycasting \
				sprites_handling \
				sprites_list_init)
FLSDIR_5   = bonus/
FLS_5      = $(addprefix $(FLSDIR_5), \
				draw_minimap \
				minimap_init)
SRC        = $(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4) $(FLS_5)

OBJ        = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS       = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

all:			$(NAME)

$(NAME):		$(LIBFT) $(MLX) $(OBJ)
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) $(LIBFLAGS) -o $(NAME)
	@echo '******* All done! *******'

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p	$(OBJDIR) $(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) \
				$(FLSDIR_3) $(FLSDIR_4) $(FLSDIR_5))
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

clean:
	rm -rf		$(OBJDIR)

clean_all: clean libft_clean mlx_clean

fclean:			clean
	rm -f		$(NAME)

fclean_all: fclean libft_fclean mlx_fclean

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

$(LIBFT): libft_force_make
	@echo '******* Making libft *******'
	@make		-C Libft/ --no-print-directory

libft_clean:
	make clean	-C Libft/

libft_fclean:
	make fclean	-C Libft/

libft_re:
	make re		-C Libft/

$(MLX): mlx_force_make
	@echo '******* Making minilibx *******'
	@make		-C $(MLX_DIR) --no-print-directory

mlx_clean:
	make clean	-C $(MLX_DIR)

mlx_fclean:
	make fclean	-C $(MLX_DIR)

mlx_re:
	make re		-C $(MLX_DIR)

mac: fclean libft_fclean
	sed -i '' '15 s/minilibx\/linux\//minilibx\/mac\//' Makefile
	sed -i '' '16 s/libmlx.a/libmlx.dylib/' Makefile
	sed -i '' '20 s/\ -lmlx\ -lXext\ -lX11\ -lm/\ \ -lmlx/' \
			Makefile
	sed -i '' 's/KEY_ESC\ 65307/KEY_ESC\ 53/' includes/cub3d.h
	sed -i '' 's/KEY_W\ 119/KEY_W\ 13/' includes/cub3d.h
	sed -i '' 's/KEY_A\ 97/KEY_A\ \ 0/' includes/cub3d.h
	sed -i '' 's/KEY_S\ 115/KEY_S\ \ 1/' includes/cub3d.h
	sed -i '' 's/KEY_D\ 100/KEY_D\ \ 2/' includes/cub3d.h
	sed -i '' 's/KEY_LEFT\ 65361/KEY_LEFT\ 123/' includes/cub3d.h
	sed -i '' 's/KEY_RIGHT\ 65363/KEY_RIGHT\ 124/' includes/cub3d.h

linux: fclean libft_fclean
	sed -i '15 s/minilibx\/mac\//minilibx\/linux\//' Makefile
	sed -i '16 s/libmlx.dylib/libmlx.a/' Makefile
	sed -i '20 s/\ \ -lmlx/\ -lmlx\ -lXext\ -lX11\ -lm/' \
			Makefile
	sed -i 's/KEY_ESC\ 53/KEY_ESC\ 65307/' includes/cub3d.h
	sed -i 's/KEY_W\ 13/KEY_W\ 119/' includes/cub3d.h
	sed -i 's/KEY_A\ \ 0/KEY_A\ 97/' includes/cub3d.h
	sed -i 's/KEY_S\ \ 1/KEY_S\ 115/' includes/cub3d.h
	sed -i 's/KEY_D\ \ 2/KEY_D\ 100/' includes/cub3d.h
	sed -i 's/KEY_LEFT\ 123/KEY_LEFT\ 65361/' includes/cub3d.h
	sed -i 's/KEY_RIGHT\ 124/KEY_RIGHT\ 65363/' includes/cub3d.h

libs: $(LIBFT) $(MLX)

re:				fclean all

test: debug
	./$(NAME) maps/test.cub

.PHONY:	all \
		clean \
		clean_all \
		fclean \
		fclean_all \
		debug \
		libft_force_make \
		libft_clean \
		libft_fclean \
		libft_re \
		mlx_force_make \
		mlx_clean \
		mlx_fclean \
		mlx_re \
		mac \
		linux \
		libs \
		re \
		test
