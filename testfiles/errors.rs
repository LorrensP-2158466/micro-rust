
// not random but my optimizer doesn't inline, so it might as well be
fn random_bool() -> bool{
    true
}


fn main(){
    let x: i32;
    while false{
        x = 10;
        break;
    }
    let b = x;
    println!("{b}");
}
