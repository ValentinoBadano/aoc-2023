f = open("01-Python/input.txt", "r")


def calibration(file):
    lines = file.readlines()
    sum = 0
    for line in lines:
        digits = []
        for char in line:
            if char.isnumeric():
                digits.append(char)
        value = digits[0] + digits[-1]
        sum += int(value)
    return sum


print(calibration(f))