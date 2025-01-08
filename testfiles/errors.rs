

// not random but my optimizer doesn't inline, so it might as well be
fn random_bool() -> bool{
    true
}

fn unintialized(){
                // { }
    let mut x; // {  }
    if random_bool(){
        x = 10; // { x } | { }
    }else{}; // {} | { x }
    let b = x; // { x? } | { } = x != 
    println!("hello world")
}

fn assign_to_immutable(){
                // {}
    let x = 10; // {x }
    if random_bool(){

    }else{

    };
    x = 30;
}

fn unintialized_used(){
    let x: i32;
    // this can't be
    let b = x;
}

fn complex_code_paths(){
    let  x;
    if random_bool(){
        x = 10
    }
    else if random_bool(){
        if random_bool(){
            x = 20
        }else{ // this branch is run and x is not init
            x = 40
        }
    }else{ // but for some reason i the compiler tells me about this branch as well
        // x = 40 // but if i do x = 40; it doesn't tell me about this branch
    };
    let b = x;
}

fn type_error(){
    let x = (10, 20);

    let y: bool = x.1;
}


fn arg_immutable(x: i32){
    x += 1;
}

fn suggestion_for_init(){
    let x: (i32, bool, u64);

    let b = x;
}

fn main(){}
