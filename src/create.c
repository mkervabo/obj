/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:44:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/03 18:46:50 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_triangle_array		create_triangle_array(size_t capacity)
{
	return ((t_triangle_array) {
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