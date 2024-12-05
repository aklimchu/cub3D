/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:16:34 by pleander          #+#    #+#             */
/*   Updated: 2024/12/05 10:29:00 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "cub3D.h"
#include "libft.h"
#include "memlist.h"

static void	parse_texture_path(char **dst, char *line)
{
	char	*path_start;
	char	*path_end;

	while (ft_isspace(*line))
		line++;
	path_start = line;
	while (!ft_isspace(*line))
		line++;
	path_end = line;
	*dst = creserve(sizeof(char), path_end - path_start + 1);
	if (!*dst)
		error_exit(ERR_FATAL);
	ft_memcpy(*dst, path_start, path_end - path_start);
	while (ft_isspace(*line))
		line++;
	if (*line == '\n' || *line == '\0')
		return ;
	else
		error_exit(ERR_INVALID_FILE);
}

static int	line_is_empty(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
		return (1);
	else
		return (0);
}

/**
 * @brief Parses a line if it is of recongnized format, othweise
 * return -1
 *
 * @param line: line to parse
 * @param map: map
 * @return: 0 if parsed line, -1 otherwise
 */
int	parse_line(char *line, t_map *map)
{
	if (ft_isalpha(line[0]))
	{
		if (!ft_strncmp(line, "NO ", 3))
			parse_texture_path(&map->no_texture, line + 3);
		else if (!ft_strncmp(line, "SO ", 3))
			parse_texture_path(&map->so_texture, line + 3);
		else if (!ft_strncmp(line, "WE ", 3))
			parse_texture_path(&map->we_texture, line + 3);
		else if (!ft_strncmp(line, "EA ", 3))
			parse_texture_path(&map->ea_texture, line + 3);
		else if (!ft_strncmp(line, "F ", 2))
			parse_colors(&map->floor_color, line + 2);
		else if (!ft_strncmp(line, "C ", 2))
			parse_colors(&map->roof_color, line + 2);
		else
			error_exit(ERR_INVALID_FILE);
	}
	else if (line_is_empty(line))
		return (0);
	else
		return (-1);
	return (0);
}
