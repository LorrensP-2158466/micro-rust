


fn bar(){
    println!("this cant be");
}


fn foo() -> fn() {

    bar
}



fn main(){  
    let f: fn() -> _ = foo;
    f()();
}