/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:56:52 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/30 12:05:16 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

double			obj_read_integer(t_obj_reader *r, bool *s)
{
	double	num;
	int16_t	c;

	*s = false;
	num = 0;
	c = obj_reader_peek(r);
	if (c == '-')
		*s = true;
	if (c == '-' || c == '+')
		obj_reader_next(r);
	while ((c = obj_reader_peek(r)) != -1 && ((c >= '0' && c <= '9')
		|| c == '_'))
	{
		if (c >= '0' && c <= '9')
			num = num * 10 + (c - 48);
		obj_reader_next(r);
	}
	return (num);
}

static double	obj_read_float_part(t_obj_reader *r)
{
	double	num;
	size_t	i;
	int16_t c;

	i = 0;
	num = 0;
	while ((c = obj_reader_peek(r)) != -1 && ((c >= '0' && c <= '9')
		|| c == '_'))
	{
		if (c >= '0' && c <= '9')
		{
			num = num * 10 + (c - 48);
			i++;
		}
		obj_reader_next(r);
	}
	while (i-- > 0)
		num *= 0.1;
	return (num);
}

t_obj_error		obj_read_double(t_obj_reader *r, double *d)
{
	bool	sign;
	int16_t	c;

	c = obj_reader_peek(r);
	if ((c < '0' || c > '9') && c != '-' && c != '+')
		return (Obj_Invalid_Double);
	*d = obj_read_integer(r, &sign);
	if (obj_reader_peek(r) != '.')
		return (Obj_Invalid_Double_Dot);
	obj_reader_next(r);
	c = obj_reader_peek(r);
	if ((c < '0' || c > '9') && c != '-' && c != '+')
		return (Obj_Invalid_Double);
	*d = (sign ? -1 : 1) * (*d + obj_read_float_part(r));
	return (Obj_No_Error);
}
