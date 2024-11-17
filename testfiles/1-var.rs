

fn foo() -> impl Debug{
    return "Hello";
}


fn main(){
    let x: OpaqueType(Debug) = foo();
    dbg!(x); // "Hello"
}
