fn main()
{
  let x = 20; // x1
  {
    let x = 3; // x2
    x + 1
  };
  // blocks are expressions
  // (list of statements followed by expression) 
  // if no final expression: value is ()
  println!("{x}");
}
