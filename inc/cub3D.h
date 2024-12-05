/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:15:40 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 12:07:57 by aklimchu         ###   ########.fr       */
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

# define SCREEN_W 1500
# define SCREEN_H 1500
# define DEGREE 0.0174533

// ERROR MESSAGES
# define ERR_INVALID_FILE "Invalid input file"
# define ERR_FATAL "Fatal error"

typedef enum e_map_elems
{
	EMPTY = 1,
	WALL,
	PADDING,
	START_NO,
	START_SO,
	START_WE,
	START_EA
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
}	t_map;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t *img_map;
	mlx_image_t *img_game;
	t_coord		map_size;
	t_player	player;
	t_coord		cell_size;
	t_map		*map;
}				t_cub;

// FUNCTIONS
// parsing
t_map	*parse(char *path);
void	parse_colors(t_color *dst, char *line);
void	read_map_line(char *line, t_list **lst);
void	parse_map(t_map *map, t_list **rows);
char	*get_token(t_map_elems tok);
void	show_map(t_map_elems **map);
int		parse_line(char *line, t_map *map);
// events
void	handle_destroy(void *input);
void	handle_keypress(struct mlx_key_data key_data, void *input);
// graphics
void	draw_cub(void *input);
void	draw_map(t_cub *cub);
void	draw_rect(mlx_image_t *img, t_rect rect);
void	draw_player(t_cub *cub);
void	raycasting(t_cub *cub);
void	fill_rect(mlx_image_t *img, t_rect rect);
void	draw_line(mlx_image_t *img, t_coord_f a, t_coord_f b, int color);
void	draw_game(t_cub *cub, float dist_to_ray, int ray_loop, float ray_angle);
// miscellaneous
void	initialize_values(t_cub *cub);
// exit
void	free_everything(t_cub *cub, int exit_code);
void	error_exit(char	*msg);

#endif /*CUB3D_H*/
