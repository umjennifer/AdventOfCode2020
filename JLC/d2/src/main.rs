use std::io;
use std::io::prelude::*;
use regex::Regex;
struct Rules {
    min: i32,
    max: i32,
    ch: &str,
    st: &str,
}

fn get_fake_lines() -> Vec<String> {
    vec![
        String::from("2-8 t: pncmjxlvckfbtrjh"),
        String::from("8-9 l: lzllllldsl"),
        String::from("3-11 c: ccchcccccclxnkcmc"),
    ]
}

fn get_real_lines(vec: &mut Vec<String>) {
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let x = line.unwrap();
        vec.push(x);
    }
}

fn decompose(input: String, reg: &regex::Regex) -> Rules {
    let a = reg.captures(&input).unwrap();
    let min: i32 = a.get(1).unwrap().as_str().parse::<i32>().unwrap();
    let max: i32 = a.get(2).unwrap().as_str().parse::<i32>().unwrap();
    let ch: &str = &a.get(3).unwrap().as_str();
    let st: &str = &a.get(4).unwrap().as_str();
    Rules{min: min, max: max, ch: ch, st: st}
}

fn check_line_policy_part_a(rules: Rules) -> bool {
    let mut count = 0;
    for c in rules.st.chars() {
        if c.to_string() == rules.ch {
            count += 1;
        }
    }
    if count <= rules.max && count>= rules.min {
        return true;
    }
    return false;
}

fn main(){
    let mut vec: Vec<String> = Vec::new();
    get_real_lines(&mut vec);
    let reg: Regex = Regex::new(r"(\d{1,3})-(\d{1,3}) (\D): (\S*)").unwrap();
    let mut part_a_truths = 0;
    let mut part_b_truths = 0;
    for line in vec{
        let rules: Rules = decompose(line, &reg);
        if check_line_policy_part_a(rules){
            part_a_truths += 1;
        }
    }
    println!("{}", part_a_truths);
}
