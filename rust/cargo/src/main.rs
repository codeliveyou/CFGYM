use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}

fn main() {

    let my_string = String::from("hello world");

    let word = first_word(&my_string[0..6]);
    let word = first_word(&my_string[..]);
    let word = first_word(&my_string);

    let my_string_literal = "hello world";

    let word = first_word(&my_string_literal[0..6]);
    let word = first_word(&my_string_literal[..]);

    let word = first_word(my_string_literal);

    println!("Guess the number!");
    

    let secret_number = rand::thread_rng().gen_range(1..=100);
    println!("Secret number is {}", secret_number);

    loop {
        println!("Input your guess!");
        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("You guessed: {guess}");

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
    
}
