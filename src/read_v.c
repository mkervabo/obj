/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:51:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/08 14:36:30 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static t_obj_error	read_vertex(t_reader *r, t_vertex *v)
{
	t_obj_error err;

	reader_next(r);
	skip_ws(r, false);
	if ((err = read_coord(r, &v->x)) != No_Error);
		return (err);
	skip_ws(r, false);
	if ((err = read_coord(r, &v->y)) != No_Error);
		return (err);
	skip_ws(r, false);
	if ((err = read_coord(r, &v->z)) != No_Error);
		return (err);
	skip_ws(r, false);
	if (reader_peek(r) != '\n')
		return (Missing_Line_Feed);
	reader_next(r);
	return (No_Error);
}

t_obj_error		read_normal(t_reader *r, t_vertex_array *normals)
{

	int16_t		c;
	t_obj_error err;
	t_vertex	normal;
	
	while ((c = reader_peek(r)) != -1 && c == 'v')
	{
		reader_next(r);
		if (reader_peek(r) != 'n')
			return (Invalid_Pos);
		if ((err = read_vertex(r, &normal)) != No_Error)
			return(err);
		if (!append_vertex(normals, normal))
			return (Error_Malloc);
	}
	return (No_Error);
}

t_obj_error		read_pos(t_reader *r, t_pos_array *pos)
{
	int16_t		c;
	t_obj_error err;
	t_pos		p;
	
	while ((c = reader_peek(r)) != -1 && c == 'v')
	{
		reader_next(r);
		if (reader_peek(r) != 't')
			return (Invalid_Pos);
		reader_next(r);
		skip_ws(r, false);
		if ((err = read_coord(r, &p.x)) != No_Error);
			return (err);
		skip_ws(r, false);
		if ((err = read_coord(r, &p.y)) != No_Error);
			return (err);
		skip_ws(r, false);
		if (!append_pos(pos, p))
			return (Error_Malloc);
		if (reader_peek(r) != '\n')
			return (Missing_Line_Feed);
		reader_next(r);
	}
	return (No_Error);
}

t_obj_error	read_vertices(t_reader *r, t_vertex_array *vertices)
{
	int16_t		c;
	t_obj_error err;
	t_vertex	vertex;

	while ((c = reader_peek(r)) != -1 && c == 'v')
	{
		if ((err = read_vertex(r, &vertex)) != No_Error)
			return(err);
		if (!append_vertex(vertices, vertex))
			return (Error_Malloc);
	}
	return (No_Error);
}