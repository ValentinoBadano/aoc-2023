data <- readLines("input.txt")

cube_limit = c(12, 13, 14)

get_id <- function(game) {
  id <- regexec("Game\\s(\\d+)", game)
  return(as.numeric(regmatches(game, id)[[1]][2]))
}

is_color_number_invalid <- function(number, color) {
  if (number > 12 & color == "r") {
    return (TRUE)
  } else if (number > 13 & color == "g") {
     return (TRUE)
  } else if (number > 14 & color == "b") {
     return (TRUE)
  }
  return (FALSE)
}

is_game_valid <- function(game) {
  matches <- gregexpr("\\d+\\s+?", game)
  starts <- matches[[1]]
  attributes(starts) <- NULL
  lengths <- lens <- attr(matches[[1]],'match.length')
  for (i in 1:length(starts)) {
    length <- as.numeric(lengths[i])
    value <- substr(c(game), starts[i], starts[i]  + length - 2)
    color <- substr(c(game), starts[i] + 2, starts[i]  + length)
    if (is_color_number_invalid(as.numeric(value), trimws(color))) {
      return (FALSE)
    }
  }
  return (TRUE)
}

sum <- 0
for (game in data) {
  print(game)
  if (is_game_valid(game)) {
     sum <- sum + get_id(game)
  }
}
print(sum)
