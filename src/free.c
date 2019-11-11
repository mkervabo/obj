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
