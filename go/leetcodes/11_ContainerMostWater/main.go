package main

func maxArea(height []int) int {
	left := 0
	right := len(height) - 1

	best := 0

	for left < right {

		x := right - left
		y := min(height[left], height[right])
		area := x * y

		if area > best {
			best = area
		}

		if height[left] > height[right] {
			right--
		} else {
			left++
		}

	}

	return best
}

func main() {

}
