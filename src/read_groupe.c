/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_groupe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 11:34:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/09 10:44:08 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.c"
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
	*str[i] = c;
	return (true);
}

static t_obj_error	read_name(t_reader *r, char **name)
{
	int16_t c;
	size_t size;
	size_t i;

	size = 10;
	if (!(*name = (char*)malloc(sizeof(char) * size)))
		return (Error_Malloc);
	i = 0;
	while ((c = reader_peek(r) != -1 && c != '\n'))
	{
		if (append_char(name, c, &size, i) == false)
			return (Error_Malloc);
		i++;
		reader_next(r);
	}
	if (append_char(name, '\0', &size, i) == false)
			return (Error_Malloc);
	return (No_Error);
}

t_obj_error			read_object(t_reader *r, t_object *object)
{
	t_obj_error	err;

	*object = create_object(10);
	skip_ws(r, false);
	if (reader_peek(r) == '\n')
		return (Missing_Name);
	if ((err = read_name(r, &object->name)) != No_Error)
		return (err);
	skip_ws(r, true);
	if ((err = read_triangles(r, object)) != No_Error)
		return (err);
	return (No_Error);
}

t_obj_error			read_groupe(t_reader *r, t_groupe *groupe)
{
	t_obj_error err;
	t_object	object;
	char		c;

	*groupe = create_groupe(10);
	skip_ws(r, false);
	if (reader_peek(r) == '\n')
		return (Missing_Name);
	if ((err = read_name(r, &groupe->name)) != No_Error)
		return (err);
	skip_ws(r, true);
	while ((c = reader_peek(r) != -1) && c == 'o')
	{
		if ((err = read_object(r, &object)) != No_Error)
			return (err);
		if (append_object(groupe, object) == false)
			return (Error_Malloc);
		skip_ws(r, true);
	}
	return (No_Error);
}