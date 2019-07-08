/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:59:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/08 14:36:12 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static t_obj_error	read_f(t_reader *r, t_f *vertex)
{
	int16_t	c;
	bool	b;

	reader_next(r);
	skip_ws(r, false);
	if ((reader_peek(r) < '0' || c > '9'))
		return (Invalid_Triangle_Vertex);
	vertex->v = (size_t)read_integer(r, &b) - 1;
	if (reader_peek(r) != '/')
		return (Invalid_Triangle_Vertex);
	reader_next(r);
	if ((reader_peek(r) < '0' || c > '9'))
		return (Invalid_Triangle_Vertex);
	vertex->vt = (size_t)read_integer(r, &b) - 1;
	if (reader_peek(r) != '/')
		return (Invalid_Triangle_Vertex);
	reader_next(r);
	if ((reader_peek(r) < '0' || c > '9'))
		return (Invalid_Triangle_Vertex);
	vertex->vn = (size_t)read_integer(r, &b) -1;
	return (No_Error);
}

static	t_obj_error	info_triangle(t_reader *r, t_infos *info)
{
	t_obj_error		err;

	if ((err = read_vertices(r, &info->v)) != No_Error)
		return (err);
	if ((err = read_pos(r, &info->vt)) != No_Error)
		return (err);
	if ((err = read_normal(r, &info->vn)) != No_Error)
		return (err);
	return (No_Error);
}

static t_obj_error	read_triangle_vertex(t_infos *infos, t_t_vertex *vertex, t_f *f)
{
	if (f->v <= infos->v.len)
		vertex->v = infos->v.inner[f->v];
	else
		return (Invalid_Triangle_Vertex);
	if (f->vt <= infos->vt.len)
		vertex->vt = infos->vt.inner[f->vt];
	else
		return (Invalid_Triangle_Vertex);
	if (f->vn <= infos->vn.len)
		vertex->vn = infos->vn.inner[f->v];
	else
		return (Invalid_Triangle_Vertex);
	return (No_Error);
}
static t_obj_error	read_triangle(t_reader *r, t_infos *infos, t_triangle *triangle)
{
	t_f 		f;
	t_obj_error	err;

	reader_next(r);
	skip_ws(r, false);
	if ((err = read_f(r, &f)) != No_Error)
		return (err);
	if((err = read_triangle_vertex(infos, &triangle->a, &f)) != No_Error)
		return (err);
	skip_ws(r, false);
	if ((err = read_f(r, &f)) != No_Error)
		return (err);
	if((err = read_triangle_vertex(infos, &triangle->b, &f)) != No_Error)
		return (err);
	skip_ws(r, false);
	if ((err = read_f(r, &f)) != No_Error)
		return (err);;
	if((err = read_triangle_vertex(infos, &triangle->c, &f)) != No_Error)
		return (err);
	return (No_Error);
}

t_obj_error			read_triangles(t_reader *r, t_object *object)
{
	t_obj_error	err;
	t_infos		infos;
	t_triangle	triangle;
	int16_t		c;

	if ((err = info_triangle(r, &infos) != No_Error))
		return (err);
	*object = create_object(10);
	while ((c = reader_peek(r)) != -1 && c == 'f')
	{
		if ((err = read_triangle(r, &infos, &triangle)) != No_Error)
			return (err);
		if (!append_triangle(object, triangle))
			return (Error_Malloc);
		skip_ws(r, true);
	}
	return (No_Error);
}