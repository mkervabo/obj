/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:51:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/08/18 19:27:59 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdio.h>

static t_obj_error	read_vertex(t_obj_reader *r, t_vertex *v)
{
	t_obj_error err;

	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = read_coord(r, &v->x)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = read_coord(r, &v->y)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = read_coord(r, &v->z)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) != '\n')
		return (Obj_Missing_Line_Feed);
	obj_reader_next(r);
	return (Obj_No_Error);
}

t_obj_error		read_normal(t_obj_reader *r, t_vertex_array *normals)
{

	int16_t		c;
	t_obj_error err;
	t_vertex	normal;
	
	*normals = create_vertex_array(10);
	while ((c = obj_reader_peek(r)) != -1 && c == 'v')
	{
		obj_reader_next(r);
		if (obj_reader_peek(r) != 'n')
			return (Obj_Invalid_Pos);
		if ((err = read_vertex(r, &normal)) != Obj_No_Error)
			return(err);
		if (!append_vertex(normals, normal))
			return (Obj_Error_Malloc);
	}
	return (Obj_No_Error);
}

t_obj_error		read_pos(t_obj_reader *r, t_pos_array *pos)
{
	int16_t		c;
	t_obj_error err;
	t_pos		p;
	
	*pos = create_pos_array(10);
	while ((c = obj_reader_peek(r)) != -1 && c == 'v')
	{
		obj_reader_next(r);
		if (obj_reader_peek(r) != 't')
			return (Obj_Invalid_Pos);
		obj_reader_next(r);
		obj_skip_ws(r, false);
		if ((err = read_coord(r, &p.x)) != Obj_No_Error)
			return (err);
		obj_skip_ws(r, false);
		if ((err = read_coord(r, &p.y)) != Obj_No_Error)
			return (err);
		obj_skip_ws(r, false);
		if (!append_pos(pos, p))
			return (Obj_Error_Malloc);
		if (obj_reader_peek(r) != '\n')
			return (Obj_Missing_Line_Feed);
		obj_reader_next(r);
	}
	return (Obj_No_Error);
}

t_obj_error	read_vertices(t_obj_reader *r, t_vertex_array *vertices)
{
	int16_t		c;
	t_obj_error err;
	t_vertex	vertex;

	*vertices = create_vertex_array(10);
	while ((c = obj_reader_peek(r)) != -1 && c == 'v')
	{
		if ((err = read_vertex(r, &vertex)) != Obj_No_Error)
			return(err);
		if (!append_vertex(vertices, vertex))
			return (Obj_Error_Malloc);
	}
	return (Obj_No_Error);
}
