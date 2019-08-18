/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:59:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/08/18 19:34:03 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static t_obj_error	read_f(t_obj_reader *r, t_f *vertex)
{
	char	c;
	bool	b;

	if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	vertex->v = (size_t)read_integer(r, &b) - 1;
	if (obj_reader_peek(r) != '/')
		return (Obj_Invalid_Triangle_Vertex);
	obj_reader_next(r);
	if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	vertex->vt = (size_t)read_integer(r, &b) - 1;
	if (obj_reader_peek(r) != '/')
		return (Obj_Invalid_Triangle_Vertex);
	obj_reader_next(r);
	if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	vertex->vn = (size_t)read_integer(r, &b) -1;
	return (Obj_No_Error);
}

static	t_obj_error	info_triangle(t_obj_reader *r, t_infos *info)
{
	t_obj_error		err;

	if ((err = read_vertices(r, &info->v)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, true);
	if ((err = read_pos(r, &info->vt)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, true);
	if ((err = read_normal(r, &info->vn)) != Obj_No_Error)
		return (err);
	return (Obj_No_Error);
}

static t_obj_error	read_triangle_vertex(t_infos *infos, t_t_vertex *vertex, t_f *f)
{
	if (f->v <= infos->v.len)
		vertex->v = infos->v.inner[f->v];
	else
		return (Obj_Invalid_Triangle_Vertex);
	if (f->vt <= infos->vt.len)
		vertex->vt = infos->vt.inner[f->vt];
	else
		return (Obj_Invalid_Triangle_Vertex);
	if (f->vn <= infos->vn.len)
		vertex->vn = infos->vn.inner[f->v];
	else
		return (Obj_Invalid_Triangle_Vertex);
	return (Obj_No_Error);
}
static t_obj_error	read_triangle(t_obj_reader *r, t_infos *infos, t_obj_triangle *triangle)
{
	t_f 		f;
	t_obj_error	err;

	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = read_f(r, &f)) != Obj_No_Error)
		return (err);
	if((err = read_triangle_vertex(infos, &triangle->a, &f)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = read_f(r, &f)) != Obj_No_Error)
		return (err);
	if((err = read_triangle_vertex(infos, &triangle->b, &f)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = read_f(r, &f)) != Obj_No_Error)
		return (err);;
	if((err = read_triangle_vertex(infos, &triangle->c, &f)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	return (Obj_No_Error);
}

t_obj_error			read_triangles(t_obj_reader *r, t_groupe *groupe)
{
	t_obj_error		err;
	t_infos			infos;
	t_obj_triangle	triangle;
	char			c;

	if ((err = info_triangle(r, &infos)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, true);
	while ((c = obj_reader_peek(r)) != -1 && c == 'f')
	{
		if ((err = read_triangle(r, &infos, &triangle)) != Obj_No_Error)
			return (err);
		if (!append_triangle(groupe, triangle))
			return (Obj_Error_Malloc);
		if (obj_reader_peek(r) != '\n')
		{
			obj_skip_ws(r, false);
			t_f 		f;
			triangle.b = triangle.c;
			if ((err = read_f(r, &f)) != Obj_No_Error)
				return (err);;
			if((err = read_triangle_vertex(&infos, &triangle.c, &f)) != Obj_No_Error)
				return (err);
			if (!append_triangle(groupe, triangle))
				return (Obj_Error_Malloc);
		}
		/*while (obj_reader_peek(r) != '\n')
			obj_reader_next(r);*/
		obj_skip_ws(r, true);
	}
	return (Obj_No_Error);
}
