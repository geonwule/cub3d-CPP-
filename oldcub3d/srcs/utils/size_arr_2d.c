/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_arr_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:38:58 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 04:25:59 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	size_arr_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
