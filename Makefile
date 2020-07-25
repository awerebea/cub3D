# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 21:56:47 by awerebea          #+#    #+#              #
#    Updated: 2020/07/25 10:07:45 by awerebea         ###   ########.fr        #
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
				error_handling \
				pars_args \
				pars_desc_file \
				pars_map \
				pars_options_1 \
				pars_options_2 \
				utils )
# FLSDIR_2  = strings/
# FLS_2     = $(addprefix $(FLSDIR_2), \
#             ft_strchr \
#             ft_strdup \
#             ft_strlcat \
#             ft_strlcpy \
#             ft_strlen \
#             ft_strncmp \
#             ft_strnstr \
#             ft_strrchr \
#             ft_split \
#             ft_strjoin \
#             ft_strmapi \
#             ft_strtrim \
#             ft_substr)
# FLSDIR_3  = memory/
# FLS_3     = $(addprefix $(FLSDIR_3), \
#             ft_bzero \
#             ft_calloc \
#             ft_memccpy \
#             ft_memchr \
#             ft_memcmp \
#             ft_memcpy \
#             ft_memmove \
#             ft_memset)
# FLSDIR_4  = symbols/
# FLS_4     = $(addprefix $(FLSDIR_4), \
#             ft_isalnum \
#             ft_isalpha \
#             ft_isascii \
#             ft_isdigit \
#             ft_isprint \
#             ft_tolower \
#             ft_toupper)
# FLSDIR_5  = numbers/
# FLS_5     = $(addprefix $(FLSDIR_5), \
#             ft_atoi \
#             ft_itoa)
# FLSDIR_6  = lists/
# FLS_6     = $(addprefix $(FLSDIR_6), \
#             ft_lstadd_back \
#             ft_lstadd_front \
#             ft_lstclear \
#             ft_lstdelone \
#             ft_lstiter \
#             ft_lstlast \
#             ft_lstmap \
#             ft_lstnew \
#             ft_lstsize)
# SRC       = $(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4) \
#             $(FLS_5) $(FLS_6)
SRC         = $(FLS_1)

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
	mkdir -p	$(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) $(FLSDIR_3) \
				$(FLSDIR_4) $(FLSDIR_5) $(FLSDIR_6))

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
