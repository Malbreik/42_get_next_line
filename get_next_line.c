/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbreik <malbreik@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:40:59 by malbreik          #+#    #+#             */
/*   Updated: 2025/01/23 14:49:21 by malbreik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free_basket(char *basket, char *new_fish)
{
	char	*temp_basket;

	temp_basket = ft_strjoin(basket, new_fish);
	free(basket);
	return (temp_basket);
}

char	*split_basket_with_knife(char *basket)
{
	int		i;
	int		j;
	char	*remaining_fish;

	i = 0;
	while (basket[i] && basket[i] != '\n')
		i++;
	if (!basket[i])
	{
		free(basket);
		return (NULL);
	}
	remaining_fish = ft_calloc((ft_strlen(basket) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (basket[i])
		remaining_fish[j++] = basket[i++];
	free(basket);
	return (remaining_fish);
}

char	*extract_line_from_basket(char *basket)
{
	char	*line;
	int		i;

	i = 0;
	if (!basket[i])
		return (NULL);
	while (basket[i] && basket[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (basket[i] && basket[i] != '\n')
	{
		line[i] = basket[i];
		i++;
	}
	if (basket[i] && basket[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*cast_net_into_lake(int fd, char *basket)
{
	char	*new_fish;
	int		fish_caught;

	new_fish = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	if (!new_fish)
		return (NULL);
	fish_caught = 1;
	while (fish_caught > 0)
	{
		fish_caught = read(fd, new_fish, BUFFER_SIZE);
		if (fish_caught == -1)
		{
			free(new_fish);
			free(basket);
			return (NULL);
		}
		new_fish[fish_caught] = 0;
		basket = join_and_free_basket(basket, new_fish);
		if (!basket || ft_strchr(basket, '\n'))
			break ;
	}
	free(new_fish);
	return (basket);
}

char	*get_next_line(int fd)
{
	static char	*basket = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	if (!basket)
	{
		basket = ft_calloc(1, 1);
		if (!basket)
			return (NULL);
	}
	basket = cast_net_into_lake(fd, basket);
	if (!basket)
		return (NULL);
	line = extract_line_from_basket(basket);
	basket = split_basket_with_knife(basket);
	return (line);
}
