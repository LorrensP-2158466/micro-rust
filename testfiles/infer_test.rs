
fn foo(x: i64) {
    return;
}

fn main() {
    let a = 5;
    let b = 5;
    let c = a == b;
    foo(a);
    let d: i32 = 5;
    let e = a == d;
}