/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_share.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:47:43 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:53:22 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

static void transfer_int(int mem_int, t_encoder *enc)
{
	int *block;

	block = (int *)attach_memory_block(FILENAME, sizeof(int *), enc->mem_id);
	if(!block)
		perror("memory block error : ");
	enc->mem_id++;
	memcpy(&block[0], &mem_int, mem_int);
	detach_memory_block((char *)block);
}

static void	transfer_string(t_encoder *enc)
{
	char *block;

	block = attach_memory_block(FILENAME, enc->bits_len * sizeof(char), enc->mem_id);
	if(!block)
		perror("memory block error : ");
	enc->mem_id++;
	memcpy(block, enc->bytes, enc->bits_len * sizeof(char));
	detach_memory_block(block);

}

void transfer_int_array(t_encoder *enc)
{
	unsigned int *block;

	block = (unsigned int *)attach_memory_block(FILENAME, 128 * sizeof(int), enc->mem_id);
	if(!block)
		perror("memory block error : ");
	enc->mem_id++;
	memcpy(block, enc->vec, 128 * sizeof(int));
	detach_memory_block((char *)block);
}

static int read_int(t_encoder *enc)
{
	char *block;
	int	 len;	

	block = attach_memory_block(FILENAME, sizeof(int), enc->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(&len, &block[0], sizeof(int));
	destroy_memory_block(FILENAME, enc->mem_id);
	enc->mem_id++;
	return (len);
}

static double read_double(t_encoder *enc)
{
	char	*block;
	double	db;	

	block = attach_memory_block(FILENAME, sizeof(double), enc->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(&db, &block[0], sizeof(double));
	destroy_memory_block(FILENAME, enc->mem_id);
	enc->mem_id++;
	return (db);
}

static char *read_string(t_encoder *enc, int size)
{
	char *block;
	char *message;

	message = (char *)calloc(size, sizeof(char) + 1);
	block = attach_memory_block(FILENAME, size * sizeof(char), enc->mem_id);
	if(!block)
		perror("memory block error : ");
	memcpy(message, block, size * sizeof(char));
	destroy_memory_block(FILENAME, enc->mem_id);
	enc->mem_id++;
	return (message);
}

void memory_share(t_encoder *enc, t_decoder_log *log)
{	
	transfer_int(enc->bits_len, enc);
	transfer_string(enc);
	transfer_int_array(enc);
	transfer_int(enc->src_size, enc);

	write(1, "WAITING DECODER...\n", strlen("WAITING DECODER...\n"));
	sleep(5);
	
	log->cmp_file_size = read_int(enc);
	log->decmp_file_size = read_int(enc);
	log->data = read_string(enc, log->decmp_file_size);
	log->exec_time = read_double(enc);
}
