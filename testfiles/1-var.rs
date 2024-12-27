
fn main(){
    let x = 11;
    let y = 12;
    let mut result = 0;
    
    if x > 10 {
        if y > 5 {
            result = x + y;
        } else {
            result = x - y;
        }
    } else {
        result = x * 2;
    }

    let mut i = 0;
    while i < y && result < 50 {
        result += 1;
        i += 1;
    }
    
    if result > 100 {
        result = 100;
    }
    println!("{result}");
}