/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_huffman_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:39 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/14 23:44:40 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

t_dc_list *create_node(t_decoder *dec, int i)
{
	t_dc_list	*new_node;

	new_node = calloc(1, sizeof(t_dc_list) + 1);
	if (!new_node)
	{
		printf("malloc error \n");
		exit (1);
	}
	new_node->char_val = i;
	new_node->freq = dec->frequency_table[i];
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_dc_list *remove_node(t_decoder *dec)
{
	t_dc_list *aux = NULL;

	if (dec->dc_list)
	{
		aux = dec->dc_list;
		dec->dc_list = aux->next;
		aux->next = NULL;
	}
	return (aux);
}

void	add_node_in_list(t_dc_list *node, t_decoder *dec)
{
	t_dc_list *last;

	if (dec->dc_list == NULL)
	{
		node->next = NULL;
		dec->dc_list = node;
	}
	else if (node->freq < dec->dc_list->freq)
	{
		node->next = dec->dc_list;
		dec->dc_list = node;
	}
	else
	{
		last = dec->dc_list;
		while (last->next != NULL && node->freq > last->next->freq)
			last = last->next;
		node->next = last->next;
		last->next = node;
	}
}

void	create_list(t_decoder *dec)
{
	t_dc_list 	*node;
	(void)node;
	dec->dc_list = NULL;
	for (int i = 0; i < 128; i++)
	{
		if (dec->frequency_table[i] > 0)
		{
			node = create_node(dec, i);
			add_node_in_list(node, dec);
		}
	}
}

int    lstsize_frequency(t_dc_list *lst)
{
    int    count;

    count = 0;
    while (lst && count++ >= 0)
        lst = lst->next;
    return (count);
}