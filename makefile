# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/08 15:25:21 by mkervabo          #+#    #+#              #
#    Updated: 2019/07/08 16:06:50 by mkervabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = obj.a
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

include src.mk

OBJS=$(patsubst src/%.c,build/%.o,$(SRCS))

all: $(NAME)

build/%.o: src/%.c include/obj.h Makefile
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re