#include "obj.h"
#include <stdio.h>

static t_obj_error control_type(t_obj_triangle_type *type, t_obj_triangle_type new_type)
{
	if (*type == Obj_No_Type)
		*type = new_type;
	else if (*type != new_type)
		return (Obj_Invalid_Type);
    return (Obj_No_Error);
}

t_obj_error read_vertex_type(t_obj_reader *r, size_t *v, t_obj_triangle_type *type)
{
    char        c;
    bool        b;
    t_obj_error err;

    if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	*v = (size_t)obj_read_integer(r, &b) - 1;
	if ((c = obj_reader_peek(r)) == ' ' || c == '\t' || c == '\r' || c == '\n')
	{
		if ((err = control_type(type, Obj_Vertex_Type)) != Obj_No_Error)
			return(err);
		return (Obj_No_Error);
	}
	else if (c != '/')
		return (Obj_Invalid_Triangle_Vertex);
    return(Obj_No_Error);
}

t_obj_error read_texture_type(t_obj_reader *r, size_t *vt, t_obj_triangle_type *type)
{
    char        c;
    bool        b;
    t_obj_error err;

    if ((c = obj_reader_peek(r)) == '/')
	{
		if ((err = control_type(type, Obj_Vertex_Normal_Type)) != Obj_No_Error)
			return(err);
	}
	else
	{
		if (c < '0' || c > '9')
			return (Obj_Invalid_Triangle_Vertex);
		*vt = (size_t)obj_read_integer(r, &b) - 1;
	}
	if ((c = obj_reader_peek(r)) == ' ' || c == '\t' || c == '\r' || c == '\n')
	{
		if ((err = control_type(type, Obj_Vertex_Texture_Type)) != Obj_No_Error)
			return(err);
		return (Obj_No_Error);
	}
	else if (obj_reader_peek(r) != '/')
		return (Obj_Invalid_Triangle_Vertex);
    return(Obj_No_Error);
}

t_obj_error read_normal_type(t_obj_reader *r, size_t *vn, t_obj_triangle_type *type)
{
    char        c;
    bool        b;
    t_obj_error err;

    if ((c = obj_reader_peek(r)) < '0' || c > '9')
		return (Obj_Invalid_Triangle_Vertex);
	*vn = (size_t)obj_read_integer(r, &b) - 1;
	if ((err = control_type(type, Obj_Vertex_Texture_Normal_Type)) != Obj_No_Error)
			return(err);
	return (Obj_No_Error);
}