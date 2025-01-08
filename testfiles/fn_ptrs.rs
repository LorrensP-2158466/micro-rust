

fn foo(x: i32, y: i32) -> i32{
    x + y
}

fn bar(x: i32, y: i32) -> i32{
    x + y
}

fn main(){
    /// hello world
    let mut f: fn(_, _) -> _ = foo;
    let x = f(10, 20);
    println!("{x}");
}