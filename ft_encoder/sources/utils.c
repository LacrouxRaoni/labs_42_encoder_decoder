/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:47:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:47:54 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	free_matrix(char **line)
{
	int i;

	if (line != NULL)
	{
		i = 0;
		while(line[i])
		{
			free(line[i]);
			i++;
		}
	}
	free(line);
	line = NULL;
}

void free_tree(t_list *root)
{
	if (root == NULL)
    	return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	root = NULL;
}

void free_everything(t_encoder *enc, t_decoder_log *log)
{
	t_list *list;

	if (enc->dictionary != NULL)
		free_matrix(enc->dictionary);
	list = enc->list;
	if (list != NULL)
		free_tree(list);
	if (enc->bytes)
		free(enc->bytes);
	if (log->data)
		free(log->data);
}

void init_structs(t_encoder *enc, t_decoder_log *log)
{
	int i;

	enc->freq_size = 0;
	enc->lib_index = 0;
	enc->dictionary = NULL;
	enc->bytes = 0;
	enc->bits_len = 0;
	enc->mem_id = 1;
	enc->src_size = 0;
	for (i = 0; i < 128; i++){
		enc->vec[i] = 0;
	}
	log->cmp_file_size = 0;
	log->decmp_file_size = 0;
	log->exec_time = 0.0;
	log->data = NULL;
}
