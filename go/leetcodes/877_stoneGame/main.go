package main

/*
Alice and Bob play a game with piles of stones. There are an even number of
piles arranged in a row, and each pile has a positive integer number of stones piles[i].

The objective of the game is to end with the most stones. The total number of
stones across all the piles is odd, so there are no ties.

Alice and Bob take turns, with Alice starting first. Each turn, a player takes the
entire pile of stones either from the beginning or from the end of the row. This continues
until there are no more piles left, at which point the person with the most stones wins.

Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.
*/

import (
	"fmt"
	"math/rand/v2"
)

const (
	policy_random = iota // we're only implementing this one - choose a random side
	policy_alternate
	policy_highest
)

func splice(idx int, in []int) []int {
	out := append(in[:idx], in[idx+1:]...)
	return out
}

func stoneGame(piles []int) bool {

	aPoints, bPoints := 0, 0
	turn := 1

	for {
		fmt.Println("Piles: ", piles)
		// take == 1 left end
		// take == 2 right end
		take := 0
		if rand.IntN(2) == 0 {
			take = 0 // first
		} else {
			take = len(piles) - 1 // last
		}

		if turn%2 == 1 {
			// Alice's turn
			aPoints += piles[take]

		} else {
			// Bob's turn
			bPoints += piles[take]
		}
		piles = splice(take, piles)

		if len(piles) == 0 {
			break
		}
	}

	// No tie checks, per the invarnace
	if aPoints > bPoints {
		return true
	} else {
		return false
	}

}

func main() {

	input := [...]int{4, 11, 5, 3, 11, 5} // [...] creates an array, this shortcut helps Go infer the length.

	if stoneGame(input[:]) { // Then, using [:], we can convert the array to a slice, which is what the function expects.
		fmt.Println("Alice Wins!")
	} else {
		fmt.Println("Bob Wins!")
	}
}
