package main

import (
	"math"
	"fmt"
)

const MAX_SIZE = 128

var NodeArena = make([]Node, 0, MAX_SIZE)

func main()  {

	// Init FL	
	var FL Freelist
	FL.Buffer = make([]Node, 0, MAX_SIZE)
	FL.FreeHead = nil
	FL.Capacity = int64(len(FL.Buffer))

	// Half full 
	for i := range(MAX_SIZE / 2) {
		// Push PI * idx, idx
		new_node := Node{nil, float64(i)*math.Pi, true}
		FL.Alloc(new_node)
	}

	fmt.Println("--Exited Loop--")
	fmt.Printf("Allocated %d Node{} structs\n", FL.Capacity)
	fmt.Printf("Nil FreeHead: \t%p\n", FL.FreeHead)
	fmt.Printf("Remaining Cap: \t%d\n", int64(cap(FL.Buffer)) - FL.Capacity)


}
