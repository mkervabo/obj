/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:01:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/10/27 14:24:27 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct	s_obj_reader
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	len;
	size_t	i;
	size_t	column;
	size_t	line;
}				t_obj_reader;

typedef enum	e_obj_error
{
	Obj_No_Error,
	Obj_Error_Malloc,
	Obj_Missing_Name,
	Obj_Missing_Object,
	Obj_Invalid_Vertex,
	Obj_Invalid_Double,
	Obj_Invalid_Double_Dot,
	Obj_Missing_Line_Feed,
	Obj_Invalid_Uv,
	Obj_Invalid_Normal,
	Obj_Invalid_Triangle,
	Obj_Invalid_Triangle_Vertex,
	Obj_Unexpected_Char,
	Obj_Face_Without_Object
}				t_obj_error;

typedef struct s_obj_uv
{
	double u;
	double v;
	double w;
}				t_obj_uv;

typedef struct	s_obj_uv_array
{
	size_t		len;
	size_t		capacity;
	t_obj_uv	*inner;
}				t_obj_uv_array;

typedef struct s_obj_vertex
{
	double x;
	double y;
	double z;
}				t_obj_vertex;

typedef struct	s_obj_vertex_array
{
	size_t			len;
	size_t			capacity;
	t_obj_vertex	*inner;
}				t_obj_vertex_array;

typedef struct	s_obj_triangle_point
{
	t_obj_vertex	*v;
	t_obj_uv 		*vt;
	t_obj_vertex	*vn;
}				t_obj_triangle_point;

typedef struct s_obj_triangle
{
	t_obj_triangle_point	a;
	t_obj_triangle_point	b;
	t_obj_triangle_point	c;
}				t_obj_triangle;

typedef struct	s_obj_triangle_array
{
	size_t			len;
	size_t			capacity;
	t_obj_triangle	*inner;
}				t_obj_triangle_array;

typedef struct s_obj_group
{
	char			*name;
	t_obj_triangle_array	faces;
}				t_obj_group;

typedef struct s_obj
{
	size_t			len;
	size_t			capacity;
	t_obj_group		*inner;
	t_obj_vertex_array	v;
	t_obj_uv_array		vt;
	t_obj_vertex_array	vn;
}				t_obj;

t_obj_reader				obj_create_reader(int fd, char *buffer, size_t buffer_size);
int16_t					obj_reader_peek(t_obj_reader *self);
void					obj_reader_next(t_obj_reader *self);
void					obj_skip_ws(t_obj_reader *r, bool newline);

t_obj					obj_create(size_t capacity);
t_obj_uv_array				obj_create_uv_array(size_t capacity);
t_obj_vertex_array			obj_create_vertex_array(size_t capacity);
t_obj_triangle_array			obj_create_triangle_array(size_t capacity);

bool					obj_append_triangle(t_obj_triangle_array *array, t_obj_triangle t);
bool					obj_append_uv(t_obj_uv_array *array, t_obj_uv uv);
bool					obj_append_vertex(t_obj_vertex_array *vertex, t_obj_vertex v);
t_obj_group				*obj_append_group(t_obj *obj, t_obj_group group);

t_obj_error				obj_read(t_obj_reader *r, t_obj *obj);
t_obj_error				obj_read_triangles(t_obj_reader *r, t_obj *obj, t_obj_group *group);
t_obj_error				obj_read_group(t_obj_reader *r, t_obj_group *group);
double					obj_read_integer(t_obj_reader *r, bool *s);
t_obj_error				obj_read_double(t_obj_reader *r, double *d);
double					obj_read_integer(t_obj_reader *r, bool *s);

void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
