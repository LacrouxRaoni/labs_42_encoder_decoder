/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:05:04 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 11:22:56 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void initi_struct(t_decoder *dec, t_dec_return *ret)
{
	dec->mem_id = 1;
	dec->byte = 0;
	dec->src_size = 0;
	dec->bytes_len = 0;
	for (int i = 0; i < 128; i++)
		dec->frequency_table[i] = 0;

	ret->dec_message = NULL;
	ret->cmp_size_bits = 0;
	ret->descmp_size_bits = 0;
	ret->exec_time = 0.0;
}

void	free_tree(t_dc_list *root) 
{
	if (root == NULL)
    	return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	root = NULL;
}

void	free_everything(t_decoder *dec, t_dec_return *ret)
{
	if (ret->dec_message)
		free(ret->dec_message);
	if(dec->dc_list)
		free_tree(dec->dc_list);
}
