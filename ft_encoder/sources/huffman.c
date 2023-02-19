/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:15 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:48:16 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

int find_tree_size(t_list *list)
{
	int left;
	int right;

	if (list == NULL)
		return (-1);
	else
	{
		left = find_tree_size(list->left) + 1;
		right = find_tree_size(list->right) + 1;
		if (left > right)
			return (left);
		else
			return (right);
	}
}

void build_huffman_tree(t_encoder *enc)
{
	t_list *first;
	t_list *second;
	t_list *new_node;

	while(lstsize_frequency(enc->list) > 1)
	{
		first = remove_node(enc);
		second = remove_node(enc);
		new_node = malloc(sizeof(t_list));
		if (!new_node)
		{
			perror("malloc error");
			exit(1);
		}
		new_node->ch_value = -1;
		new_node->frequency = first->frequency + second->frequency;
		new_node->left = first;
		new_node->right = second;
		new_node->next = NULL;
		insert_in_list(enc, new_node);
	}
}
