/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:59:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/30 15:06:47 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static t_obj_error	read_triangle_vertex_indexes(t_obj_reader *r, size_t *v,
	size_t *vt, size_t *vn)
{
	char	c;
	bool	b;

	if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	*v = (size_t)obj_read_integer(r, &b) - 1;
	if (obj_reader_peek(r) != '/')
		return (Obj_Invalid_Triangle_Vertex);
	obj_reader_next(r);
	if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	*vt = (size_t)obj_read_integer(r, &b) - 1;
	if (obj_reader_peek(r) != '/')
		return (Obj_Invalid_Triangle_Vertex);
	obj_reader_next(r);
	if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	*vn = (size_t)obj_read_integer(r, &b) - 1;
	return (Obj_No_Error);
}

static t_obj_error	read_triangle_vertex(t_obj_reader *r, t_obj *obj,
	t_obj_triangle_point *p)
{
	t_obj_error	err;
	size_t		v;
	size_t		vt;
	size_t		vn;

	if ((err = read_triangle_vertex_indexes(r, &v, &vt, &vn)) != Obj_No_Error)
		return (err);
	if (v <= obj->v.len)
		p->v = &obj->v.inner[v];
	else
		return (Obj_Invalid_Triangle_Vertex);
	if (vt <= obj->vt.len)
		p->vt = &obj->vt.inner[vt];
	else
		return (Obj_Invalid_Triangle_Vertex);
	if (vn <= obj->vn.len)
		p->vn = &obj->vn.inner[vn];
	else
		return (Obj_Invalid_Triangle_Vertex);
	return (Obj_No_Error);
}

static t_obj_error	obj_triangle_vertex(t_obj_reader *r, t_obj *obj,
	t_obj_group *group, t_obj_triangle *triangle)
{
	t_obj_error	err;

	if (!obj_append_triangle(&group->faces, *triangle))
		return (Obj_Error_Malloc);
	triangle->b = triangle->c;
	if ((err = read_triangle_vertex(r, obj, &triangle->c)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	return (Obj_No_Error);
}

t_obj_error			obj_read_triangles(t_obj_reader *r, t_obj *obj,
	t_obj_group *group)
{
	t_obj_error		err;
	t_obj_triangle	triangle;

	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = read_triangle_vertex(r, obj, &triangle.a)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = read_triangle_vertex(r, obj, &triangle.b)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = read_triangle_vertex(r, obj, &triangle.c)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	while (obj_reader_peek(r) != '\n' && obj_reader_peek(r) != -1)
	{
		if ((err = obj_triangle_vertex(r, obj, group, &triangle))
			!= Obj_No_Error)
			return (err);
	}
	if (!obj_append_triangle(&group->faces, triangle))
		return (Obj_Error_Malloc);
	obj_skip_ws(r, true);
	return (Obj_No_Error);
}
