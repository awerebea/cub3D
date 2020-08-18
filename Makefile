# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/19 12:14:06 by awerebea          #+#    #+#              #
#    Updated: 2020/08/18 16:50:27 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = cub3D
NAME_B     = cub3D_bonus
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

override FLAGS ?= $(CFLAGS)

#----------------------------- Mandatory part compling -------------------------
SRCDIR     = srcs/
OBJDIR     = objs/

FLSDIR_1   = ./
FLS_1      = $(addprefix $(FLSDIR_1), \
				colors \
				main \
				utils )
FLSDIR_2   = errors/
FLS_2      = $(addprefix $(FLSDIR_2), \
				errors_1 \
				errors_2)
FLSDIR_3   = file_parsing/
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
				screenshot \
				sprites_handling \
				sprites_list_init)
SRC        = $(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4)

OBJ        = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS       = $(SRC:=.d)

all:			$(NAME)

$(NAME):		$(LIBFT) $(MLX) $(OBJ)
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) $(LIBFLAGS) -o $(NAME)
	@echo '******* All done! *******'

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p	$(OBJDIR) $(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) \
				$(FLSDIR_3) $(FLSDIR_4))
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

#------------------------------- Bonus part compling ---------------------------
SRCDIR_B   = srcs_bonus/
OBJDIR_B   = objs_bonus/

FLSDIR_1_B = ./
FLS_1_B    = $(addprefix $(FLSDIR_1_B), \
				colors \
				main \
				utils )
FLSDIR_2_B = errors/
FLS_2_B    = $(addprefix $(FLSDIR_2_B), \
				errors_1 \
				errors_2)
FLSDIR_3_B = file_parsing/
FLS_3_B    = $(addprefix $(FLSDIR_3_B), \
				map_array_preparing \
				pars_args \
				pars_desc_file \
				pars_map \
				pars_options_1 \
				pars_options_2)
FLSDIR_4_B = engine/
FLS_4_B    = $(addprefix $(FLSDIR_4_B), \
				draw_minimap \
				draw_sprite \
				draw_textured_background \
				draw_vert_line \
				engine_tools \
				game \
				game_init \
				key_press_n_release \
				key_process \
				minimap_init \
				raycasting \
				screenshot \
				sprites_handling \
				sprites_list_init)
SRC_B      = $(FLS_1_B) $(FLS_2_B) $(FLS_3_B) $(FLS_4_B)

OBJ_B      = $(addprefix $(OBJDIR_B), $(SRC_B:=.o))
DFLS_B     = $(SRC_B:=.d)

bonus:			$(NAME_B)

$(NAME_B):		$(LIBFT) $(MLX) $(OBJ_B)
	$(CC)		$(FLAGS) $(OBJ_B) $(INCLUDES) $(LIBFLAGS) -o $(NAME_B)
	@echo '******* All done! *******'

$(OBJ_B):			$(OBJDIR_B)%.o: $(SRCDIR_B)%.c
	mkdir -p	$(OBJDIR_B) $(addprefix $(OBJDIR_B), $(FLSDIR_1_B) \
				$(FLSDIR_2_B) $(FLSDIR_3_B) $(FLSDIR_4_B))
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(addprefix $(OBJDIR_B), $(DFLS_B)))

#--------------------------------- Common rules --------------------------------
clean:
	rm -rf		$(OBJDIR)
	rm -rf		$(OBJDIR_B)

clean_all: clean libft_clean mlx_clean

fclean:			clean
	rm -f		$(NAME)
	rm -f		$(NAME_B)

fclean_all: fclean libft_fclean mlx_fclean

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

debug_bonus:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" bonus

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
	sed -i '' 's/KEY_ESC\ 65307/KEY_ESC\ 53/' includes/cub3d_bonus.h
	sed -i '' 's/KEY_W\ 119/KEY_W\ 13/' includes/cub3d_bonus.h
	sed -i '' 's/KEY_A\ 97/KEY_A\ \ 0/' includes/cub3d_bonus.h
	sed -i '' 's/KEY_S\ 115/KEY_S\ \ 1/' includes/cub3d_bonus.h
	sed -i '' 's/KEY_D\ 100/KEY_D\ \ 2/' includes/cub3d_bonus.h
	sed -i '' 's/KEY_LEFT\ 65361/KEY_LEFT\ 123/' includes/cub3d_bonus.h
	sed -i '' 's/KEY_RIGHT\ 65363/KEY_RIGHT\ 124/' includes/cub3d_bonus.h

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
	sed -i 's/KEY_ESC\ 53/KEY_ESC\ 65307/' includes/cub3d_bonus.h
	sed -i 's/KEY_W\ 13/KEY_W\ 119/' includes/cub3d_bonus.h
	sed -i 's/KEY_A\ \ 0/KEY_A\ 97/' includes/cub3d_bonus.h
	sed -i 's/KEY_S\ \ 1/KEY_S\ 115/' includes/cub3d_bonus.h
	sed -i 's/KEY_D\ \ 2/KEY_D\ 100/' includes/cub3d_bonus.h
	sed -i 's/KEY_LEFT\ 123/KEY_LEFT\ 65361/' includes/cub3d_bonus.h
	sed -i 's/KEY_RIGHT\ 124/KEY_RIGHT\ 65363/' includes/cub3d_bonus.h

libs: $(LIBFT) $(MLX)

re:				fclean all

test: debug
	./$(NAME) maps/test.cub

test_bonus: debug_bonus
	./$(NAME_B) maps/test_bonus.cub

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
