/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:49:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:49:19 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"


static int	search_char_in_dictionary(char c, char **dictionary)
{
	for (int i = 0; dictionary[i]; i++)
	{
		if (c == dictionary[i][0])
			return (i);
	}
	return (-1);
}

static char *genarete_bincode_line(t_encoder *enc, char *str)
{
	int		i;
	int		j;
	int		k;
	char	**line;
	char	*phrase;

	i = 0;
	j = 0;
	line = (char **)calloc(strlen(str), sizeof(char *) + 1);
	while (str[i])
	{
		k = search_char_in_dictionary(str[i], enc->dictionary);
		line[j] = ft_substr(enc->dictionary[k], 1, strlen(enc->dictionary[k]));
		j++;
		i++;
	}
	phrase = ft_str_superjoin(line);
	free_matrix(line);
	return (phrase);
} 

static int get_byte_size(char *code, int size)
{
	if (strlen(code) % 8 == 0)
		return (size = strlen(code) / 8);
	else
		return (size = (strlen(code) / 8) + 1);
}

static int	bitshif_value(char c, unsigned char *byte, int j)
{
	unsigned char mask;

	mask = 1;
	if (c == '1')
	{
		mask = mask << j;
		*(byte) = *(byte) | mask;
	}
	return (j - 1);
}

static int copy_byte_to_string(t_encoder *enc, unsigned char *byte)
{
	static int k;
	
	enc->bytes[k] = *(byte);
	k++;
	return (0);
}

void compress_code(char *code, t_encoder *enc)
{
	int	i;
	int	j;
	int	k;
	unsigned char byte;

	enc->bits_len = get_byte_size(code, enc->bits_len);
	enc->bytes = (unsigned char *)calloc(enc->bits_len, sizeof(unsigned char) + 1);

	i = 0;
	j = 7;
	k = 0;
	byte = 0;
	while (code[i])
	{
		j = bitshif_value(code[i], &byte, j);
		if (j < 0)
		{
			byte = copy_byte_to_string(enc, &byte);
			j = 7;
			k++;
		}
		i++;
	}
	if (j != 7)
		copy_byte_to_string(enc, &byte);
	enc->bits_len = k;
}

void	convert_to_bin(t_encoder *enc, char *str)
{
	char *code;

	code = genarete_bincode_line(enc, str);
	compress_code(code, enc);
	free(code);
}
