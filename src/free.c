/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:07:02 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/13 20:07:03 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <stdlib.h>

int	obj_free(t_obj *obj)
{
	size_t	i;

	i = 0;
	while (i < obj->len)
	{
		free(obj->inner[i].name);
		free(obj->inner[i].faces.inner);
		i++;
	}
	free(obj->v.inner);
	free(obj->vt.inner);
	free(obj->vn.inner);
	free(obj->inner);
	return (0);
}
