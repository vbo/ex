use stack::Stack;

mod stack {
    use std::mem::replace;

    #[deriving(Show)]
    enum LinkedList<T> { Nil, Cons(T, Box<LinkedList<T>>) }

    #[deriving(Show)]
    pub struct Stack<T> { vals: LinkedList<T> }

    impl<T> Stack<T> {
        pub fn new<T>() -> Stack<T> {
            Stack::<T>{ vals: Nil::<T> }
        }

        pub fn push<T>(&mut self, v: T) {
            let vals = replace(&mut self.vals, Nil);
            replace(&mut self.vals, Cons(v, box vals));
        }

        pub fn head<'a, T>(&'a self) -> Option<&'a T> {
            match self.vals {
                Nil => None,
                Cons(ref x, _) => Some(x)
            }
        }

        pub fn pop<T>(&mut self) -> Option<T> {
            let vals = replace(&mut self.vals, Nil);
            let (new_vals, head) =
                match vals {
                    Nil => (Nil, None),
                    Cons(x, xs) => (*xs, Some(x))
                };
            replace(&mut self.vals, new_vals);
            head
        }
    }
}

fn main() {
    let mut a : Stack<int> = Stack::<int>::new();
    a.push(42);
    a.push(45);
    println!("In: {}", a);
    {
        let h : Option<&int> = a.head();
        println!("He: {}", h);
    }
    let p : Option<int> = a.pop();
    println!("Po: {}", p);
    println!("Af: {}", a);
}
