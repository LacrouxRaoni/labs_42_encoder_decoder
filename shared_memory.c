#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>

#define IPC_RESULT_ERROR (-1)

static int	get_shared_block(int size)
{
	key_t	key;
	int		shmid;

	key = ftok("shmfile", 1);
	if (key == IPC_RESULT_ERROR)
	{
		printf("key memory share error : ");
		exit(-1);
	}
	shmid = shmget(key , size, 0666 | IPC_CREAT);
	return (shmid);
}

char	*attach_memory_block(int size)
{
	int		key;
	char	*result;

	key = get_shared_block(size);
	result = shmat(key, NULL, 0);
	if (result == (char *)IPC_RESULT_ERROR)
	{
		return (NULL);
	}
	return (result);
}

int		detach_memory_block(char *block)
{
	return (shmdt(block) != IPC_RESULT_ERROR);
}
	
int	destroy_memory_block()
{
	int shared_block_id = get_shared_block(0);
	return (shmctl(shared_block_id, 4096, NULL) != IPC_RESULT_ERROR);
}
