/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:44:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/08 11:47:31 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_object		create_object(size_t capacity)
{
	return ((t_object) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_triangle))
	});
}

t_pos_array		create_pos_array(size_t capacity)
{
	return ((t_pos_array) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_pos))
	});
}

t_vertex_array		create_vertex_array(size_t capacity)
{
	return ((t_vertex_array) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_vertex))
	});
}

t_obj		create_obj(size_t capacity)
{
	return ((t_obj) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_groupe))
	});
}

t_groupe		create_groupe(size_t capacity)
{
	return ((t_groupe) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_object))
	});
}