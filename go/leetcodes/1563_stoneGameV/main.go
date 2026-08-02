package main

import (
	"fmt"
)

const (
	policy_random = iota
	policy_center
)

var memo [][]int

/**
* Note: We do not need to simulate every complete game independently.
* Many different sequences of earlier choices lead to the same remaining contiguous row.
 */

func arrSum(values []int) int {

	total := 0
	for _, v := range values {
		total += v
	}
	return total
}

func rangeSum(prefix []int, left, right int) int {
	return prefix[right+1] - prefix[left]
}

func intMax(a, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

// a la Bellman Principle of Optimality.
// `right` enters as the greatest valid index
func solve(left, right int, vals []int) int {

	if left == right {
		return 0
	}

	// Check for an existing result
	if memo[left][right] != -1 {
		fmt.Println("L/R Cached:", left, right)
		return memo[left][right]
	}

	best := 0

	for cut := left; cut < right; cut++ {

		// This section describes the transition function

		leftSum := rangeSum(vals, left, cut)     // sum from left to cut
		rightSum := rangeSum(vals, cut+1, right) // sum from cut + 1 to right

		switch {
		case leftSum < rightSum:
			// Alice scores, continues with left row
			score := leftSum + solve(left, cut, vals)
			best = intMax(best, score)

		case rightSum < leftSum:
			// Alice scores, continues with right row
			score := rightSum + solve(cut+1, right, vals)
			best = intMax(best, score)

		default:
			// choose left
			best = intMax(
				best,
				leftSum+intMax(
					solve(left, cut, vals),
					solve(cut+1, right, vals),
				))
		}

	}

	memo[left][right] = best
	return best

}

func stoneGameV(stoneValue []int) int {

	n := len(stoneValue)
	memo = make([][]int, n)

	for i := range memo {
		memo[i] = make([]int, n)

		for j := range memo[i] {
			memo[i][j] = -1
		}
	}

	/*
	* Creating a prefix-sum table eliminates the need
	* to perform an array sum every time we need to calculate one.
	 */
	prefix := make([]int, n+1)

	for i, value := range stoneValue {
		prefix[i+1] = prefix[i] + value
	}

	return solve(0, n-1, prefix)
}

func main() {

	input := []int{6, 2, 3, 4, 5, 5, 6, 2, 3, 4, 5, 5, 6, 2, 3, 4, 5, 5, 6, 2, 3, 4, 5, 5, 6, 2, 3, 4, 5, 5}

	result := stoneGameV(input)
	fmt.Println(result)
}
