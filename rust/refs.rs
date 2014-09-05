use std::fmt::Show;

// type_of
fn type_of<T>(_: &T) -> &'static str {
    unsafe {
        (*std::intrinsics::get_tydesc::<T>()).name
    }
}

fn print_fixed(vec: &[int]) {
    for i in vec.iter() {
        println!("{}", i);
    }
}

fn print_uniq<T: Show>(vec: &Vec<T>) {
    for i in vec.iter() {
        println!("{}", i);
    }
}

fn inc(x: &mut int) { *x += 1; }

fn vrange(s: int, e: int) -> Vec<int> {
    let mut v = Vec::new();
    for i in range(s, e + 1) {
        v.push(i);
    }
    return v;
}

fn sum(x: int, y: int) -> int { x + y }

fn main () {
    let vec: &[int] = [1i, 2, 3];
    println!("{}", type_of(&vec));
    print_fixed(vec);

    let vec2: Vec<int> = vec!(4, 5, 6);
    println!("{}", type_of(&vec2));
    print_uniq(&vec2);

    let vec3 = vrange(1, 10);
    println!("Range");
    print_uniq(&vec3);
    println!("Range slice");
    print_fixed(vec3.slice(5, 7));

    let mut x = 1;
    println!("{}", type_of(&x));

    inc(&mut x);
    inc(&mut x);
    println!("{}", x);

    inc(&mut x);
    inc(&mut x);
    println!("{}", x);

    let str1: &str = "Hello world";
    println!("{}", type_of(&str1));

    let str2: &'static str = "Hello world";
    println!("{}", type_of(&str2));
    println!("{}, {}", str1, str2);

    let ostr = "Hello world".to_string();
    println!("{}", type_of(&ostr));

    let vrange_func = vrange;
    println!("{}", type_of(&vrange_func));

    let sum_func = sum;
    println!("{}", type_of(&sum_func));

    fn hl(f: (fn(int, int) -> int), x: int, y: int) -> int {
        f(x, y)
    }

    println!("{}", type_of(&hl));
    println!("{}", hl(sum_func, 40, 2));
}
