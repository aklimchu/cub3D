#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.bash                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 10:47:12 by pleander          #+#    #+#              #
#    Updated: 2024/12/09 10:54:22 by pleander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "Running CUB3D tests.."

SCRIPTDIR=$(dirname "$0")
CUB3D="$SCRIPTDIR/../cub3D"
BROKEN_MAPS=$(ls "$SCRIPTDIR"/broken_maps/*.cub)

echo "Testing maps that should not work.."
for MAP in $BROKEN_MAPS
do
	echo -n -e "\x1b[31m"
	$CUB3D $MAP &> .tmp || (echo -n -e "\x1b[32m $MAP Failed successfully with error: \x1b[0m" && cat .tmp | tr '\n' ' ' && rm .tmp)
	echo ""
done
