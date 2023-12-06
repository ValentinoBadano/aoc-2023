use std::fs::read_to_string;

fn main() -> std::io::Result<()> {
    let input = read_to_string("./sample.txt")?;
    println!("{}", input);
    println!("Hola, mundo");
    return Ok(());
}