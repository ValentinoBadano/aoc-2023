f = open("01-Python/input.txt", "r")

def calibration(file):
    lines = file.readlines()
    sum = 0
    for line in lines:
        digits = read_numbers(line)
        value = digits[0] + digits[-1]
        sum += int(value)
    return sum

def read_numbers(string):
    digits = []
    numbers = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
    
    for i in range(len(string)):
        char = string[i]

        if char.isnumeric():
            digits.append(char)
        else:    
            for j in range(3, 6):
                word = string[i:i+j]
                if word in numbers:
                    char = str(numbers.index(word) + 1)
                    digits.append(char)
    
    return digits
print(calibration(f))