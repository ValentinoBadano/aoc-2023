package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func getMinimum(arr []int) int {
	var minimum = arr[0]
	for _, e := range arr {
		if e < minimum {
			minimum = e
		}
	}
	return minimum
}

func extractNumbers(str string) []int {
	re := regexp.MustCompile("\\d+") // creates regexp

	matches := re.FindAllString(str, -1) // gets all matches in string

	var numbers []int
	for _, match := range matches {
		number, err := strconv.Atoi(match)
		if err == nil {
			numbers = append(numbers, number)
		}
	}

	return numbers
}

func convert(number int, dest int, source int, len int) int {
	if (source <= number) && (number < source+len) {
		return dest + number - source
	}
	return -1
}

func getLocation(almanac []string, seed int) int {
	almanac = almanac[3:]

	var actualValue = seed
	var canConvert = true

	for _, line := range almanac {
		var numbers = extractNumbers(line)
		if len(numbers) == 0 {
			canConvert = true
			continue
		}
		var convertion = convert(actualValue, numbers[0], numbers[1], numbers[2])
		if convertion != -1 && canConvert {
			//fmt.Printf("Value %d converted to %d", actualValue, convertion)
			canConvert = false
			actualValue = convertion
		}
	}
	return actualValue
}

func main() {
	file, err := os.Open("input.txt") // opens file
	if err != nil {                   // if error, panics
		panic(err)
	}
	defer file.Close() // closes on exit

	scanner := bufio.NewScanner(file) // read file line by line
	var lines []string

	for scanner.Scan() {
		line := scanner.Text()
		lines = append(lines, line) // saves each line
	}

	var seeds = extractNumbers(lines[0])
	var locations []int
	for _, seed := range seeds {
		var location = getLocation(lines, seed)
		fmt.Printf("Seed %d, location %d\n", seed, location)
		locations = append(locations, location)
	}

	fmt.Printf("The minimum location is %d\n", getMinimum(locations))
}
