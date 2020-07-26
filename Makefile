# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 21:56:47 by awerebea          #+#    #+#              #
#    Updated: 2020/07/26 22:01:39 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
LIBFT       = Libft/libft.a
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
OFLAGS      = -O2
DBGFLAGS    = -g
INCLUDES    = -I includes/ -I Libft/includes/
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

$(NAME):		$(LIBFT) $(OBJDIR) $(OBJ)
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) -L Libft -lft -o $(NAME)
	@echo		"all done!"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIR):
	mkdir -p	$(OBJDIR)
	mkdir -p	$(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) $(FLSDIR_3))

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

clean:
	rm -rf		$(OBJDIR)

cclean: fclean libft_fclean

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

fclean:			clean
	rm -f		$(NAME)

$(LIBFT): libft_force_make
	@make		-C Libft/ --no-print-directory

libft_clean:
	make clean	-C Libft/

libft_fclean:
	make fclean	-C Libft/

libft_re:
	make re		-C Libft/

re:				fclean all

rre:			cclean all

.PHONY:	all \
		clean \
		cclean \
		debug \
		fclean \
		libft_clean \
		libft_fclean \
		libft_force_make \
		libft_re \
		libftprintf_clean \
		libftprintf_fclean \
		libftprintf_force_make \
		libftprintf_re \
		re \
		rre
