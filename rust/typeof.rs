extern crate debug;

fn print_type_of<T>(_: &T) -> () {
    let type_name =
        unsafe {
            (*std::intrinsics::get_tydesc::<T>()).name
        };
    println!("{}", type_name);
}

fn main() -> () {
    let mut my_number = 32.90;
    print_type_of(&my_number);

    fn my_func(x: int) -> int { x + 1 }
    print_type_of(&my_func);

    print_type_of(&(|x: int| -> int { x + 1 }));

    print_type_of(&(vec!(1, 2, 4)));

    println!("{:?}", (|x: int| -> int { x + 1 }));
}
