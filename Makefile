# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/19 12:14:06 by awerebea          #+#    #+#              #
#    Updated: 2020/08/26 13:26:52 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
LIBFT		= Libft/libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
OFLAGS		= -O2
DBGFLAGS	= -g

override FLAGS ?= $(CFLAGS)

#-- configuring MLX library path and 'key-define' header files depending on OS
OS				= $(shell uname)
ifeq ($(OS), Linux)
	DEF_OS		= -D LINUX
	MLX_DIR		= minilibx/linux/
	MLX_NAME	= libmlx.a
	LIBFLAGS	= -lmlx -lXext -lX11 -lm
	INCLUDES	= -I $(shell ./x11init.sh)
else
	MLX_DIR		= minilibx/mac/
	MLX_NAME	= libmlx.dylib
	LIBFLAGS	= -lmlx
	INCLUDES	=
endif


MLX			= $(addprefix $(MLX_DIR),$(MLX_NAME))
INCLUDES	+= -I includes/ -I Libft/includes/ -I $(MLX_DIR)
LIBFLAGS	+= -L Libft -lft -L $(MLX_DIR)

#---------------- check if fclean needed after last project building -----------
CHECK_OBJS = $(shell find . -wholename "./objs/*_bonus.o")

ifeq ($(CHECK_OBJS), )
	CHECK_OBJS_BONUS = fclean
else
	CHECK_OBJS = fclean
endif

#--------------------------------- cub3D compiling -----------------------------
SRCDIR		= srcs/
OBJDIR		= objs/
FLSDIR_1	= ./
FLSDIR_2	= errors/
FLSDIR_3	= file_parsing/
FLSDIR_4	= engine/

FLS_1_COMMON	= $(addprefix $(FLSDIR_1), \
					colors \
					main \
					utils )

FLS_3_COMMON	= $(addprefix $(FLSDIR_3), \
					map_array_preparing \
					pars_args \
					pars_desc_file \
					pars_map \
					pars_sprites_str \
					pars_walls_str)

FLS_4_COMMON	= $(addprefix $(FLSDIR_4), \
					draw_sprite \
					draw_vert_line \
					engine_tools \
					game_init \
					key_press_n_release \
					key_process \
					raycasting \
					screenshot \
					sprites_handling \
					sprites_list_init)

ifeq ($(PROGRAM_TYPE), Bonus)
	DEF_TYPE	= -D BONUS
	FLS_1		= $(addprefix $(FLSDIR_1), \
					exit_bonus \
					opts_init_bonus)
	FLS_2		= $(addprefix $(FLSDIR_2), \
					errors_1 \
					errors_2)
	FLS_3		= $(addprefix $(FLSDIR_3), \
					check_opts_completeness_bonus \
					pars_fl_ceil_str_bonus \
					pars_line_bonus)
	FLS_4		= $(addprefix $(FLSDIR_4), \
					add_shade_bonus \
					draw_minimap_bonus \
					draw_textured_background_bonus \
					game_bonus \
					minimap_init_bonus)
	FCLEAN_FLAG	= $(CHECK_OBJS_BONUS)
else
	FLS_1		= $(addprefix $(FLSDIR_1), \
					exit \
					opts_init)
	FLS_2		= $(addprefix $(FLSDIR_2), \
					errors_1 \
					errors_2)
	FLS_3		= $(addprefix $(FLSDIR_3), \
					check_opts_completeness \
					pars_fl_ceil_str \
					pars_line)
	FLS_4		= $(addprefix $(FLSDIR_4), \
					draw_background \
					game)
	FCLEAN_FLAG	= $(CHECK_OBJS)
endif

SRC			= $(FLS_1_COMMON) $(FLS_3_COMMON) $(FLS_4_COMMON) \
				$(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

all:			$(NAME)

$(NAME):		$(FCLEAN_FLAG) $(LIBFT) $(MLX) $(OBJ)
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) $(LIBFLAGS) -o $(NAME)
	@echo '******* All done! *******'

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p	$(OBJDIR) $(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) \
				$(FLSDIR_3) $(FLSDIR_4))
	$(CC)		$(DEF_OS) $(DEF_TYPE) $(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

bonus:
	make PROGRAM_TYPE="Bonus" all

#--------------------------------- Common rules --------------------------------
clean:
	rm -rf		$(OBJDIR)

clean_all: clean libft_clean mlx_clean

fclean:			clean
	rm -f		$(NAME)
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

mlx_gcc: mlx_fclean
	@sed -i '18 s/clang/gcc/' minilibx/linux/Makefile.mk
	@echo '******* minilibx compiler set to GCC *******'

mlx_clang: mlx_fclean
	@sed -i '18 s/gcc/clang/' minilibx/linux/Makefile.mk
	@echo '******* minilibx compiler set to CLANG *******'

libs: $(LIBFT) $(MLX)

re:				fclean all

run: all
	./$(NAME) maps/map_256.cub

run_bonus: bonus
	./$(NAME) maps/map_256_bonus.cub

.PHONY:	all \
		clean \
		clean_all \
		fclean \
		fclean_all \
		debug \
		libft_clean \
		libft_fclean \
		libft_force_make \
		libft_re \
		mlx_clean \
		mlx_fclean \
		mlx_force_make \
		mlx_re \
		mlx_gcc \
		mlx_clang \
		libs \
		re \
		run \
		run_bonus
