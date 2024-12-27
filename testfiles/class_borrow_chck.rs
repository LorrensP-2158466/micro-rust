fn main(){

    let x = 10;
    let mut ref_val = &x;
    {
        let y = 10;
        ref_val = &y;
    }

    println!("{ref_val}");
}