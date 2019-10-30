/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:48:34 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/30 10:07:26 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>

bool					obj_append_triangle(t_obj_triangle_array *array,
	t_obj_triangle t)
{
	size_t			new_capacity;
	t_obj_triangle	*new;

	if (array->len == array->capacity)
	{
		new_capacity = array->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_obj_triangle))))
			return (false);
		ft_memcpy(new, array->inner, array->capacity * sizeof(t_obj_triangle));
		free(array->inner);
		array->inner = new;
		array->capacity = new_capacity;
	}
	array->inner[array->len++] = t;
	return (true);
}

bool					obj_append_uv(t_obj_uv_array *array, t_obj_uv uv)
{
	size_t		new_capacity;
	t_obj_uv	*new;

	if (array->len == array->capacity)
	{
		new_capacity = array->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_obj_uv))))
			return (false);
		ft_memcpy(new, array->inner, array->capacity * sizeof(t_obj_uv));
		free(array->inner);
		array->inner = new;
		array->capacity = new_capacity;
	}
	array->inner[array->len++] = uv;
	return (true);
}

bool					obj_append_vertex(t_obj_vertex_array *array,
	t_obj_vertex v)
{
	size_t			new_capacity;
	t_obj_vertex	*new;

	if (array->len == array->capacity)
	{
		new_capacity = array->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_obj_vertex))))
			return (false);
		ft_memcpy(new, array->inner, array->capacity * sizeof(t_obj_vertex));
		free(array->inner);
		array->inner = new;
		array->capacity = new_capacity;
	}
	array->inner[array->len++] = v;
	return (true);
}

t_obj_group				*obj_append_group(t_obj *obj, t_obj_group group)
{
	size_t		new_capacity;
	t_obj_group	*new;

	if (obj->len == obj->capacity)
	{
		new_capacity = obj->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_obj_group))))
			return (NULL);
		ft_memcpy(new, obj->inner, obj->capacity * sizeof(t_obj_group));
		free(obj->inner);
		obj->inner = new;
		obj->capacity = new_capacity;
	}
	obj->inner[obj->len] = group;
	return (obj->inner + obj->len++);
}
