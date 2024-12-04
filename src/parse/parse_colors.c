/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:46 by pleander          #+#    #+#             */
/*   Updated: 2024/12/04 11:06:55 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3D.h"

static void	parse_single_color(uint8_t *dst, char *color_start, char *color_end)
{
	char	*str;
	int		color;

	if (!ft_isalnum(*color_start))
		error_exit(ERR_INVALID_FILE);
	str = ft_strndup(color_start, color_end - color_start);
	if (!str)
		return (error_exit(ERR_FATAL));
	color = ft_atoi(str);
	if (color < 0 || color > 255)
		error_exit(ERR_INVALID_FILE);
	*dst = (uint8_t)color;
}

void parse_colors(t_color *dst, char *line)
{
	char	*color_start;
	char	*color_end;

	while (ft_isspace(*line))
		line++;
	color_start = line;
	color_end = ft_strchr(color_start, ',');
	parse_single_color(&dst->r, color_start, color_end);
	color_start = ++color_end;
	color_end = ft_strchr(color_start, ',');
	parse_single_color(&dst->g, color_start, color_end);
	color_start = ++color_end;
	color_end = ft_strchr(color_start, '\n');
	parse_single_color(&dst->b, color_start, color_end);
}
