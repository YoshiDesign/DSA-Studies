#include <iostream>
#include "Memory/Arena.h"
#include "DQ/Dequeue.h"

enum class TerrainTaskKind {
	Points = 1,
	AllPoints,
	Triangulation,
	Mesh,
};

struct ChunkCoord {
	int x, z;
};

struct TerrainTask {
	TerrainTaskKind kind;
	ChunkCoord coord;
	uint64_t frameIndex;
	uint64_t requestId;
};

const size_t MAX_TASKS = 65536;

int main(void) {

	size_t dq_arena_size = sizeof(TerrainTask) * MAX_TASKS;

	// Used to perform operations within tasks
	Arena working_arena = *CreateArena(1024 * 1024 * 1024); // 1 GB
	Arena dequeue_arena = *CreateArena(dq_arena_size);	// 100k tasks

	WSDeque<TerrainTask> dq = WSDeque<TerrainTask>(MAX_TASKS, &dequeue_arena);

	std::cout << "Done!" << std::endl;
	return 0;
}