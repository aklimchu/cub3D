/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:46 by pleander          #+#    #+#             */
/*   Updated: 2024/12/17 13:02:05 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "cub3D.h"

static void	parse_single_color(uint8_t *dst, char *color_start, char *color_end)
{
	char	*str;
	int		color;

	if (!color_start || !color_end)
		error_exit("Invalid color");
	if (!ft_isalnum(*color_start))
		error_exit("Invalid color");
	str = ft_strndup(color_start, color_end - color_start);
	if (!str)
		return (error_exit(ERR_FATAL));
	color = ft_atoi(str);
	free(str);
	if (color < 0 || color > 255)
		error_exit("Invalid color");
	*dst = (uint8_t)color;
}

char	*skip_whitespace(char *color_start)
{
	while (ft_isspace(*color_start))
		color_start++;
	return (color_start);
}

void	parse_colors(t_color *dst, char *line)
{
	char	*color_start;
	char	*color_end;

	while (ft_isspace(*line))
		line++;
	color_start = line;
	color_end = ft_strchr(color_start, ',');
	parse_single_color(&dst->r, skip_whitespace(color_start), color_end);
	color_start = ++color_end;
	color_end = ft_strchr(color_start, ',');
	parse_single_color(&dst->g, skip_whitespace(color_start), color_end);
	color_start = ++color_end;
	color_end = ft_strchr(color_start, '\n');
	parse_single_color(&dst->b, skip_whitespace(color_start), color_end);
	dst->a = 255;
}

uint32_t	get_rgba(t_color c)
{
	return ((uint32_t)c.r << 24 | c.g << 16 | c.b << 8 | c.a);
}
