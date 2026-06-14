package main

import(
	"fmt"
	"math"
)

/*
 * Free a node and set the current FreeHead to that node.
 * The node's NextHead is swapped for the previous FreeHead
**/
func (fl *Freelist) Free(node *Node) error {

	fmt.Println("Freeing Node: ", node.Value)	

	if node.Active == false {
		return fmt.Errorf("error freeing node [1]")
	}

	node.Active 	= false
	node.NextHead 	= fl.FreeHead
	fl.FreeHead	= node

	return nil
}

/**
 * Allocate a new node or recycle an old one
 */
func (fl *Freelist) Alloc(node Node) (*Node, error) {

	if fl.FreeHead != nil {
		fmt.Println("Alloc: FreeHead is nil, allocating...")
		var recycled *Node = fl.FreeHead
		fl.FreeHead = recycled.NextHead
		return recycled, nil
	} else {
		fmt.Println("Alloc: Recycling previous node...")
		var new_node Node = Node{nil, math.Pi, true}
		fl.Capacity++
		return &new_node, nil
	}

	return nil, nil
}
