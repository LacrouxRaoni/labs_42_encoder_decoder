/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:43:37 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 01:09:12 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static	char *concat_data(char c, char *str)
{
	char *new_str;
	int	len;

	len = strlen(str);
	new_str = (char *)realloc(str, (len + 2) * sizeof(char));
	if (!new_str)
	{
		perror ("Realloc error : ");
		exit(1);
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

static int check_bit(int i , char byte)
{
	char mask = (1 << i);
	return byte & mask;
}

void	decompress_data(t_decoder* dec, t_dec_return *ret)
{
	t_dc_list	*root = dec->dc_list;
	t_dc_list	*aux = root;
	int			i;
	int			j;

	j = 0;
	ret->dec_message = (char *)calloc(1, sizeof(char));
	while(j < dec->bytes_len)
	{
		for (i = 7; i >= 0; i--)
		{
			if (check_bit(i, dec->byte[j]))
				aux = aux->right;
			else
				aux = aux->left;
			if (aux->left == NULL && aux->right == NULL)
			{
				ret->dec_message = concat_data(aux->char_val, ret->dec_message);
				aux = root;
			}
		}
		j++;
	}
}
