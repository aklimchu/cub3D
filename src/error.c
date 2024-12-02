/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:56:02 by pleander          #+#    #+#             */
/*   Updated: 2024/12/02 14:47:16 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "memlist.h"
#include <stdlib.h>

void	error_exit(char	*msg)
{
	ft_dprintf(2, "Error\n%s\n", msg);
	memlist_release_all();
	exit(1);
}
