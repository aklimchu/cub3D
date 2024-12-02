/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:10:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/02 14:53:52 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	create_image(t_cub *cub);

int	main(int argc, char **argv)
{
	t_cub	cub;
	t_map	*map;

	if (argc != 2)
		error_exit("Incorrect amount of arguments");
	map = parse(argv[1]);
	create_image(&cub);
	initialize_values(&cub);
	mlx_loop_hook(cub.mlx, &draw_cub, &cub);
	if (!cub.img || (mlx_image_to_window(cub.mlx, cub.img, 0, 0) < 0))
		free_everything(cub.img, &cub, EXIT_FAILURE);
	mlx_close_hook(cub.mlx, &handle_destroy, &cub);
	mlx_key_hook(cub.mlx, &handle_keypress, &cub);
	mlx_loop(cub.mlx);
	free_everything(cub.img, &cub, EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}

static void	create_image(t_cub *cub)
{
	cub->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3D", 0);
	if (cub->mlx == NULL)
		exit (EXIT_FAILURE);
	cub->img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	if (cub->img == NULL)
		free_everything(NULL, cub, EXIT_FAILURE);
}
