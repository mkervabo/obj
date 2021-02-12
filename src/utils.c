/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:59:56 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/30 15:06:33 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void			obj_skip_ws(t_obj_reader *r, bool newline)
{
	int16_t	c;

	while ((c = obj_reader_peek(r)) != -1 && (c == ' ' || c == '\t'
		|| c == '\r' || c == '#' || (newline && c == '\n')))
	{
		if (c == '#')
		{
			while ((c = obj_reader_peek(r)) != -1 && c != '\n')
				obj_reader_next(r);
		}
		obj_reader_next(r);
	}
}

char	*obj_error_msg(t_obj_error err)
{
	const char	*messages[] = {
	[Obj_Error_Malloc] = "Error Malloc",
	[Obj_Missing_Name] = "Missing Name",
	[Obj_Missing_Object] = "Missing Object",
	[Obj_Invalid_Vertex] = "Invalid Vertex",
	[Obj_Invalid_Double] = "Invalid Double",
	[Obj_Invalid_Double_Dot] = "Invalid Double Dot",
	[Obj_Missing_Line_Feed] = "Missing Line Feed",
	[Obj_Invalid_Uv] = "Invalid_Uv",
	[Obj_Invalid_Normal] = "Invalid Normal",
	[Obj_Invalid_Triangle] = "Invalid Triangle",
	[Obj_Invalid_Triangle_Vertex] = "Invalid Traingle Vertex",
	[Obj_Unexpected_Char] = "Unexpected Char",
	[Obj_Face_Without_Object] = "Face Without Object",
	[Obj_Invalid_Type] = "Invalid Type",
	};

	if (err > 0 && err <= sizeof(messages) / sizeof(*messages))
		return ((char *)messages[err]);
	else
		return (NULL);
}

