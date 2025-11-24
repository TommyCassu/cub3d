/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:50:06 by npederen          #+#    #+#             */
/*   Updated: 2025/11/23 22:52:35 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == '2'
		|| c == '3' || c == 'D' || is_player(c));
}

int	ft_verif_digit(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb_value(char *new_value, char **tab_value)
{
	if (new_value)
		free(new_value);
	if (!tab_value[0] || !tab_value[1] || !tab_value[2])
	{
		ft_free(tab_value);
		free(tab_value);
		return (1);
	}
	return (0);
}

int	check_rgb_limit(int r, int g, int b, char **tab_value)
{
	if (!(r >= 0 && r <= 255 && g >= 0 && g <= 255
			&& b >= 0 && b <= 255) || tab_value[3])
	{
		printf("Error map ! Please enter a valid RGB value\n");
		return (1);
	}
	return (0);
}
