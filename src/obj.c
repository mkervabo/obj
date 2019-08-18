/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:58:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/08/18 19:23:42 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>

void			obj_skip_ws(t_obj_reader *r, bool newline)
{
	int16_t	c;

	while ((c = obj_reader_peek(r)) != -1 && (c == ' ' || c == '\t' || c == '\r' || c == '#'
				|| (newline && c == '\n')))
	{
		if (c == '#')
		{
			while ((c = obj_reader_peek(r)) != -1 && c != '\n')
				obj_reader_next(r);
		}
		obj_reader_next(r);
	}
}

t_obj_error		read_obj(t_obj_reader *r, t_obj *obj)
{
	t_obj_error 	err;
	t_groupe		groupe;
	t_obj_object	object;
	int16_t			c;

	*obj = create_obj(10);
	obj_skip_ws(r, true);
	while ((c = obj_reader_peek(r)) != -1 && c == 'o')
	{
		if ((err = read_obj_object(r, &object)) != Obj_No_Error)
			return (err);
		append_object(obj, object);
		obj_reader_next(r);
		obj_skip_ws(r, true);
	}
	if (obj->len == 0)
	{
		object = create_object(10);
		object.name = malloc(sizeof(char));
		object.name[0] = '\0';
		while ((c = obj_reader_peek(r) != -1) && c == 'g')
		{
			if ((err = read_groupe(r, &groupe)) != Obj_No_Error)
				return (err);
			if (append_groupe(&object, groupe) == false)
				return (Obj_Error_Malloc);
			obj_skip_ws(r, true);
		}
	}
	if (c != -1)
		return (Obj_Unexpected_Char);
	return (Obj_No_Error);
}
