/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:39:58 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 15:39:10 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>
#include <ctype.h>

#define FILENAME "../tmp/shmfile.txt"

typedef struct s_list
{
	int				ch_value;
	int 			frequency;
	struct s_list	*next;
	struct s_list	*left;
	struct s_list	*right;
} t_list;

typedef struct s_decoder_log
{
	int		cmp_file_size;
	int		decmp_file_size;
	double	exec_time;
	char	*data;
} t_decoder_log;

typedef struct s_encoder 
{
	int				vec[128];
	int				freq_size;
	char			**dictionary;
	int				lib_index;
	unsigned char	*bytes;
	int 			bits_len;
	int				mem_id;
	int				src_size;
	t_list			*list;
} t_encoder;

void	init_structs(t_encoder *enc, t_decoder_log *log);
char	*open_files(char **files);
void	create_frequency_table(t_encoder *enc, char *str);
t_list	*create_node(t_encoder *enc, int i);
t_list	*remove_node(t_encoder *enc);
void	insert_in_list(t_encoder *enc, t_list *node);
void	create_list(t_encoder *enc);
int		lstsize_frequency(t_list *lst);
void	build_huffman_tree(t_encoder *enc);
void	build_dctionary(t_encoder *enc);
int		find_tree_size(t_list *list);
void	convert_to_bin(t_encoder *enc, char *str);
void	memory_share(t_encoder *enc, t_decoder_log *log);
char	*attach_memory_block(char *filename, int size, int id);
int		detach_memory_block(char *block);
int		destroy_memory_block(char *filename, int id);
char	*ft_str_superjoin(char **src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_everything(t_encoder *enc, t_decoder_log *log);
void	free_matrix(char **line);
void	free_tree(t_list *root);
void	print_log(t_decoder_log *log);

#endif