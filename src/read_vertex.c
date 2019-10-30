/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:01:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/30 15:06:26 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_obj_error	obj_read_vertex(t_obj_reader *r, t_obj_vertex_array *array)
{
	t_obj_error		err;
	t_obj_vertex	v;

	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &v.x)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &v.y)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &v.z)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) != '\n')
		return (Obj_Missing_Line_Feed);
	obj_skip_ws(r, true);
	if (!obj_append_vertex(array, v))
		return (Obj_Error_Malloc);
	return (Obj_No_Error);
}

t_obj_error	obj_read_uv(t_obj_reader *r, t_obj_uv_array *array)
{
	t_obj_error		err;
	t_obj_uv		uv;

	obj_reader_next(r);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &uv.u)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if ((err = obj_read_double(r, &uv.v)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) != '\n')
	{
		if ((err = obj_read_double(r, &uv.w)) != Obj_No_Error)
			return (err);
		obj_skip_ws(r, false);
	}
	else
		uv.w = 0;
	if (obj_reader_peek(r) != '\n')
		return (Obj_Missing_Line_Feed);
	obj_skip_ws(r, true);
	if (!obj_append_uv(array, uv))
		return (Obj_Error_Malloc);
	return (Obj_No_Error);
}
