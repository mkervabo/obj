/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimose <adimose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:58:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/11 21:58:45 by adimose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>

void			skip_ws(t_reader *r, bool newline)
{
	int16_t	c;

	while ((c = reader_peek(r)) != -1 && (c == ' ' || c == '\t' || c == '#'
				|| (newline && c == '\n')))
	{
		if (c == '#')
		{
			while ((c = reader_peek(r)) != -1 && c != '\n')
				reader_next(r);
		}
		reader_next(r);
	}
}

t_obj_error		read_obj(t_reader *r, t_obj *obj)
{
	t_obj_error err;
	t_groupe	groupe;
	t_object	object;
	int16_t		c;

	*obj = create_obj(10);
	skip_ws(r, true);
	while ((c = reader_peek(r)) != -1 && c == 'o')
	{
		if ((err = read_object(r, &object)) != No_Error)
			return (err);
		append_object(obj, object);
		reader_next(r);
		skip_ws(r, true);
	}
	if (obj->len == 0)
	{
		object = create_object(10);
		object.name = malloc(sizeof(char));
		object.name[0] = '\0';
		while ((c = reader_peek(r) != -1) && c == 'g')
		{
			if ((err = read_groupe(r, &groupe)) != No_Error)
				return (err);
			if (append_groupe(&object, groupe) == false)
				return (Error_Malloc);
			skip_ws(r, true);
		}
	}
	return (No_Error);
}