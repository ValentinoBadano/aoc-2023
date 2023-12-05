package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

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

	for _, line := range lines {
		fmt.Println(extractNumbers(line))
	}

	fmt.Println("Hello World!")
}
