/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_groupe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 11:34:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/08/18 18:03:17 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>


void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*c_src = src;
	char		*c_dst;

	c_dst = dst;
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}

static bool			append_char(char **str, char c, size_t *size , size_t i)
{
	size_t	new_size;
	char 	*new;

	if (i == *size)
	{
		new_size = *size * 2;
		if (!(new = malloc(new_size * sizeof(char))))
			return (false);
		ft_memcpy(new, *str, *size);
		free(*str);
		*str = new;
		*size = new_size;
	}
	(*str)[i] = c;
	return (true);
}

static t_obj_error	read_name(t_obj_reader *r, char **name)
{
	int16_t c;
	size_t size;
	size_t i;

	size = 10;
	if (!(*name = (char*)malloc(sizeof(char) * size)))
		return (Obj_Error_Malloc);
	i = 0;
	while ((c = obj_reader_peek(r)) != -1 && c != '\n')
	{
		if (append_char(name, c, &size, i) == false) 
			return (Obj_Error_Malloc);
		i++;
		obj_reader_next(r);
	}
	if (append_char(name, '\0', &size, i) == false)
			return (Obj_Error_Malloc);
	return (Obj_No_Error);
}

t_obj_error			read_groupe(t_obj_reader *r, t_groupe *groupe)
{
	t_obj_error	err;

	*groupe = create_groupe(10);
	obj_reader_next(r);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) == '\n')
		return (Obj_Missing_Name);
	if ((err = read_name(r, &groupe->name)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, true);
	if ((err = read_triangles(r, groupe)) != Obj_No_Error)
		return (err);
	return (Obj_No_Error);
}

t_obj_error			read_obj_object(t_obj_reader *r, t_obj_object *object)
{
	t_obj_error err;
	t_groupe	groupe;
	char		c;

	*object = create_object(10);
	obj_skip_ws(r, false);
	if (obj_reader_peek(r) == '\n')
		return (Obj_Missing_Name);
	if ((err = read_name(r, &object->name)) != Obj_No_Error)
		return (err);
	obj_skip_ws(r, true);
	while ((c = obj_reader_peek(r)) != -1 && c == 'g')
	{
		if ((err = read_groupe(r, &groupe)) != Obj_No_Error)
			return (err);
		if (append_groupe(object, groupe) == false)
			return (Obj_Error_Malloc);
		obj_skip_ws(r, true);
	}
	if (object->len == 0)
	{
		groupe = create_groupe(10);
		groupe.name = malloc(sizeof(char));
		groupe.name[0] = '\0';
		if ((err = read_triangles(r, &groupe)) != Obj_No_Error)
			return (err);
	}
	return (Obj_No_Error);
}
