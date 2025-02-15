/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:23:32 by pleander          #+#    #+#             */
/*   Updated: 2024/12/17 13:40:36 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"
#include "memlist.h"

void	check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			error_exit(ERR_INVALID_FILE);
		i++;
	}
}

static int	get_longest_row(t_list **rows)
{
	t_list	*row;
	int		longest;
	int		len;

	longest = 0;
	row = *rows;
	while (row)
	{
		len = ft_strlen(row->content);
		if (((char *)row->content)[len - 1] == '\n')
			len--;
		if (len > longest)
			longest = len;
		row = row->next;
	}
	return (longest);
}

static void	parse_map_row(t_map_elems *dst, int size, char *row)
{
	int	i;

	i = 0;
	while (row[i] && row[i] != '\n')
	{
		if (row[i] == ' ')
			dst[i++] = PADDING;
		else if (row[i] == '0')
			dst[i++] = EMPTY;
		else if (row[i] == '1')
			dst[i++] = WALL;
		else if (row[i] == 'N')
			dst[i++] = START_NO;
		else if (row[i] == 'S')
			dst[i++] = START_SO;
		else if (row[i] == 'W')
			dst[i++] = START_WE;
		else if (row[i] == 'E')
			dst[i++] = START_EA;
		else
			error_exit(ERR_INVALID_FILE);
	}
	while (i < size)
		dst[i++] = PADDING;
	dst[i] = END_ROW;
}

int	row_is_empty(t_map_elems *row)
{
	int	i;

	i = 0;
	while (row[i] != END_ROW)
	{
		if (row[i] != PADDING)
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_map *map, t_list **rows)
{
	size_t	i;
	t_list	*cur;
	int		reached_map_end;

	reached_map_end = 0;
	map->map_cols = (size_t)get_longest_row(rows);
	map->map_rows = (size_t)ft_lstsize(*rows);
	map->map = creserve(map->map_rows + 1, sizeof(void *));
	if (!map->map)
		error_exit(ERR_FATAL);
	i = 0;
	cur = *rows;
	while (i < map->map_rows && cur)
	{
		map->map[i] = creserve(map->map_cols + 1, sizeof(t_map_elems));
		if (!map->map[i])
			error_exit(ERR_FATAL);
		parse_map_row(map->map[i], map->map_cols, (char *)cur->content);
		if (!reached_map_end && row_is_empty(map->map[i]))
			reached_map_end = 1;
		if (reached_map_end && !row_is_empty(map->map[i]))
			error_exit("Extra content after map");
		cur = cur->next;
		i++;
	}
}
