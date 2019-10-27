/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:58:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/27 14:26:25 by dde-jesu         ###   ########.fr       */
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

static t_obj_error	obj_read_vertex(t_obj_reader *r, t_obj_vertex_array *array)
{
	t_obj_error err;
	t_obj_vertex	v;

	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &v.x)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &v.y)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &v.z)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) != '\n')
		return (Obj_Missing_Line_Feed);
	obj_skip_ws(r, true);
	if (!obj_append_vertex(array, v))
		return (Obj_Error_Malloc);
	return (Obj_No_Error);
}

static t_obj_error		obj_read_uv(t_obj_reader *r, t_obj_uv_array *array)
{
	t_obj_error		err;
	t_obj_uv		uv;
	
	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &uv.u)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &uv.v)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) != '\n') {
		if ((err = obj_read_double(r, &uv.w)) != Obj_No_Error)
			return (err);
		obj_skip_ws(r, false);
	} else
		uv.w = 0;
	if (obj_reader_peek(r) != '\n')
		return (Obj_Missing_Line_Feed);
	obj_skip_ws(r, true);
	if (!obj_append_uv(array, uv))
		return (Obj_Error_Malloc);
	return (Obj_No_Error);
}


#include <stdio.h>

t_obj_error		obj_read(t_obj_reader *r, t_obj *obj)
{
	t_obj_error 	err;
	t_obj_group	*current_group;
	int16_t		c;

	*obj = obj_create(10);
	obj->v = obj_create_vertex_array(10);
	obj->vt = obj_create_uv_array(10);
	obj->vn = obj_create_vertex_array(10);
	if (!(current_group = obj_append_group(obj, (t_obj_group) {
		.name = "default",
		.faces = obj_create_triangle_array(10)
	})))
		return (Obj_Error_Malloc);
	obj_skip_ws(r, true);
	while ((c = obj_reader_peek(r)) != -1)
	{
		if ((c = obj_reader_peek(r)) == 'v')
		{
			obj_reader_next(r);
			if ((c = obj_reader_peek(r)) == ' ' || c == '\t' || c == '\r')
			{
				if ((err = obj_read_vertex(r, &obj->v)) != Obj_No_Error)
					return (err);
			}
			else if (c == 'n')
			{
				if ((err = obj_read_vertex(r, &obj->vn)) != Obj_No_Error)
					return (err);
			}
			else if (c == 't')
			{
				if ((err = obj_read_uv(r, &obj->vt)) != Obj_No_Error)
					return (err);
			}
		}
		else if (c == 'f')
		{
			if ((err = obj_read_triangles(r, obj, current_group)) != Obj_No_Error)
				return (err);
		}
		else if (c == 'g')
		{
			if (!(current_group = obj_append_group(obj, (t_obj_group) {
				.faces = obj_create_triangle_array(10)
			})))
				return (Obj_Error_Malloc);
			if ((err = obj_read_group(r, current_group)) != Obj_No_Error)
				return (err);
		}
		else if (c == 's' || c == 'm' || c == 'u' || c == 'o')
		{
			while ((c = obj_reader_peek(r)) != -1 && c != '\n')
				obj_reader_next(r);
			obj_skip_ws(r, true);
		}
		else
			return (Obj_Unexpected_Char);
	}
	if (c != -1)
		return (Obj_Unexpected_Char);
	return (Obj_No_Error);
}
