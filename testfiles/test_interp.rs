
fn foo() -> bool{
    if true {
        true
    }else{
        10
    }
}


fn main(){
    let x = foo();
    println!("{x}");
}