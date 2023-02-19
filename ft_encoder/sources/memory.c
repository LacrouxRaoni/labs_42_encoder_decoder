/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:48:03 by rruiz-la          #+#    #+#             */
/*   Updated: 2023/01/15 10:48:04 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define IPC_RESULT_ERROR (-1)

static int	get_shared_block(char *filename, int size, int id)
{
	key_t key;

	key = ftok(filename, id); 
	if (key == IPC_RESULT_ERROR)
	{
		perror("key error : ");
		return IPC_RESULT_ERROR;
	}
	return shmget(key, size, 0644 | IPC_CREAT);
}

char	*attach_memory_block(char *filename, int size, int id)
{
	int		shared_block_id = get_shared_block(filename, size, id);
	char	*result;

	result = shmat(shared_block_id, NULL, 0);
	if (result == (char *)IPC_RESULT_ERROR)
	{
		perror("shmat error");
		return NULL;
	}
	return result;
}

int	detach_memory_block(char *block)
{
	return (shmdt(block) != IPC_RESULT_ERROR);
}

int	destroy_memory_block(char *filename, int id)
{
	int	shared_block_id = get_shared_block(filename, 0, id);

	if(shared_block_id == IPC_RESULT_ERROR)
	{
		return -1;
	}
	return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}