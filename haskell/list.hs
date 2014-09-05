import Prelude hiding (map, reverse, foldl, foldr, take, takeWhile, last, tail, init, length, concat, and, or, any, all, iterate)

data List a = Nil | Cons a (List a) deriving (Show)

-- |Applies function f to each element in the list
-- returning list of results of this applications
map :: (a -> b) -> List a -> List b
map _  Nil        = Nil
map f (Cons x xs) = Cons (f x) (map f xs)

reverse :: List a -> List a
reverse xs = _reverse xs Nil
  where 
    _reverse xs ac = case xs of
        Nil        -> ac
        Cons x xs -> _reverse xs (Cons x ac)

foldl :: (a -> b -> a) -> a -> List b -> a
foldl f z xs = case xs of
    Nil       -> z
    Cons x xs -> foldl f (f z x) xs

foldr :: (b -> a -> a) -> a -> List b -> a
foldr f z xs = case xs of
    Nil       -> z
    Cons x xs -> f x (foldr f z xs)

range :: (Num a, Ord a) => a -> a -> a -> List a
range fst step lst = if (fst <= lst) then Cons fst (range (fst + step) step lst) else Nil

open_range :: (Num a, Ord a) => a -> a -> List a
open_range fst step = Cons fst $ open_range (fst + step) step

take :: (Num a, Eq a) => a -> List a -> List a
take 0 _           = Nil
take _ Nil         = Nil
take n (Cons x xs) = Cons x $ take (n - 1) xs

takeWhile :: (a -> Bool) -> List a -> List a
takeWhile pred xs = case xs of
    Nil       -> Nil
    Cons x xs -> if pred x then Cons x $ takeWhile pred xs else Nil

head :: List a -> a
head Nil        = error "List: head from empty list"
head (Cons x _) = x

last :: List a -> a
last Nil          = error "List: last from empty list"
last (Cons x Nil) = x
last (Cons x xs)  = last xs

tail :: List a -> List a
tail Nil         = error "tail from empty list"
tail (Cons x xs) = xs
    
init :: List a -> List a
init Nil         = error "init from empty list"
init (Cons x Nil) = Nil
init (Cons x xs) = Cons x $ init xs

null :: List a -> Bool
null Nil = True
null _   = False

length :: List a -> Int
length Nil = 0
length (Cons _ xs) = 1 + length xs

append :: List a -> List a -> List a
append Nil ys         = ys
append (Cons x xs) ys = Cons x $ append xs ys

intersperse :: a -> List a -> List a
intersperse _ Nil = Nil
intersperse v xs@(Cons x Nil) = xs
intersperse v (Cons x xs)  = Cons x . Cons v $ intersperse v xs

concat :: List (List a) -> List a
concat xss = _impl xss Nil
  where
    _impl Nil           a = a
    _impl (Cons xs xss) a = append xs $ _impl xss a

any :: (a -> Bool) -> List a -> Bool
any pred xs = case xs of
    Nil         -> False
    (Cons x xs) -> if pred x then True else any pred xs

all :: (a -> Bool) -> List a -> Bool
all pred xs = case xs of
    Nil         -> True
    (Cons x xs) -> if not . pred $ x then False else all pred xs

and :: List Bool -> Bool
and = not . any (==False)

or :: List Bool -> Bool
or = any (==True)

iterate :: (a -> a) -> a -> List a
iterate f x = Cons x $ iterate f $ f x

main = do
    let lst123 = Cons 1 . Cons 2 . Cons 3 $ Nil
    let lst456 = Cons 4 . Cons 5 . Cons 6 $ Nil
    print $ map (+1) $ lst123
    print $ reverse $ lst123
    print $ foldl (+) 0 $ lst123
    print $ foldr (+) 0 $ lst123
    print $ range 1 1 5
    print $ take 5 $ open_range 1 1
    print $ take 5 $ foldr Cons Nil $ open_range 1 1
    print $ takeWhile (<100) $ open_range 1 5
    print $ last lst123
    print $ append lst123 $ range 1 1 5
    print $ intersperse 10 $ lst123
    print $ concat $ Cons lst123 . Cons lst456 $ Nil
    print $ and $ Cons True . Cons True . Cons False $ Nil
    print $ any (<6) $ open_range 1 1
    print $ all (<6) $ range 1 1 10
    print $ all (<6) $ open_range 1 1
    print $ take 5 $ iterate (+1) 1
