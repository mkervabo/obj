/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:01:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/12 13:55:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct	s_reader
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	len;
	size_t	i;
	size_t	column;
	size_t	line;
}				t_reader;

typedef enum	e_obj_error
{
	No_Error,
	Error_Malloc,
	Missing_Name,
	Missing_Object,
	Invalid_Vertex,
	Invalid_Coord,
	Invalid_Coord_Dot,
	Missing_Line_Feed,
	Invalid_Pos,
	Invalid_Normal,
	Invalid_Triangle,
	Invalid_Triangle_Vertex,
	Unexpected_Char
}				t_obj_error;

typedef struct s_pos
{
	double x;
	double y;
}				t_pos;

typedef struct	s_pos_array
{
	size_t	len;
	size_t	capacity;
	t_pos	*inner;
}				t_pos_array;

typedef struct s_vertex
{
	double x;
	double y;
	double z;
}				t_vertex;

typedef struct	s_vertex_array
{
	size_t		len;
	size_t		capacity;
	t_vertex	*inner;
}				t_vertex_array;

typedef struct	s_f
{
	size_t v;
	size_t vt;
	size_t vn;
}				t_f;

typedef struct s_infos
{
	t_vertex_array	v;
	t_pos_array		vt;
	t_vertex_array	vn;
}				t_infos;


typedef struct	s_t_vertex
{
	t_vertex v;
	t_pos vt;
	t_vertex vn;
}				t_t_vertex;

typedef struct s_triangle
{
	t_t_vertex	a;
	t_t_vertex	b;
	t_t_vertex	c;
}				t_triangle;

typedef struct s_groupe
{
	char		*name;
	size_t		len;
	size_t		capacity;
	t_triangle	*inner;
}				t_groupe;

typedef struct	s_object
{
	char		*name;
	size_t		len;
	size_t		capacity;
	t_groupe	*inner;
}				t_object;

typedef struct s_obj
{
	size_t		len;
	size_t		capacity;
	t_object	*inner;
}				t_obj;

t_reader				create_reader(int fd, char *buffer, size_t buffer_size);
int16_t					reader_peek(t_reader *self);
void					reader_next(t_reader *self);

t_object				create_object(size_t capacity);
t_pos_array				create_pos_array(size_t capacity);
t_vertex_array			create_vertex_array(size_t capacity);
t_obj					create_obj(size_t capacity);
t_groupe				create_groupe(size_t capacity);

void					*ft_memcpy(void *dst, const void *src, size_t n);
bool					append_triangle(t_groupe *groupe, t_triangle t);
bool					append_pos(t_pos_array *pos, t_pos p);
bool					append_vertex(t_vertex_array *vertex, t_vertex v);
bool					append_object(t_obj *obj, t_object object);
bool					append_groupe(t_object *object, t_groupe groupe);
void					skip_ws(t_reader *r, bool newline);

t_obj_error				read_obj(t_reader *r, t_obj *obj);
t_obj_error				read_vertices(t_reader *r, t_vertex_array *v);
t_obj_error				read_pos(t_reader *r, t_pos_array *p);
t_obj_error				read_normal(t_reader *r, t_vertex_array *n);
t_obj_error				read_groupe(t_reader *r, t_groupe *groupe);
t_obj_error				read_object(t_reader *r, t_object *object);
t_obj_error				read_triangles(t_reader *r, t_groupe *groupe);


double					read_coord(t_reader *r, double *coord);
double					read_integer(t_reader *r, bool *s);

#endif