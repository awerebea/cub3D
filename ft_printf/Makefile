# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 14:51:15 by awerebea          #+#    #+#              #
#    Updated: 2020/07/20 16:18:16 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = libftprintf.a
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
OFLAGS   = -O2
DBGFLAGS = -g
INCLDIR  = includes/
SRCDIR   = srcs/
OBJDIR   = objs/

SRC      = ft_printf \
			ft_printf_libft \
			ft_printf_parsing \
			ft_printf_print_c_s \
			ft_printf_print_d_i \
			ft_printf_print_f_e \
			ft_printf_print_p_u_x_o \
			ft_printf_print_percent \
			ft_printf_utils \
			ft_printf_utils2

OBJ      = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS     = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

all:			$(OBJDIR) $(NAME)

$(NAME):		$(OBJ)
	ar rc		$(NAME) $?
	ranlib		$(NAME)

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC)		$(FLAGS) -I $(INCLDIR) -c $< -o $@ -MD

$(OBJDIR):
	mkdir -p	$(OBJDIR)

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" re

bonus: all

clean:
	rm -rf		$(OBJDIR)

fclean:			clean
	rm -f		$(NAME)

re:				fclean all

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

.PHONY: all clean fclean re debug bonus
