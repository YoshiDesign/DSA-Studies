package better

import (
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
)

var half int = 12 * 60
var whole int = 24 * 60

// Note: t2 is always greater than t1
func deltaTime(t1, t2 int) int {

	if t2 < t1 {
		fmt.Println("error: sorting failure")
		os.Exit(1)
	}

	var delta int

	diff := t2 - t1

	if diff > half {
		// Calculate across the midnight boundary
		delta = t1 + (whole - t2)

	} else {
		// Calculate directly between the times, don't cross midnight
		delta = t2 - t1

	}

	return delta
}

func findMinDifference(timePoints []string) int {

	var min int
	var times []int

	for _, t := range timePoints {
		// Convert each time to its total minutes
		hrs, _ := strconv.Atoi(strings.Split(t, ":")[0])
		mins, _ := strconv.Atoi(strings.Split(t, ":")[1])

		total := (hrs * 60) + mins
		times = append(times, total)
	}

	// times converted to minutes, earliest to latest
	slices.Sort(times)

	min = 9999

	// Quadratic and loving it. I will not be implementing a logarithmic approach
	// using hourly buckets due to the time constraint. This is a speed-run
	for i, t1 := range times {
		for j := i + 1; j < len(times); j++ {
			t2 := times[j]
			diff := deltaTime(t1, t2)

			if diff < min {
				min = diff
			}
		}
	}

	return min
}

func main() {
	input := []string{"00:07", "02:22", "04:45", "3:02", "18:59"}
	result := findMinDifference(input)
	fmt.Println(result)
}
