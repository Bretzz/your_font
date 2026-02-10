/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_parse_glyph_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:16:24 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/10 16:29:33 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
// #include <stdio.h>

int	yft_parse_glyph_block(char *char_block);

// NULL error, ptr all good
static char	*extract_glyph_block(char *char_block)
{
	size_t	i, j;
	short	bracket_count;
	char	*block;

	bracket_count = 0;
	i = 1;
	while (char_block[i] != '\0' && char_block[i] != '{')
		++i;
	if (char_block[i] == '\0')
		return (NULL);
	j = i;
	while (char_block[j] != '\0' && char_block[j] != '}')
		j++;
	if (char_block[j] == '\0' || char_block[j + 1] == '\0')
		return (NULL);
	block = ft_substr(char_block, i, j - i + 1);
	if (block == NULL)
		return (NULL);
	return (block);
}

static int	parse_glyph_block(char *block)
{
	const size_t	len = ft_strlen(block);
	char			**rows;
	size_t			i, len2;

	block[len - 1] = '\0';
	rows = ft_split(block + 1, ',');
	if (rows == NULL)
		return (2);
	i = 0;
	while (rows[i] != NULL)
	{
		len2 = ft_strlen(rows[i]);
		if (rows[i][0] != '"'
			|| rows[i][len2 - 1] != '"'
			|| (ssize_t)len2 != g_parsing_width + 2)
			return (ft_free_mtx((void **)rows), 1);
		++i;
	}
	ft_free_mtx((void **)rows);
	if ((ssize_t)i != g_parsing_heigth)
		return (1);
	return (0);
}

int	yft_parse_glyph_block(char *char_block)
{
	char *const	block = extract_glyph_block(char_block);
	int			ret;

	if (block == NULL)
		return (2);
	// printf("[glyph] extracted glyph block '%s'\n", block);
	ret = parse_glyph_block(block);
	free(block);
	return (ret);
}