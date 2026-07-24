package main

import (
	"time"
	"fmt"
)

type Finder struct {}

func (f *Finder) findMinDifference(timePoints []string) int {

	

	return 0	
}
 
func main(){
	input := [...]string{"00:00", "00:02", "00:05", "01:01", "01:02"} 

	result := findMinDifference(input)
	fmt.Println("Result:", result)

}
