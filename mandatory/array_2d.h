/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:21:16 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 14:49:53 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_2D_H
# define ARRAY_2D_H
# include "libft.h"

void	print_2d_array(char **array, int fd);
size_t	size_of_2d_array(char **array);
char	**dup_2d_array(char **array);
char	**delete_element_2d_array(char **array, size_t index);
int		find_in_2d_array(char **array, char *str);
char	**init_2d_array(void);
void	free_2d_array(char **array);
char	**add_element_2d_array(char **array, char *elem, size_t index);
char	**join_2d_array(char **dst, char **source);
char	**add_element_2d_array_last(char **array, char *elem);
char	*join_2d_array_into_str(char **array);
char	**split_and_join(char **array, char *line, char c);
#endif
