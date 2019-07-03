/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:01:09 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/03 19:13:17 by mkervabo         ###   ########.fr       */
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
	Invalid_Vertex,
	Invalid_Coord,
	Missing_Line_Feed,
	Invalid_Pos,
	Invalid_Normal,
	Invalid_Triangle,
	Invalid_Triangle_Vertex
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

typedef struct	s_t_vertex
{
	size_t v;
	size_t vt;
	size_t vn;
}				t_t_vertex;

typedef struct s_triangle
{
	t_t_vertex	a;
	t_t_vertex	b;
	t_t_vertex	c;
}				t_triangle;

typedef struct	s_triangle_array
{
	size_t		len;
	size_t		capacity;
	t_triangle	*inner;
}				t_triangle_array;

typedef struct s_obj
{
	char 		*name;
	t_triangle	*triangles;
}				t_obj;

t_reader				create_reader(int fd, char *buffer, size_t buffer_size);
int16_t					reader_peek(t_reader *self);
void					reader_next(t_reader *self);

t_triangle_array		create_triangle_array(size_t capacity);
t_pos_array				create_pos_array(size_t capacity);
t_vertex_array			create_vertex_array(size_t capacity);

bool					append_triangle(t_triangle_array *triangle, t_triangle t);
bool					append_pos(t_pos_array *pos, t_pos p);
bool					append_vertex(t_vertex_array *vertex, t_vertex v);

void					skip_ws(t_reader *r, bool newline);

t_obj_error				read_vertices(t_reader *r, t_vertex_array *v);
t_obj_error				read_pos(t_reader *r, t_pos_array *p);
t_obj_error				read_normal(t_reader *r, t_vertex_array *n);
t_obj_error				read_triange(t_reader *r, t_triangle_array *t);


double					read_coord(t_reader *r, double *coord);


#endif