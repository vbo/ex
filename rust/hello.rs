#![feature(macro_rules)]

use state::State;

// debug helper
macro_rules! dbug(($($a:expr),*) => { println!(concat!($(stringify!($a), " = {}, "),*), $($a),*); }) 

// define State and related operations
mod state {
    #[deriving(Show)]
    pub struct State {
        pub val: int,
        log: Vec<String>
    }

    impl State {
        pub fn new(val: int) -> State {
            State { val: val, log: Vec::new() }
        }

        pub fn log_str(&mut self, log: &str) {
            self.log.push(String::from_str(log));
        }

        pub fn log_val(&mut self) {
            let log = format!("Val: {}", self.val);
            self.log_str(log.as_slice());
        }
    }
}

// user-level function working on state
fn mod_state(s: &mut State) {
    s.log_str("Before mod");
    s.log_val();
    s.val = 42;
    s.log_str("After mod");
    s.log_val();
}

fn mod_tuple(t: &mut (String, int)) {
    match *t {
        (ref mut x, ref y) => {
            *x = *x + "Hel".to_string();
            dbug!(y);
        }
    };
}

fn print_tuple<T: std::fmt::Show, S: std::fmt::Show>(&(ref x, ref y): &(T, S)) {
    println!("{}:{}", x, y);
}

fn strs_to_strings(v: &[&str]) -> Vec<String> {
    let mut r = Vec::new();
    for i in v.iter() {
        r.push(i.to_string());
    };
    return r;
}

// top-level code
fn main() {
    let strs = vec!["A", "B", "Hell"];
    dbug!(strs);
    let strings = strs_to_strings(&strs);
    dbug!(strings);
    let mut t = ("Hel".to_string(), 2i);
    mod_tuple(&mut t);
    print_tuple(&t);
    let d = 1i;
    let mut s = State::new(13);
    s.log_str("Initial");
    s.log_val();
    mod_state(&mut s);
    s.val = 86;
    s.log_str("Finish");
    s.log_val();
    dbug!(d, s);
}
