package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

type Finder struct{}

func (f *Finder) findMinDifference(timePoints []string) int {

	// Better than quadratic time complexity.
	timeTable := make(map[int][]int)

	for i := 0; i < 24; i++ {
		timeTable[i*60] = []int{}
	}

	// Organize input into hashtable
	for _, time := range timePoints {

		split_time := strings.Split(time, ":")
		bucket, _ := strconv.Atoi(split_time[0])
		bucket = bucket * 60 // Align to minutes
		mins, _ := strconv.Atoi(split_time[1])

		// Append total number of minutes into the hour
		timeTable[bucket] = append(timeTable[bucket], bucket+mins)
		//timeLens[bucket] = len(timeTable[bucket])
		fmt.Printf("allocated {%d} to bucket [%d]:\n", bucket+mins, bucket)
	}

	min := 999

	// Every bucket
	for i := 0; i < 24; i++ {

		idx := i * 60

		// Compare all elements in the same bucket
		for j := 0; j < len(timeTable[idx]); j++ {

			diff := 0
			t1 := timeTable[idx][j]
			fmt.Println("T1: ", t1)

			// Check the last element of the previous bucket - omit i == 0 edge-case
			if prev_idx := (i - 1) * 60; j == 0 && i > 0 {
				diff = diffLastElement(timeTable, prev_idx, t1)
				min = int(math.Min(float64(min), float64(diff)))

				fmt.Println("Previous bucket diff: ", diff, " min: ", min)
			}

			// Check the first element of the next bucket
			if next_idx := (i + 1) * 60; i < 23 {
				diff = diffFirstElement(timeTable, next_idx, t1)
				min = int(math.Min(float64(min), float64(diff)))

				fmt.Println("Next bucket diff: ", diff, " min: ", min)
			}

			// Edge case - Check the last element of the last bucket against the first element of the first bucket
			if i == 0 && j == 00 && len(timeTable[23]) > 0 {
				// Check the last element of the last bucket
				diff = diffLastElement(timeTable, 23*60, t1+(24*60))
				min = int(math.Min(float64(min), float64(diff)))

				fmt.Println("Last bucket diff: ", diff, " min: ", min)
			}

			// Edge case - Check the first element of the first bucket against the last element of the last bucket
			if i == 23 && j == len(timeTable[i*60])-1 && len(timeTable[0]) > 0 {
				// Check the first element of the first bucket
				diff = diffFirstElement(timeTable, 0, t1-(24*60))
				min = int(math.Min(float64(min), float64(diff)))

				fmt.Println("First bucket diff: ", diff, " min: ", min)
			}

			// Compare all elements in the same bucket
			for k := j + 1; k < len(timeTable[idx]); k++ {

				t2 := timeTable[idx][k]
				fmt.Println("T2: ", t2)

				// Diff within the same hour
				diff = int(math.Abs(float64(t2 - t1)))
				min = int(math.Min(float64(min), float64(diff)))

				fmt.Println("Same bucket diff: ", diff, " min: ", min)

			}
		}
	}

	return min
}

func diffLastElement(timeTable map[int][]int, prev_idx int, t1 int) int {
	diff := 999
	last := len(timeTable[prev_idx]) - 1
	if last >= 0 {
		prev := timeTable[prev_idx][last]
		diff = int(math.Min(float64(diff), math.Abs(float64(t1-prev))))
	}
	return int(math.Abs(float64(diff)))
}

func diffFirstElement(timeTable map[int][]int, next_idx int, t1 int) int {
	diff := 999
	if len(timeTable[next_idx]) > 0 {
		next := timeTable[next_idx][0]
		diff = int(math.Min(float64(diff), math.Abs(float64(next-t1))))
	}
	return diff
}

func main() {
	input := []string{"00:07", "02:22", "04:45", "3:02", "23:59"}
	finder := Finder{}
	result := finder.findMinDifference(input)
	fmt.Println("Result:", result)
}
