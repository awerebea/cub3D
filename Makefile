# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/19 12:14:06 by awerebea          #+#    #+#              #
#    Updated: 2020/08/21 23:54:08 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
NAME_B		= cub3D_bonus
LIBFT		= Libft/libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
OFLAGS		= -O2
DBGFLAGS	= -g

override FLAGS ?= $(CFLAGS)

#-- configuring MLX library path and 'key-define' header files depending on OS
OS				= $(shell uname)
ifeq ($(OS), Linux)
	MLX_DIR		= minilibx/linux/
	MLX_NAME	= libmlx.a
	LIBFLAGS	= -lmlx -lXext -lX11 -lm
	KEYS_HEADER	= includes/keys_linux/
	INCLUDES	= -I $(shell ./x11init.sh)
else
	MLX_DIR		= minilibx/mac/
	MLX_NAME	= libmlx.dylib
	LIBFLAGS	= -lmlx
	KEYS_HEADER	= includes/keys_mac/
	INCLUDES	=
endif


MLX			= $(addprefix $(MLX_DIR),$(MLX_NAME))
INCLUDES	+= -I includes/ -I Libft/includes/ -I $(MLX_DIR) -I $(KEYS_HEADER)
LIBFLAGS	+= -L Libft -lft -L $(MLX_DIR)

#----------------------------- Mandatory part compling -------------------------
SRCDIR		= srcs/
OBJDIR		= objs/

FLSDIR_1	= ./
FLS_1		= $(addprefix $(FLSDIR_1), \
				colors \
				main \
				utils )
FLSDIR_2	= errors/
FLS_2		= $(addprefix $(FLSDIR_2), \
				errors_1 \
				errors_2)
FLSDIR_3	= file_parsing/
FLS_3		= $(addprefix $(FLSDIR_3), \
				map_array_preparing \
				pars_args \
				pars_desc_file \
				pars_map \
				pars_options_1 \
				pars_options_2)
FLSDIR_4	= engine/
FLS_4		= $(addprefix $(FLSDIR_4), \
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
SRC			= $(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

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
SRCDIR_B	= srcs_bonus/
OBJDIR_B	= objs_bonus/

FLSDIR_1_B	= ./
FLS_1_B		= $(addprefix $(FLSDIR_1_B), \
				colors \
				main \
				utils )
FLSDIR_2_B	= errors/
FLS_2_B		= $(addprefix $(FLSDIR_2_B), \
				errors_1 \
				errors_2)
FLSDIR_3_B	= file_parsing/
FLS_3_B		= $(addprefix $(FLSDIR_3_B), \
				map_array_preparing \
				pars_args \
				pars_desc_file \
				pars_map \
				pars_options_1 \
				pars_options_2)
FLSDIR_4_B	= engine/
FLS_4_B		= $(addprefix $(FLSDIR_4_B), \
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
SRC_B		= $(FLS_1_B) $(FLS_2_B) $(FLS_3_B) $(FLS_4_B)

OBJ_B		= $(addprefix $(OBJDIR_B), $(SRC_B:=.o))
DFLS_B		= $(SRC_B:=.d)

bonus:			$(NAME_B)

$(NAME_B):		$(LIBFT) $(MLX) $(OBJ_B)
	$(CC)		$(FLAGS) $(OBJ_B) $(INCLUDES) $(LIBFLAGS) -o $(NAME_B)
	@echo '******* Bonus done! *******'

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
	rm -f		screenshot*.bmp

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

libs: $(LIBFT) $(MLX)

re:				fclean all

run: all
	./$(NAME) maps/map_256.cub

run_bonus: bonus
	./$(NAME_B) maps/map_256_bonus.cub

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
		HEADERS_MAC \
		HEADERS_LINUX \
		run \
		run_bonus
