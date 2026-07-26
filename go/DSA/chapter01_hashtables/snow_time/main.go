package main

import "fmt"

type snowflake_node struct {
	next      *snowflake_node
	snowflake [6]int
}

const MAX_SNOWFLAKES int = 1 << 17

// Specifically hashes snowflakes
func oaat(data [6]int) uint64 {

	var hash uint64 = 0

	for _, b := range data { // _ is index, b is value
		hash += uint64(b)
		hash += (hash << 10)
		hash ^= (hash >> 6)
	}

	hash += (hash << 3)
	hash ^= (hash >> 11)
	hash += (hash << 15)

	return hash
}

func identical_right(snow1 [6]int, snow2 [6]int, start int) bool {

	for offset := 0; offset < 6; offset++ {
		index2 := (start + offset) % 6
		if snow1[offset] != snow2[index2] {
			return false
		}
	}

	return true
}
func identical_left(snow1 [6]int, snow2 [6]int, start int) bool {

	for offset := 0; offset < 6; offset++ {
		index2 := start - offset
		if index2 < 0 {
			// wrap around behavior
			index2 += 6
		}
		if snow1[offset] != snow2[index2] {
			return false
		}
	}

	return true
}

func are_identical(snow1 [6]int, snow2 [6]int) bool {

	for start := 0; start < 6; start++ {
		if identical_right(snow1, snow2, start) {
			fmt.Println("Identical Right!!")
			return true
		}
		if identical_left(snow1, snow2, start) {
			fmt.Println("Identical Left!!")
			return true
		}
	}

	return false
}

func identify_identical(snowflakes []*snowflake_node) {

	for i := 0; i < MAX_SNOWFLAKES; i++ {
		node1 := snowflakes[i]
		for node1 != nil {
			node2 := node1.next

			for node2 != nil {
				if are_identical(node1.snowflake, node2.snowflake) {
					fmt.Println("Found matching pair!")
					return
				}
				node2 = node2.next
			}
			node1 = node1.next
		}

	}
}

func sumflake(snow [6]int) int {

	total := 0

	for _, n := range snow {
		total += n
	}

	return total
}

func lessSnow(best, snow [6]int) bool {

	for i := 0; i < 6; i++ {
		// snow is a better candidate
		if best[i] > snow[i] {
			return true
		}

		// snow is not a better candidate
		if snow[i] > best[i] {
			return false
		}
	}

	// they're the same
	return false
}

func canonicalizeSnowflake(snow [6]int) [6]int {

	best := snow
	for start := 0; start < 6; start++ {

		var right [6]int
		var left [6]int

		for offset := 0; offset < 6; offset++ {
			right[offset] = snow[(start+offset)%6]

			lindex := start - offset
			if lindex < 0 {
				lindex += 6
			}
			left[offset] = snow[lindex]
		}

		if lessSnow(best, right) {
			best = right
		}
		if lessSnow(best, left) {
			best = left
		}
	}

	return best
}

func main() {
	// Hashtable with preallocated 0-value indices
	var hashtable = make([]*snowflake_node, MAX_SNOWFLAKES)

	var n, i, j uint
	fmt.Printf("Num Snowflakes: ")
	fmt.Scanf("%d", &n)

	for i = uint(0); i < n; i++ {

		var snow snowflake_node

		fmt.Println("Enter side lenghts...")
		for j = uint(0); j < 6; j++ {
			fmt.Scanf("%d", &snow.snowflake[j])
		}

		// code := uint64(sumflake(snow.snowflake))
		code := oaat(canonicalizeSnowflake(snow.snowflake))
		code = code & uint64(MAX_SNOWFLAKES-1)
		fmt.Printf("Hash: %d\n", code)
		snow.next = hashtable[code]
		hashtable[code] = &snow

	}

	identify_identical(hashtable)

	fmt.Print("Done!\n")

}
