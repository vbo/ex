fn mut1(a : &mut int) {
    *a += 1;
}

fn mut2(mut a: int) -> int {
    a += 1;
    return a;
}

fn main() {
    let mut x: int = 10;
    mut1(&mut x);
    println!("{}", x);

    let x: int = 100;
    let x1: int = mut2(x);
    println!("{}->{}", x, x1);
}
