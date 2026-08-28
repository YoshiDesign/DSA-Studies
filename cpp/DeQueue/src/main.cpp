#include <iostream>
#include "Memory/Arena.h"
#include "DQ/Dequeue.h"

const size_t MAX_TASKS = 65536;

int main(void) {

	size_t dq_arena_size = sizeof(TerrainTask) * MAX_TASKS;

	// Used to perform operations within tasks
	Arena working_arena = *CreateArena(1024 * 1024 * 1024); // 1 GB
	Arena dequeue_arena = *CreateArena(dq_arena_size);	// 100k tasks

	WSDeque<TerrainTask> dq = WSDeque<TerrainTask>(MAX_TASKS, &dequeue_arena);
	WSDeque<int> dq2 = WSDeque<int>(MAX_TASKS, &working_arena);

	std::cout << "Done!" << std::endl;
	return 0;
}