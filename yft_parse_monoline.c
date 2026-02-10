/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_parse_monoline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:26:13 by totommi           #+#    #+#             */
/*   Updated: 2026/02/10 16:13:26 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
#include <stdio.h>

int	yft_parse_monoline(char *monoline);

/* checks for correct parsing of the fomat file
Takes the file stripped by comments and whitespaces */
int	yft_parse_monoline(char *monoline)
{
	int		ret;
	size_t	char_block_count;

	ret = yft_parse_definition_block(&monoline);
	
	if (ret == 1)
	{
		write(2, "yft: Parsing error at Definition block\n", 41);
		return (1);
	}
	else if (ret == 2)
	{
		write(2, "yft: Internal error\n", 21);
		return (1);
	}

	char_block_count = 0;
	ret = 0;
	while (ret == 0)
	{
		ret = yft_parse_character_block(&monoline);
		++char_block_count;
	}

	if (ret == 1)
	{
		fprintf(stderr, "yft: Parsing error at Character block N.%zu\n", char_block_count);
		return (1);
	}
	else if (ret == 2)
	{
		write(2, "yft: Internal error\n", 21);
		return (1);
	}

	return (0);
}
