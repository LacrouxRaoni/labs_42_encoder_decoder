/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:49:08 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:49:08 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

static void allocate_matrix_dictionary(int size, t_encoder *enc)
{
	int		i;

	enc->dictionary = (char **)calloc(enc->freq_size, sizeof(char *) + 1);
	for (i = 0; i < enc->freq_size; i++)
		enc->dictionary[i] = (char *)calloc(size, sizeof(char) + 1);
}

static void generate_dictionary(t_encoder *enc, t_list *root, char *path, int pos)
{
	char aux_left[pos];
	char aux_right[pos];

	if (root->left == NULL && root->right == NULL)
	{
		char tmp[2];
		tmp[0] = root->ch_value;
		tmp[1] = '\0';
		strcat(enc->dictionary[enc->lib_index], tmp);
		strcat(enc->dictionary[enc->lib_index], path);
		enc->lib_index++;
	}
	else
	{
		strcpy(aux_left, path);
		strcpy(aux_right, path);
		strcat(aux_left, "0");
		strcat(aux_right, "1");
		generate_dictionary(enc, root->left, aux_left, pos);
		generate_dictionary(enc, root->right, aux_right, pos);
	}
}


void	build_dctionary(t_encoder *enc)
{
	int size;
	t_list *list = enc->list;

	size = find_tree_size(list) + 1;
	allocate_matrix_dictionary(size, enc);
	generate_dictionary(enc, enc->list, "", size);
}
