#![feature(macro_rules)]

use test::Relation;
use test::Monster;
use test::Test;

macro_rules! ns_enum(
    ($name:ident #[deriving($($der:ident),*)] $im:item) => (
        pub type $name = self::$name::$name;
        mod $name {
            #[deriving($($der),*)]
            $im
        }
    );
)

macro_rules! ns_enum2(
    (
        #[$at:meta]
        pub enum $name:ident {
            $(
                $(#[$variant_at:meta])*
                $variant:ident
            ),*
        }
    ) => (
        pub type $name = self::$name::$name;
        mod $name {
            #[$at]
            pub enum $name {
                $(
                    $(#[$variant_at:meta])*
                    $variant
                ),*
            }
        }
    );
)

mod test {
    pub type Relation = self::Relation::Relation;
    mod Relation {
        #[deriving(Show)]
        pub enum Relation {
            Friend,
            Foe
        }
    }
    ns_enum!(Monster
        #[deriving(Show)]
        pub enum Monster {
            Vampire, Zombie
        }
    )
    ns_enum2!(
        #[deriving(Show)]
        pub enum Test {
            Pass, Fail
        }
    )
}

fn main() {
    let rel: Relation = Relation::Friend;
    println!("{}", rel);
    let mon: Monster = Monster::Zombie;
    println!("{}", mon);
    let mon: Test = Test::Pass;
    println!("{}", mon);
}
