/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:59:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/03 19:06:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static t_obj_error	read_triangle_vertex(t_reader *r, t_t_vertex *vertex)
{
	char	c;
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

t_obj_error			read_triangles(t_reader *r, t_triangle_array *triangles)
{
	size_t		i;
	char 		c;
	t_obj_error err;
	t_triangle	triangle;
	
	i = 0;
	while ((c = reader_peek(r)) != -1 && c == 'f')
	{
		reader_next(r);
		skip_ws(r, false);
		if ((err = read_triangle_vertex(r, &triangle.a)) != No_Error)
			return (err);
		skip_ws(r, false);
		if ((err = read_triangle_vertex(r, &triangle.b)) != No_Error)
			return (err);
		skip_ws(r, false);
		if ((err = read_triangle_vertex(r, &triangle.c)) != No_Error)
			return (err);
		if (!append_triangle(triangles, triangle))
			return (Error_Malloc);
		skip_ws(r, true);
	}
	if (i = 0)
		return (Invalid_Triangle);
	return (No_Error);
}