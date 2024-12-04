/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:15:40 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/04 15:51:15 by pleander         ###   ########.fr       */
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

# define SCREEN_W 1500
# define SCREEN_H 1500

# define ERR_INVALID_FILE "Invalid input file"
# define ERR_FATAL "Fatal error"

typedef enum e_map_elems
{
	EMPTY,
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

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t *img;
	t_coord		map_size;
	t_coord		player;
	t_coord		cell_size;
	t_map_elems	**map;
}				t_cub;

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

void	handle_destroy(void *input);
void	free_everything(mlx_image_t *img, t_cub *cub, int exit_code);
void	handle_keypress(struct mlx_key_data key_data, void *input);
void	draw_cub(void *input);
void	initialize_values(t_cub *cub);
void	draw_map(t_cub *cub);
void	draw_rect(mlx_image_t *img, t_rect rect);
void	fill_rect(mlx_image_t *img, t_rect rect);
void	error_exit(char	*msg);
t_map	*parse(char *path);
int		parse_line(char *line, t_map *map);
void	parse_colors(t_color *dst, char *line);
void	read_map_line(char *line, t_list **lst);
void	parse_map(t_map *map, t_list **rows);

#endif /*CUB3D_H*/
