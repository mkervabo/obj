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
