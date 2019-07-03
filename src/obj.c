/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:58:21 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/03 13:05:45 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void			skip_ws(t_reader *r, bool newline)
{
	int16_t	c;

	while ((c = reader_peek(r)) != -1 && (c == ' ' || c == '\t' || c == '#'
				|| (newline && c == '\n')))
	{
		if (c == '#')
		{
			while ((c = reader_peek(r)) != -1 && c != '\n')
				reader_next(r);
		}
		reader_next(r);
	}
}

t_obj_error		read_obj(t_reader *r, t_obj **obj)
{
	t_obj_error err;

	if (reader_peek(r) == '#')
		skip_ws(r, true);

}