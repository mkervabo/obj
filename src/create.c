/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:44:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/27 14:24:03 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>

t_obj_uv_array			obj_create_uv_array(size_t capacity)
{
	return ((t_obj_uv_array) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_obj_uv))
	});
}

t_obj_vertex_array		obj_create_vertex_array(size_t capacity)
{
	return ((t_obj_vertex_array) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_obj_vertex))
	});
}

t_obj_triangle_array	obj_create_triangle_array(size_t capacity)
{
	return ((t_obj_triangle_array) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_obj_triangle))
	});
}

t_obj					obj_create(size_t capacity)
{
	return ((t_obj) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_obj_group))
	});
}
