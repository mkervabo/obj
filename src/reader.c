/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimose <adimose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:13:11 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/11 20:58:17 by adimose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <unistd.h>

t_obj_reader	obj_create_reader(int fd, char *buffer, size_t buffer_size)
{
	return ((t_obj_reader){
		.fd = fd,
		.buffer = buffer,
		.buffer_size = buffer_size,
		.len = 0,
		.i = 0,
		.column = 0,
		.line = 1
	});
}

int16_t		obj_reader_peek(t_obj_reader *self)
{
	size_t	len;

	if (self->i >= self->len)
	{
		len = read(self->fd, self->buffer, self->buffer_size);
		if (len <= 0)
			return (-1);
		self->i = 0;
		self->len = len;
	}
	return (self->buffer[self->i]);
}

void		obj_reader_next(t_obj_reader *self)
{
	if (obj_reader_peek(self) == '\n')
	{
		self->line++;
		self->column = 0;
	}
	else
		self->column++;
	self->i++;
}
