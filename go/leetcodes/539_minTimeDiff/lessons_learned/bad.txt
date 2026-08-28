package main

import (
	"fmt"
	"slices"
	"strconv"
	"strings"
)

func prevIdx(idx int, timeData [24][]int) int {

	if idx == 0 {
		for i := 23; i >= 0; i-- {
			if len(timeData[i]) > 0 {
				return i
			}
		}
	}

	for i := idx - 1; i >= 0; i-- {
		if len(timeData[i]) > 0 {
			return i
		}
	}

	return -1
}

func nextIdx(idx int, timeData [24][]int) int {

	if idx == 23 {
		for i := 0; i < 24; i++ {

			if len(timeData[i]) > 0 {
				return i
			}
		}
	}

	for i := idx + 1; i < 24; i++ {

		if len(timeData[i]) > 0 {
			return i
		}
	}

	return -1
}

// You'd think to use math.Min, but in Go, that implies converting to float64, then back to int
func minInt(a, b int) int {

	if a < b {
		return a
	} else {
		return b
	}

}

func timeDelta(t1, t2, m1, m2 int, flag bool) int {

	var totalCycle int
	var delta int

	if flag {
		totalCycle = 24
	} else {
		totalCycle = 60
	}

	// Distance between our times
	dist := t1 - t2
	if dist < 0 {
		dist = -dist
	}

	// Difference is smallest as the sum of each hour's distance to midnight.
	var ghr int // the larger hour
	var lhr int // the smaller hour
	var gmn int // minutes belonging to the larger hour.
	var lmn int // minutes belonging to the lesser hour.

	if t1 > t2 {
		ghr = t1
		gmn = m1
		lhr = t2
		lmn = m2
	} else {
		ghr = t2
		gmn = m2
		lhr = t1
		lmn = m1
	}

	if dist > totalCycle/2 {

		// We take the difference between hours as the sum
		// of their shortest distance to midnight.
		// To add minutes to the overall diff, the greater hours's minutes
		// will contribute its difference from 60, while
		// the lesser hour's minutes will contribute its difference from 0

		ghrDist := totalCycle - ghr
		lhrDist := lhr

		if flag {
			ghrDist -= 1
		}

		delta = (ghrDist + lhrDist)
		if flag {
			// Convert hrs to mins
			delta = delta * 60
		}

		delta += lmn + (60 - gmn)

	} else {
		// hr diff is 12 or less
		delta = dist
		if flag {
			// Convert hrs to mins
			delta = dist * 60
			delta += (60 - gmn) + lmn
		}
	}

	return delta

}

func absDiffTime(m1, m2, h1, h2 int) int {

	if h1 == h2 {

		diff := m1 - m2
		if diff < 0 {
			return -diff
		}

		return diff

	}

	return timeDelta(h1, h2, m1, m2, true)

}

func findMinDifference(timePoints []string) int {

	min := 9999
	var timeData [24][]int // We know our dimensions and how they relate. So a raw array is particularly good here

	// Sort and store the input
	for _, time := range timePoints {

		hour, _ := strconv.Atoi(strings.Split(time, ":")[0])
		minute, _ := strconv.Atoi(strings.Split(time, ":")[1])

		timeData[hour] = append(timeData[hour], minute)
		slices.Sort(timeData[hour]) // Sort the minutes in each hour bucket
	}

	// DEBUG
	for i, bucket := range timeData {

		if len(bucket) > 0 {
			for _, mins := range bucket {
				fmt.Printf("%02d:%02d\n", i, mins)
			}
		}
	}

	for i := range 24 {

		for j := 0; j < len(timeData[i]); j++ {

			diff := 0
			t1 := timeData[i][j]

			// Check the previous hour's last element
			if j == 0 {
				if pidx := prevIdx(i, timeData); pidx != -1 {
					t2 := timeData[pidx][len(timeData[pidx])-1]

					diff = absDiffTime(t1, t2, i, pidx)
					min = minInt(min, diff)
				}
			}

			// Check the next hour's first element
			if j == len(timeData[i])-1 {
				if nidx := nextIdx(i, timeData); nidx != -1 {
					t3 := timeData[nidx][0]

					diff = absDiffTime(t1, t3, i, nidx)
					min = minInt(min, diff)
				}
			}

			// Compare internal values
			for k := j + 1; k < len(timeData[i]); k++ {
				t4 := timeData[i][k]
				diff = absDiffTime(t1, t4, i, i)
				min = minInt(min, diff)
			}

		}

	}

	return min
}

func main() {
	input := []string{"02:22", "04:45", "03:02", "23:55"}
	result := findMinDifference(input)
	fmt.Println("Result:", result)
}
