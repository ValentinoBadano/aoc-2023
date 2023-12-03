import java.io.File

fun getLines(path: String): List<String> {
    val file: File = File(path)
    return file.readLines()
}

fun getNumberRanges(line : String): MutableList<IntRange> {
    val regex : Regex = "\\d+".toRegex()
    val matches = regex.findAll(line)
    val rangeList : MutableList<IntRange> = mutableListOf()
    for (match in matches) {
        rangeList.add(match.range)
    }
    return rangeList
}

fun isNumberValid(range: IntRange, line:String , topLine: String?, bottomLine:String?): Boolean {
    val longRange: IntRange = IntRange(range.first - 1, range.last + 1)
    val lines: List<String?> = listOf(bottomLine, line, topLine)
    for (line in lines) {
        if (checkForSymbols(longRange, line)) {
            return true
        }
    }
    return false
}

fun checkForSymbols(range: IntRange, line: String?): Boolean {
    if (line.isNullOrBlank()) {
        return false
    }
    for (i in range) {
        val char: Char = if ((i < 0) or (i == line.length)) '.' else line[i]
        if ((char != '.') and !char.isDigit()) {
            return true
        }
    }
    return false
}

fun getValidNumbers(lines: List<String>) : MutableList<Int> {
    val numbers : MutableList<Int> = mutableListOf()
    val LINE_AMOUNT : Int = lines.count()
    val LINE_LENGTH : Int = lines[1].length
    for (i in 0 until LINE_AMOUNT) {
        val ranges: List<IntRange> = (getNumberRanges(lines[i]))
        for (range in ranges) {
            val topLine: String? = if (i == 0) null else lines[i - 1]
            val bottomLine: String? = if (i == LINE_AMOUNT - 1) null else lines[i + 1]
            if (isNumberValid(range, lines[i], topLine, bottomLine)) {
                numbers.add(lines[i].substring(range).toInt())
            }
        }
    }
    return numbers
}

fun main(args: Array<String>) {
    val lines = getLines("src/main/resources/input.txt")
    print(getValidNumbers(lines).sum())
}