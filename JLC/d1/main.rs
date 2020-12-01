use std::io;
use std::io::prelude::*;

fn load_vector_from_stdin(vec: &mut Vec<i32>){
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let x = line.unwrap().parse::<i32>().unwrap();
        vec.push(x);
    }
}


fn find_pair_from_list_that_sum_to_value(list: Vec<i32>, expected: i32) -> Result<(i32, i32), &'static str> {
    for (i1, v1) in list.iter().enumerate() {
        for (i2, v2) in list.iter().enumerate() {
            if i1 != i2 && v1 + v2 == expected {
                return Ok((*v1, *v2));
            }
        }
    }
    return Err("Nothing good happened");
}


fn main(){
    let mut list = vec![];
    load_vector_from_stdin(&mut list);
    match find_pair_from_list_that_sum_to_value(list, 2020){
        Ok(t) => {
            println!("{:?}", t);
            let product = t.0 * t.1;
            println!("{:?}", product);
        },
        Err(e) => println!("{:?}", e),
    }

}
