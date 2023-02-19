/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_huffman_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:33 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/14 23:44:34 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void	build_huffman_tree(t_decoder *dec)
{
	t_dc_list *first;
	t_dc_list *second;
	t_dc_list *new_node;

	while(lstsize_frequency(dec->dc_list) > 1)
	{
		first = remove_node(dec);
		second = remove_node(dec);
		new_node = malloc(sizeof(t_dc_list));
		if (!new_node)
		{
			perror("malloc error");
			exit(1);
		}
		new_node->char_val = -1;
		new_node->freq = first->freq + second->freq;
		new_node->left = first;
		new_node->right = second;
		new_node->next = NULL;
		add_node_in_list(new_node, dec);
	}
}
