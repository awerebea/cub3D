# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 21:56:47 by awerebea          #+#    #+#              #
#    Updated: 2020/08/17 15:05:58 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = libft.a
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
OFLAGS   = -O2
DBGFLAGS = -g
INCLUDES = -I includes/
SRCDIR   = srcs/
OBJDIR   = objs/

FLSDIR_1 = put/
FLS_1    = $(addprefix $(FLSDIR_1), \
			ft_putchar_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putstr_fd)
FLSDIR_2 = strings/
FLS_2    = $(addprefix $(FLSDIR_2), \
			ft_split \
			ft_strchr \
			ft_strdup \
			ft_strjoin \
			ft_strlcat \
			ft_strlcpy \
			ft_strlen \
			ft_strmapi \
			ft_strncmp \
			ft_strncpy \
			ft_strnstr \
			ft_strrchr \
			ft_strtrim \
			ft_substr)
FLSDIR_3 = memory/
FLS_3    = $(addprefix $(FLSDIR_3), \
			ft_bzero \
			ft_calloc \
			ft_memccpy \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memmove \
			ft_memset)
FLSDIR_4 = symbols/
FLS_4    = $(addprefix $(FLSDIR_4), \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_isspace \
			ft_tolower \
			ft_toupper)
FLSDIR_5 = numbers/
FLS_5    = $(addprefix $(FLSDIR_5), \
			ft_atoi \
			ft_itoa)
FLSDIR_6 = lists/
FLS_6    = $(addprefix $(FLSDIR_6), \
			ft_lstadd_back \
			ft_lstadd_front \
			ft_lstclear \
			ft_lstdelone \
			ft_lstiter \
			ft_lstlast \
			ft_lstmap \
			ft_lstnew \
			ft_lstsize)
FLSDIR_7 = get_next_line/
FLS_7    = $(addprefix $(FLSDIR_7), \
			get_next_line \
			get_next_line_utils)
SRC      = $(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4) \
			$(FLS_5) $(FLS_6) $(FLS_7)

OBJ      = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS     = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

all:			$(NAME)

$(NAME):		$(OBJ)
	ar rc		$(NAME) $?
	ranlib		$(NAME)

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p	$(OBJDIR) $(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2) \
				$(FLSDIR_3) $(FLSDIR_4) $(FLSDIR_5) $(FLSDIR_6) $(FLSDIR_7))
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

clean:
	rm -rf		$(OBJDIR)

fclean:			clean
	rm -f		$(NAME)

re:				fclean all

.PHONY: all debug clean fclean re
