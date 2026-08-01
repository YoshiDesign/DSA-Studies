package main

import (
	"fmt"
	"slices"
	"strconv"
	"strings"
)

// We did not need to return to hourly bucketing to improve the performance.
// Chronological structure provided implicit logical enhancements that carried performance.

/**
Sorting:     O(n log n)
Comparison:  O(n)
Overall:     O(n log n)
*/

const half = 12 * 60
const whole = 24 * 60

func findMinDifference(timePoints []string) int {

	min := whole
	var times []int

	for _, t := range timePoints {
		// Convert each time to its total minutes
		s := strings.Split(t, ":")
		hrs, _ := strconv.Atoi(s[0])
		mins, _ := strconv.Atoi(s[1])

		total := (hrs * 60) + mins
		times = append(times, total)
	}

	// times converted to minutes, earliest to latest
	slices.Sort(times)

	for i := 1; i < len(times); i++ {

		diff := times[i] - times[i-1]

		if diff < min {
			min = diff
		}

	}

	wrapDiff := (times[0] + whole) - times[len(times)-1]

	if wrapDiff < min {
		min = wrapDiff
	}

	return min
}

func main() {
	input := []string{"00:07", "02:22", "04:45", "3:02", "18:59"}
	result := findMinDifference(input)
	fmt.Println(result)
}
