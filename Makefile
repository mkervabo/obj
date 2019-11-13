# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 13:29:47 by mkervabo          #+#    #+#              #
#    Updated: 2019/11/11 14:43:26 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SECONDARY:

libobj.rootdir := $(dir $(lastword $(MAKEFILE_LIST)))

libobj.objects := append.o create.o obj.o read_double.o read_group.o \
	read_triangle.o read_vertex.o reader.o utils.o free.o
libobj.objects := $(addprefix $(libobj.rootdir)src/, $(libobj.objects))

$(libobj.objects): CFLAGS   ?= -Wall -Wextra -Werror
$(libobj.objects): CPPFLAGS += -MMD -MP -I$(libobj.rootdir)include

.PHONY: all
all: libobj.a

libobj.a: libobj.a($(libobj.objects))

.PHONY: clean
clean::
	$(RM) $(libobj.objects:.o=.{o,d,gcno,gcna})

.PHONY: fclean
fclean:: clean
	$(RM) libobj.a

.PHNOY: re
re: fclean all

-include $(wildcard $(libobj.rootdir)src/*.d)
