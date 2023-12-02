# lectura del archivo
data <- readLines("sample.txt")

cube_limit = c(12, 13, 14)

get_id <- function(game) {
  id <- substr(c(game), 6, 6)
  return(id)
}

get_numbers <- function(game) {
  matches <- gregexpr("\\d+\\s+\\w+;?", game)

  return(matches)
}

get_handful <- function(game) {
  matches <- get_numbers(game)
  starts <- matches[[1]]
  attributes(starts) <- NULL
  lenghts <- lens <- attr(matches[[1]],'match.length')

  cubes <- c()
  for (i in matches) {
    append(cubes, substr(c(game), i, i + 2))
  }
  return (cubes)
}

sum <- 0
for (game in data) {
  values <- get_handful(game)
  print(values)
}

