/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:39:58 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 15:42:23 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define FILENAME "../tmp/shmfile.txt"

typedef struct s_dc_list
{
	int	char_val;
	int freq;
	struct s_dc_list *next;
	struct s_dc_list *left;
	struct s_dc_list *right;
} t_dc_list;

typedef struct s_decoder
{
	int				mem_id;
	char			*byte;
	int				frequency_table[128];
	int				src_size;
	int				bytes_len;
	t_dc_list		*dc_list;
} t_decoder;

typedef struct s_dec_return
{
	char	*dec_message;
	int		cmp_size_bits;
	int		descmp_size_bits;
	double	exec_time;
	
} t_dec_return;

void		read_from_shared_memory(t_decoder *dec);
void		create_list(t_decoder *dec);
void		add_node_in_list(t_dc_list *node, t_decoder *dec);
t_dc_list	*remove_node(t_decoder *dec);
char		*attach_memory_block(char *filename, int size, int id);
int			detach_memory_block(char *block);
int			destroy_memory_block(char *filename, int id);
void		build_huffman_tree(t_decoder *dec);
int			lstsize_frequency(t_dc_list *lst);
void		decompress_data(t_decoder *dec, t_dec_return *ret);
void		get_log_data(t_decoder *dec, t_dec_return *ret);
void		return_to_encoder(t_dec_return *ret, t_decoder *dec);
void		initi_struct(t_decoder *dec, t_dec_return *ret);
void		free_tree(t_dc_list *root);
void		free_everything(t_decoder *dec, t_dec_return *ret);

#endif