/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:10:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 11:39:38 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	create_images(t_cub *cub);
static void	add_shading(mlx_texture_t *texture);
static void	create_bg_buffer(t_cub *cub);

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		error_exit("Incorrect amount of arguments");
	cub.map = parse(argv[1]);
	load_textures(&cub);
	add_shading(cub.textures.n);
	add_shading(cub.textures.e);
	create_images(&cub);
	initialize_values(&cub);
	create_bg_buffer(&cub);
	mlx_loop_hook(cub.mlx, &draw_cub, &cub);
	//mlx_close_hook(cub.mlx, &handle_destroy, &cub);
	mlx_key_hook(cub.mlx, &handle_keypress, &cub);
	mlx_loop(cub.mlx);
	free_everything(&cub, EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}

static void	create_images(t_cub *cub)
{
	int32_t	w;
	int32_t	h;

	cub->mlx = mlx_init(800, 600, "cub3D", 1);
	if (cub->mlx == NULL)
		exit (EXIT_FAILURE);
	mlx_get_monitor_size(0, &w, &h);
	mlx_set_window_size(cub->mlx, w, h);
	//mlx_set_setting(MLX_FULLSCREEN, true);
	cub->img_map = mlx_new_image(cub->mlx, MM_W, MM_H);
	if (cub->img_map == NULL)
		free_everything(cub, EXIT_FAILURE);
	cub->img_game = mlx_new_image(cub->mlx, w, h);
	if (cub->img_game == NULL)
		free_everything(cub, EXIT_FAILURE);
	cub->img_fps = NULL;
	if (!cub->img_map || (mlx_image_to_window(cub->mlx, \
		cub->img_map, 0, 0) < 0))
	{
		free_everything(cub, EXIT_FAILURE);
	}
	if (!cub->img_game || (mlx_image_to_window(cub->mlx, \
		cub->img_game, 0, 0) < 0))
	{
		free_everything(cub, EXIT_FAILURE);
	}
	mlx_set_instance_depth(cub->img_map->instances, 1);
	mlx_set_instance_depth(cub->img_game->instances, 0);
}

static void	add_shading(mlx_texture_t *texture)
{
	float	shading_factor;
	int		i;
	uint8_t	*pixels;
	int		pixel_count;
	uint8_t	*pixel;

	shading_factor = 0.7;
	i = 0;
	pixels = texture->pixels;
	pixel_count = texture->width * texture->height;
	while (i < pixel_count)
	{
		pixel = &pixels[i * BPP];
		pixel[0] = (uint8_t)(pixel[0] * shading_factor);
		pixel[1] = (uint8_t)(pixel[1] * shading_factor);
		pixel[2] = (uint8_t)(pixel[2] * shading_factor);
		if (BPP == 4)
			pixel[3] = pixel[3];
		i++;
	}
}

static void	create_bg_buffer(t_cub *cub)
{
	size_t	i;
	size_t	game_size;

	game_size = cub->img_game->height * cub->img_game->width * BPP;
	cub->bg_buffer = reserve(game_size);
	if (!cub->bg_buffer)
		error_exit(ERR_FATAL);
	i = 0;
	while (i < game_size / 2)
	{
		mlx_draw_pixel(&cub->bg_buffer[i], get_rgba(cub->map->roof_color));
		i += 4;
	}
	while (i < game_size)
	{
		mlx_draw_pixel(&cub->bg_buffer[i], get_rgba(cub->map->floor_color));
		i += 4;
	}
}
