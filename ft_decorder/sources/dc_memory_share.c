/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_memory_share.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:13 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 09:00:44 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static int read_int(t_decoder *dec)
{
	char *block;
	int	 len;	

	block = attach_memory_block(FILENAME, sizeof(int), dec->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(&len, &block[0], sizeof(int));
	destroy_memory_block(FILENAME, dec->mem_id);
	dec->mem_id++;
	return (len);
}

static void read_strbts(t_decoder *dec)
{
	char 	*block;

	dec->bytes_len = read_int(dec);
	block = attach_memory_block(FILENAME, dec->bytes_len * sizeof(unsigned char), dec->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(&(dec->byte), &block, sizeof(unsigned char *));
	destroy_memory_block(FILENAME, dec->mem_id);
	dec->mem_id++;
}

void	read_int_vector(t_decoder *dec)
{
	unsigned int *block;

	block = (unsigned int*)attach_memory_block(FILENAME, 128 * sizeof(int), dec->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(dec->frequency_table, block, 128 * sizeof(int));
	destroy_memory_block(FILENAME, dec->mem_id);
	dec->mem_id++;
}

void read_from_shared_memory(t_decoder *dec)
{
	read_strbts(dec);
	read_int_vector(dec);
	dec->src_size = read_int(dec);
}

void transfer_int(int mem_int, t_decoder *dec)
{
	char *block;

	block = attach_memory_block(FILENAME, sizeof(int), dec->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(&block[0], &mem_int, sizeof(int));
	detach_memory_block((char *)block);
	dec->mem_id++;
}

void transfer_double(double db, t_decoder *dec)
{
	char *block;

	block = attach_memory_block(FILENAME, sizeof(double), dec->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(&block[0], &db, sizeof(double));
	detach_memory_block(block);
	dec->mem_id++;
}

static void	transfer_string(char **str, int size, t_decoder *dec)
{
	char *block;

	block = attach_memory_block(FILENAME, size * sizeof(char), dec->mem_id);
	if(!block)
		perror("memory block error : ");
	dec->mem_id++;
	memcpy(block, *(str), size * sizeof(char));
	detach_memory_block(block);
}

void return_to_encoder(t_dec_return *ret, t_decoder *dec)
{
	transfer_int(ret->cmp_size_bits, dec);
	transfer_int(ret->descmp_size_bits, dec);
	transfer_string(&(ret->dec_message), ret->descmp_size_bits, dec);
	transfer_double(ret->exec_time, dec);

}
