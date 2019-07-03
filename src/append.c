/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:48:34 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/03 18:56:46 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

bool			append_triangle(t_triangle_array *triangle, t_triangle t)
{
	size_t	new_capacity;
	t_triangle	*new;

	if (triangle->len == triangle->capacity)
	{
		new_capacity = triangle->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_triangle))))
			return (false);
		ft_memcpy(new, triangle->inner, triangle->capacity);
		free(triangle->inner);
		triangle->inner = new;
		triangle->capacity = new_capacity;
	}
	triangle->inner[triangle->len++] = t;
	return (true);
}

bool			append_pos(t_pos_array *pos, t_pos p)
{
	size_t	new_capacity;
	t_pos	*new;

	if (pos->len == pos->capacity)
	{
		new_capacity = pos->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_pos))))
			return (false);
		ft_memcpy(new, pos->inner, pos->capacity);
		free(pos->inner);
		pos->inner = new;
		pos->capacity = new_capacity;
	}
	pos->inner[pos->len++] = p;
	return (true);
}

bool			append_vertex(t_vertex_array *vertex, t_vertex v)
{
	size_t	new_capacity;
	t_vertex	*new;

	if (vertex->len == vertex->capacity)
	{
		new_capacity = vertex->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_vertex))))
			return (false);
		ft_memcpy(new, vertex->inner, vertex->capacity);
		free(vertex->inner);
		vertex->inner = new;
		vertex->capacity = new_capacity;
	}
	vertex->inner[vertex->len++] = v;
	return (true);
}