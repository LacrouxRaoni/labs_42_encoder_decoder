/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:12 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:48:13 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

t_list *create_node(t_encoder *enc, int i)
{
	t_list *node;
	node = (t_list *)calloc(1, sizeof(t_list) + 1);
	if (!node)
	{
		perror("malloc error");
		exit(1);
	}
	node->ch_value = i; 
	node->frequency = enc->vec[i];
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_list *remove_node(t_encoder *enc)
{
	t_list* aux = NULL;

	if (enc->list)
	{
		aux = enc->list;
		enc->list = aux->next;
		aux->next = NULL;
	}
	return aux;
}

void insert_in_list(t_encoder *enc, t_list *node)
{
	t_list *last;

	if (enc->list == NULL)
	{	
		node->next = NULL;
		enc->list = node;
	} 
	else if (node->frequency < enc->list->frequency)
	{
		node->next = enc->list;
		enc->list = node;
	}
	else
	{
		last = enc->list;
		while (last->next != NULL && node->frequency > last->next->frequency)
		{
			last = last->next;
		}
		node->next = last->next;
		last->next = node;
	}
		
}

void create_list(t_encoder *enc)
{
	t_list *node;
	int i;

	enc->list = NULL;
	for (i = 0; i < 128; i++)
	{
		if (enc->vec[i] > 0)
		{
			node = create_node(enc, i);
			insert_in_list(enc, node);
			enc->freq_size++;
		}
	}		
}

int    lstsize_frequency(t_list *lst)
{
    int    count;

    count = 0;
    while (lst && count++ >= 0)
        lst = lst->next;
    return (count);
}
