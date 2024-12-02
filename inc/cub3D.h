/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:15:40 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/29 15:09:06 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
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
	int			*map;
}				t_cub;

typedef struct s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}				t_rect;

void	handle_destroy(void *input);
void	free_everything(mlx_image_t *img, t_cub *cub, int exit_code);
void	handle_keypress(struct mlx_key_data key_data, void *input);
void	draw_cub(void *input);
void	initialize_values(t_cub *cub);
void	draw_map(t_cub *cub);
void	draw_rect(mlx_image_t *img, t_rect rect);
void	fill_rect(mlx_image_t *img, t_rect rect);

#endif /*CUB3D_H*/
