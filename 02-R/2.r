library(stringr)

data <- readLines("input.txt")

get_power_set <- function(list) {
    power_set <- 1
    for (element in list) {
        power_set <- power_set * element
    }
    return (power_set)
}

split_cube <- function(cube){
    cube_list <- list(value=0, color="")
    split <- str_split(cube, " ")
    split <- split[[1]]
    cube_list["value"] <- split[1]
    cube_list["color"] <- split[2]
    return (cube_list)
}

get_max <- function(game) {
    max <- list(red = 0,
                    green = 0,
                    blue = 0)
    
    cubes <- split_game(game)
    for (cube in cubes[[1]]) {
       actual <- split_cube(cube)
       actual_color <- actual["color"]
       actual_value <- as.numeric(actual["value"])
       if (max[actual_color[[1]]] < actual_value[[1]]) {
          max[actual_color[[1]]] <- actual_value[[1]]
       }
    }
    # print(as.numeric(max))
    return (as.numeric(max))
}

split_game <- function(game) {
    string <- ((str_split(game, ": "))[[1]])
    string <- string[2]
    string <- (str_split(string, ", |; "))
    string <- lapply(string, sort, decreasing=TRUE)
    return(string)
}

sum <- 0
for (game in data) {
    print(game)
    max <- get_max(game)
    sum <- sum + get_power_set(max)
}
print(sum)
