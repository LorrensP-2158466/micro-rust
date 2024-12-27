
fn fib(n: u32) -> u32 {
    if n <= 1 {
        n
    } else {
        fib(n - 1) + fib(n - 2)
    }
}


// A large while loop summing numbers and doing arithmetic operations.
fn large_loop(n: i32) -> i32 {
    let mut sum = 0;
    let mut i = 0;
    while i < n {
        sum += i * 2;  // Arithmetic operation inside the loop
        if (n / 2) * 2 == n {
            sum -= 1;  // Conditional change to the sum
        } else {
            sum += 3;  // Another branch for the conditional
        }
        i += 1;
    }
    sum
}


fn main() {
    let mut x = 0;
    while x <= 10000{
        let result = large_loop(x);
        println!("large_loop({x}) = {result}");
        x += 1;
    }
}