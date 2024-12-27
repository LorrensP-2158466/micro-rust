

fn foo(x: i8, y: i8) -> i8{
    x - y
}

fn main(){
    let x = foo(10, 20);
    x += 10;
    println!("{x}");
}