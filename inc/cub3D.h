/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:15:40 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/11 12:54:41 by aklimchu         ###   ########.fr       */
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

# define SCREEN_W 3000
# define SCREEN_H 3000
# define DEGREE 0.0174533
# define WHITE 0xFFFFFFFF
# define GREY 0x808080FF
# define YELLOW 0xFFFF00FF
# define BLUE 0x0000FFFF
# define LIGHT_BLUE 0x00FFFFFF
# define RED 0xFF0000FF
# define GREEN 0x008000FF
# define BPP sizeof(int32_t)
# define DEGREE 0.0174533

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
	int		x;
	int		y;
}				t_coord;

typedef struct s_coord_f
{
	float	x;
	float	y;
}				t_coord_f;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}				t_player;

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
	t_coord		player_start; // row first
}	t_map;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t *img_map;
	mlx_image_t *img_game;
	t_coord		map_size;
	t_player	player;
	int			cell_size;
	t_map		*map;
	int			iter_limit;
	float dist_to_ray;
	int ray_loop;
	float ray_angle;
}				t_cub;

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
// events
void	handle_destroy(void *input);
void	handle_keypress(struct mlx_key_data key_data, void *input);
int		check_next_tile(t_cub *cub, float x, float y);
int		check_offset(float *num1, int *off1, float *num2, int *off2);
void	check_angle(t_cub *cub, bool x_dir);
void	key_left_event(t_cub *cub);
void	key_right_event(t_cub *cub);
// graphics
void	draw_cub(void *input);
void	draw_map(t_cub *cub);
void	draw_rect(mlx_image_t *img, t_rect rect);
void	draw_player(t_cub *cub);
void	raycasting(t_cub *cub);
void	fill_rect(mlx_image_t *img, t_rect rect);
void	draw_line(mlx_image_t *img, t_coord_f a, t_coord_f b, int color);
void	draw_textures(t_cub *cub, float dist_to_ray, int ray_loop, float ray_angle);
float	check_dist_to_ray(t_coord_f a, t_coord_f b, float angle);
// miscellaneous
void	initialize_values(t_cub *cub);
// exit
void	free_everything(t_cub *cub, int exit_code);
void	error_exit(char	*msg);

#endif /*CUB3D_H*/
