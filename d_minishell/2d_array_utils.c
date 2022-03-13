/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:40:26 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/13 08:51:00 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	size_of_2d_array(char **array)
{
	size_t	size;

	size = 0;
	if (array == NULL)
		return (0);
	while (array[size])
		size++;
	return (size);
}

int	find_in_2d_array(char **array, char *str)
{
	int	i;

	if (array == NULL || str == NULL)
		return (-1);
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(str, array[i], ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**add_element_2d_array_last(char **array, char *elem)
{
	if (array == NULL)
		return (NULL);
	if (elem == NULL)
		return (array);
	array = add_element_2d_array(array, elem, size_of_2d_array(array));
	return (array);
}

char	**init_2d_array(void)
{
	char	**init;

	init = malloc(sizeof(char *));
	*init = NULL;
	return (init);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i])
			free(array[i++]);
		free(array);
	}
}
