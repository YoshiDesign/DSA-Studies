package main

import (
	"fmt"
)

func main() {

	var nlines int
	var nwalkins int
	fmt.Printf("Number of lines: ")
	fmt.Scanf("%d", &nlines)

	fmt.Printf("Number of walkins: ")
	fmt.Scanf("%d", &nwalkins)

	// Note: slice begins with 0 len and nlines cap
	linecounts := make([]int, 0, nlines)

	for i := 0; i < nlines; i++  {
		var n int	
		fmt.Printf("Number of ppl in line %d: ", i + 1)
		fmt.Scanf("%d", &n)
		linecounts = append(linecounts, n)
	}


	// The index of the shortest line
	var shortest = 0 
	for i := 0; i < nwalkins; i++ {

		for j := 0; j < len(linecounts); j++ {
			
			if linecounts[j] < linecounts[shortest] {

				shortest = j

			}	

		}

		linecounts[shortest]++


		for i := 0; i < len(linecounts); i++ {
			fmt.Printf("[Line %d]: ", i)
			for j := 0; j < linecounts[i]; j++ {
		
				fmt.Printf("# ")

			}
			fmt.Printf("\n")
		}

		fmt.Printf("\n\n")


	}


}
