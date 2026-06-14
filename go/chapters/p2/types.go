package main

type Freelist struct {

	Buffer		[]Node
	// Next available slot
	FreeHead	*Node
	// Current capacity
	Capacity	int64

}

type Node struct {
	NextHead 	*Node
	Value		float64
	Active		bool
}
