use std::gc::{Gc, GC};

struct Point {x: f32, y: f32}

fn prnt(p: &Point) {
    println!("{} {}", p.x, p.y);
}

fn main() {
    let p: Gc<Point> = box (GC) Point {x: 5.0, y: 1.0};
    let p1 = p;
    prnt(p1);
    prnt(p);
}
