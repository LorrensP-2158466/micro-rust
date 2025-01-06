
// not random but my optimizer doesn't inline, so it might as well be
fn random_bool() -> bool{
    true
}


fn main(){
    let x;

    if random_bool(){
        x = 10;
    }else{
        x = 20;
    }
    x = 10;
    let b = x;

}
