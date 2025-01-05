
// not random but my optimizer doesn't inline, so it might as well be
fn random_bool() -> bool{
    true
}


fn main(){
    let x: i32;
    if random_bool(){
        x = 10;
    }else{
    };
    let b = x;
}
