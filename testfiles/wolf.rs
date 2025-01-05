fn a() -> i32 {
    let a = 3;
    let b = {
        a + 5
    } - 3;
    b
}

fn main() {
    let x = a();
    println!("{x}");
}