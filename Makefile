# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 21:56:47 by awerebea          #+#    #+#              #
#    Updated: 2020/07/27 14:41:45 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
LIBFT       = Libft/libft.a
MLX_PATH    = minilibx/mac/
MLX_NAME    = libmlx.dylib
MLX         = $(addprefix $(MLX_PATH),$(MLX_NAME))
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
OFLAGS      = -O2
DBGFLAGS    = -g
INCLUDES    = -I includes/ -I Libft/includes/ -I $(MLX_PATH)
SRCDIR      = srcs/
OBJDIR      = objs/

FLSDIR_1    = ./
FLS_1       = $(addprefix $(FLSDIR_1), \
				cub3d \
				utils )
FLSDIR_2    = error_handling/
FLS_2       = $(addprefix $(FLSDIR_2), \
				error_handling)
FLSDIR_3    = parsing_scene_description_file/
FLS_3       = $(addprefix $(FLSDIR_3), \
				map_array_preparing \
				pars_args \
				pars_desc_file \
				pars_map \
				pars_options_1 \
				pars_options_2)
SRC         = $(FLS_1) $(FLS_2) $(FLS_3)

OBJ         = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS        = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

all:			$(NAME)

$(NAME):		$(LIBFT) $(MLX) $(OBJ)
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) \
				-L Libft -lft -L $(MLX_PATH) -lmlx -o $(NAME)
	@echo		"all done!"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p	$(OBJDIR) $(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) \
				$(FLSDIR_3))
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
	make		-C Libft/

libft_clean:
	make clean	-C Libft/

libft_fclean:
	make fclean	-C Libft/

libft_re:
	make re		-C Libft/

$(MLX): mlx_force_make
	make		-C $(MLX_PATH)

mlx_clean:
	make clean	-C $(MLX_PATH)

mlx_fclean:
	make fclean	-C $(MLX_PATH)

mlx_re:
	make re		-C $(MLX_PATH)

mac:
	sed -i '' '15 s/minilibx\/linux\//minilibx\/mac\//' Makefile
	sed -i '' '16 s/libmlx.a/libmlx.dylib/' Makefile

linux:
	sed -i '15 s/minilibx\/mac\//minilibx\/linux\//' Makefile
	sed -i '16 s/libmlx.dylib/libmlx.a/' Makefile

re:				fclean_all all

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
		re
