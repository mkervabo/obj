/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:58:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/30 19:17:21 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>
#include <stdio.h>

static t_obj_error	obj_read_vertex_type(t_obj_reader *r, t_obj *obj)
{
	t_obj_error err;
	int16_t		c;

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
	return (Obj_No_Error);
}

static t_obj_error	obj_read_type_groupe(t_obj_reader *r, t_obj *obj,
	t_obj_group *current_group)
{
	t_obj_error err;

	if (!(current_group = obj_append_group(obj, (t_obj_group) {
		.faces = obj_create_triangle_array(10)})))
		return (Obj_Error_Malloc);
	if ((err = obj_read_group(r, current_group)) != Obj_No_Error)
		return (err);
	return (Obj_No_Error);
}

static t_obj_error	obj_read_type(t_obj_reader *r, t_obj *obj,
	t_obj_group *current_group, t_obj_error err)
{
	int16_t		c;

	if ((c = obj_reader_peek(r)) == 'v')
		err = obj_read_vertex_type(r, obj);
	else if (c == 'f')
		err = obj_read_triangles(r, obj, current_group);
	else if (c == 'g')
		err = obj_read_type_groupe(r, obj, current_group);
	else if (c == 's' || c == 'm' || c == 'u' || c == 'o')
	{
		while ((c = obj_reader_peek(r)) != -1 && c != '\n')
			obj_reader_next(r);
		obj_skip_ws(r, true);
		err = Obj_No_Error;
	}
	else
		err = Obj_Unexpected_Char;
	return (err);
}

t_obj_error			obj_read(t_obj_reader *r, t_obj *obj)
{
	t_obj_error err;
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
		if ((err = obj_read_type(r, obj, current_group, err)) != Obj_No_Error)
			return (err);
	}
	if (c != -1)
		return (Obj_Unexpected_Char);
	return (Obj_No_Error);
}
