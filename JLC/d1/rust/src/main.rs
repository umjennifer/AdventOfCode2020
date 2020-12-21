use std::io;
use std::io::prelude::*;
use std::collections::HashMap;

struct IndexValue {
    index: usize,
    value: i32,
}

fn load_vector_from_stdin(vec: &mut Vec<i32>){
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let x = line.unwrap().parse::<i32>().unwrap();
        vec.push(x);
    }
}


fn find_pair_from_list_that_sums_to_value(list: &Vec<i32>, expected: i32) -> Result<(i32, i32), &'static str> {
    for (i1, v1) in list.iter().enumerate() {
        for (i2, v2) in list.iter().enumerate() {
            if i1 != i2 && v1 + v2 == expected {
                return Ok((*v1, *v2));
            }
        }
    }
    return Err("Nothing good happened");
}


fn find_triplet_from_list_that_sums_to_value(list: &Vec<i32>, expected: i32) -> Result<(i32, i32, i32), &'static str> {
    let mut my_map = HashMap::new();
    for (i1, v1) in list.iter().enumerate() {
        for (i2, v2) in list.iter().enumerate() {
            if i1 != i2 {
                let iv1 = IndexValue { index: i1, value: *v1 };
                let iv2 = IndexValue { index: i2, value: *v2 };
                my_map.insert(v1 + v2, (iv1, iv2));
            }
        }
    }
    for (i1, v1) in list.iter().enumerate() {
        let needed_val: i32 = expected - v1;
        match my_map.get(&needed_val){
            Some((i, j)) => {
                if i1 != i.index && i1 != j.index{
                    return Ok((i.value, j.value, *v1));
                }
            },
            _ => continue
        }
    }
    return Err("Nothing good happened");
}


fn main(){
    let mut list = vec![];
    load_vector_from_stdin(&mut list);
    // Part 1
    match find_pair_from_list_that_sums_to_value(&list, 2020){
        Ok(t) => {
            println!("{:?}", t);
            let product = t.0 * t.1;
            println!("{:?}", product);
        },
        Err(e) => println!("{:?}", e),
    }

    // Part 2
    match find_triplet_from_list_that_sums_to_value(&list, 2020){
        Ok(t) => {
            println!("{:?}", t);
            let product = t.0 * t.1 * t.2;
            println!("{:?}", product);
        },
        Err(e) => println!("{:?}", e),
    }

}
