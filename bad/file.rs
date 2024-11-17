pub enum LinkedList<T>{
    Empty(),
    Node(T, LinkedList<T> next)
}



impl<T> LL<T> for LinkedList<T>{
    fn new() -> Self{
        Empty()
    }

    fn add(self, T x) -> Self{
        Node(x, self)
    }
}

fn main() -> Result<(), ()>
{
    println!("Hello World");
    LinkedList<u8> ll =
    Ok(())
}
