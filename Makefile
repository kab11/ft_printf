# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/27 09:44:56 by mikim             #+#    #+#              #
#    Updated: 2017/10/14 23:41:58 by mikim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c\
	  ft_bzero.c\
	  ft_itoa.c\
	  ft_itoa_base.c\
	  ft_ltoa.c\
	  ft_ltoa_base.c\
	  ft_printf.c\
	  ft_strchr.c\
	  ft_strcpy.c\
	  ft_strdup.c\
	  ft_strjoin.c\
	  ft_strlen.c\
	  ft_strlower.c\
	  ft_strncmp.c\
	  ft_strnew.c\
	  ft_strsub.c\
	  ft_uitoa.c\
	  ft_uitoa_base.c\
	  ft_ultoa.c\
	  ft_ultoa_base.c\
	  init_args.c\
	  init_args_etc.c\
	  parse_args.c\
	  parse_spec.c\
	  print_base.c\
	  print_char.c\
	  print_dice.c\
	  print_digit.c\
	  print_invalid.c\
	  print_non_printable.c\
	  print_prec_a.c\
	  print_prec_e.c\
	  print_prec_f.c\
	  print_prec_g.c\
	  print_prec_tools.c\
	  print_ptraddr.c\
	  print_spec.c\
	  print_spec_etc.c\
	  print_str.c\
	  print_wchar.c\
	  print_wstr.c\
	  settings.c

OBJ = $(SRC:.c=.o)

SRCDIR = srcs
OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
HEADER = -I includes

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

NAME = libftprintf.a

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@/bin/mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADER) $< -o $@

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@ranlib $@
	@echo "[ft_printf - 모래반지 빵야빵야!]"

clean:
	@/bin/rm -rf $(OBJDIR)
	@echo "[ft_printf - clean]"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "[ft_printf - fclean]"

re: fclean all
