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
