/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:15:40 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 15:06:19 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/memlist.h"
# include "../MLX42/include/MLX42.h"
# include "../MLX42/include/MLX42_Int.h"
# include <stdio.h> //for printf
# include <stdlib.h> //for exit status and malloc
# include <errno.h> // for errno (error identifiers)
# include <fcntl.h> // for open
# include <unistd.h> // for close
# include <sys/time.h> // for gettimeofday
# include <stdbool.h> // for boolean data type
# include <math.h> // for mathematical functions

# define MM_W 300
# define MM_H 300
# define DEGREE 0.0174533
# define WHITE 0xFFFFFFFF
# define GREY 0x808080FF
# define YELLOW 0xFFFF00FF
# define BLUE 0x0000FFFF
# define LIGHT_BLUE 0x00FFFFFF
# define RED 0xFF0000FF
# define GREEN 0x008000FF
# define BPP sizeof(int32_t) // not according to Norm?
# define CELL_SIZE 64
# define MAP_CELL_SIZE 25
# define ROTATION_SPEED 2
# define PLAYER_SPEED 200
# define MOVEMENT_OFFSET 0.5

// ERROR MESSAGES
# define ERR_INVALID_FILE "Invalid input file"
# define ERR_FATAL "Fatal error"

typedef enum e_map_elems
{
	EMPTY = 1,
	WALL = 2,
	PADDING = 3,
	START_NO = 4,
	START_SO = 5,
	START_WE = 6,
	START_EA = 7,
	END_ROW = 8
}	t_map_elems;

typedef struct s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct s_coord_f
{
	double	x;
	double	y;
}				t_coord_f;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	angle;
}				t_player;

typedef struct s_current
{
	double		dist_to_ray;
	t_coord_f	offset;
	t_coord_f	r_pos;
	t_coord		map_pos;
	int			ray_iter;
	double		ray_angle;
	double		neg_inv_tan;
	double		neg_tan;
}				t_current;

typedef struct s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}				t_rect;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color;

typedef struct s_map
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_color		floor_color;
	t_color		roof_color;
	t_map_elems	**map;
	size_t		map_cols;
	size_t		map_rows;
	t_coord		player_start;
}	t_map;

typedef struct s_textures
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
}	t_textures;

typedef struct s_key_state {
    bool w;
    bool a;
    bool s;
    bool d;
    bool left;
    bool right;
}	t_key_state;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img_map;
	mlx_image_t	*img_game;
	mlx_image_t	*img_fps;
	t_textures	textures;
	t_coord		map_size;
	t_player	player;
	t_map		*map;
	t_key_state	keys;
	int		iter_limit;
	int		ray_loop;
	size_t		n_rays;
	size_t		vertical_lines;
	double		dist_to_ray;
	double		ray_angle;
	uint8_t		*bg_buffer;
}				t_cub;

typedef struct s_draw_context
{
	double	dist_to_wall;
	double	ray_angle;
	int	iteration;
	int	side;
}	t_draw_context;

typedef struct s_texture_context
{
	t_draw_context	*dc;
	t_cub		*cub;
	mlx_texture_t	*texture;
	double		texture_x;
	double		y_scale;
	int		y_start;
	int		y_end;
	int		x;
}	t_texture_context;

// FUNCTIONS
// parsing
t_map		*parse(char *path);
void		parse_colors(t_color *dst, char *line);
void		read_map_line(char *line, t_list **lst);
void		parse_map(t_map *map, t_list **rows);
char		*get_token(t_map_elems tok);
void		show_map(t_map *map);
int			parse_line(char *line, t_map *map);
t_map_elems	get_tile(size_t row, size_t col, t_map *map);
void		check_map(t_map *map);
void		check_tiles(t_map *map);
t_map_elems	get_tile_xy(size_t x, size_t y, t_map *map);
uint32_t	get_rgba(t_color c);
// events
//void		handle_destroy(void *input);
void		handle_keypress(struct mlx_key_data key_data, void *input);
int			check_next_tile(t_cub *cub, double x, double y);
void		check_angle(bool x_dir, double *dx, double *dy);
// graphics
void		draw_cub(void *input);
void		draw_map(t_cub *cub);
void		draw_rect(mlx_image_t *img, t_rect rect);
void		draw_player(t_cub *cub);
void		raycasting(t_cub *cub);
void		fill_rect(mlx_image_t *img, t_rect rect);
void		draw_line(mlx_image_t *img, t_coord_f a, t_coord_f b, int color);
void		draw_game(t_cub *cub, t_draw_context dc);
void		load_textures(t_cub *cub);
double		check_dist_to_ray(t_coord_f a, t_coord_f b, double angle);
void		iter_loop(t_cub *cub, t_current *h, double *ray_x, double *ray_y);
void		update_no_iter(t_cub *cub, t_current *h);
double		normalize_angle(double angle);
void		draw_cell(t_cub *cub, t_coord cell, t_coord_f current);
void		update_player(t_cub *cub);
// miscellaneous
void		initialize_values(t_cub *cub);
// exit
void		free_everything(t_cub *cub, int exit_code);
void		error_exit(char	*msg);

#endif /*CUB3D_H*/
