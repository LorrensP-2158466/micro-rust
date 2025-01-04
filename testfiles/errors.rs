
fn foo() -> bool{
    let x = 10;
    x
}

fn main(){
    let x: i32 = {
        let y: usize = 10; {let z = y; z}};
}
