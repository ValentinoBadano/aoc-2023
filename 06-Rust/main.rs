use std::fs::read_to_string;

fn ways_to_win(time: i32, distance: i32) -> i32 {
    let mut ways: i32 = 0;
    for time_pressed in 1..time {
        // dist reached is vel*(time - time pressed) but vel = time pressed
        let distance_reached = time_pressed*(time - time_pressed);
        //println!("{}", distance_reached);
        if distance_reached > distance {
            ways += 1;
        }
    }
    return ways;
}

fn main() -> std::io::Result<()> {
    let input = read_to_string("./input.txt")?;
    let words: Vec<&str> = input.split_whitespace().collect();
    let mut time: Vec<i32> = Vec::new();
    let mut distance: Vec<i32> = Vec::new();
    let length = 4;

    for i in 1..5 {
        time.push(words[i].parse().unwrap());
    }

    for i in 6..10 {
        distance.push(words[i].parse().unwrap());
    }

    for n in 0..length {
        let race_time = time[n];
        let race_dist = distance[n];
        println!("Race time: {} Race distance: {} Ways to win: {}", race_time, race_dist, ways_to_win(race_time, race_dist));
    }   

    return Ok(());
}