
fn add(){}

fn main(){
    let x = {
        let a = 10;
        let b = 20;
        
        fn add(a: i32, b: i32) -> i32{
            a + b
        }
        
        add(a, b)
    };
    
    fn add(a: i32, b: i32) -> i32 { a + b + 10 }
    
    let y = add(x, 10);
}