fn main() {
    let t1 = (1, true);

    let nested = ((1, 2), (false, 10));

    let sum = add_tuple((10, 20));
    println!("{sum}");

    let t2 = ((1, 2), (3, 4));

    let mut mix = (10, true, (3, 4));
    mix.0 += 5;
}

fn add_tuple(pair: (i32, i32)) -> i32 {
    pair.0 + pair.1
}


fn test_shift_reduce(){
    let tup = ((true, true), false, true, 10);

    if !tup.0.0{
        println!("its working");
    }else{
        
    };
}