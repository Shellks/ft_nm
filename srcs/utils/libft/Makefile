# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 23:11:22 by acarlott          #+#    #+#              #
#    Updated: 2025/01/20 15:12:41 by acarlott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra
CC = gcc
HEADER = ./include
AR = ar rcs
OBJS_DIR = .objs/

SRCS =	ft_atoi.c \
		ft_itoa.c \
		ft_split.c \
		ft_bzero.c \
		ft_memset.c \
		ft_memcmp.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_calloc.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_substr.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_strlcat.c \
		ft_strjoin.c \
		ft_strlcpy.c \
		ft_strmapi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_tolower.c \
		ft_strtrim.c \
		ft_toupper.c \
		ft_memmove.c \
		ft_striteri.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c\
		ft_printf.c \
		ft_dprintf.c


OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	${CC} ${CFLAGS} -I ${HEADER} -MMD -c $< -o $@ 


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -rf .objs

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

-include $(OBJS:.o=.d)

.SILENT:

.PHONY: all clean fclean re
