package main

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

	input := [...]int{4, 11, 5, 3, 11, 4}

	if stoneGame(input[:]) {
		fmt.Println("Alice Wins!")
	} else {
		fmt.Println("Bob Wins!")
	}
}
