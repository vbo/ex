data Tree a =
    Nil
  | Tree a (Tree a) (Tree a)

data Infinitable a =
    NegativeInfinity
  | Finite a
  | PositiveInfinity
    deriving (Ord, Eq, Show)

isBST :: (Ord a) => Tree a -> Bool
isBST node = _impl node NegativeInfinity PositiveInfinity
    where
    _impl :: (Ord a) => Tree a -> Infinitable a -> Infinitable a -> Bool
    _impl Nil _ _ = True
    _impl (Tree v ls rs) l r = between && (_impl ls l fv) && (_impl rs fv r)
        where fv = Finite v; between = fv > l && fv < r

example :: Tree Int
example =
    (Tree 20
        (Tree 10
            (Tree 5
                Nil
                Nil
            )
            Nil
        )
        (Tree 30
            (Tree 25
                (Tree 21
                    Nil
                    Nil
                )
                Nil
            )
            (Tree 40
                Nil
                Nil
            )
        )
    )

main = do
    print $ isBST example
