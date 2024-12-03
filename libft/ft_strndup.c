/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:40:12 by pleander          #+#    #+#             */
/*   Updated: 2024/04/18 15:32:59 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "include/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	size;
	char	*copy;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	size = n;
	len = ft_strlen(s1);
	if (len < size)
		size = len;
	copy = ft_calloc(size + 1, sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}
