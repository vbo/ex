-- Pretty standard foldr implementation:
-- like in standard library
foldrLazy :: (a -> b -> b) -> b -> [a] -> b
foldrLazy f = impl
  where
    impl z []     = z
    impl z (x:xs) = f x $ (impl z xs)

-- Same thing but strict on accumulator
foldrStrict :: (a -> b -> b) -> b -> [a] -> b
foldrStrict f = foldrLazy f'
  where f' x z = f x $! z

main = do
    -- Test foldr implementations by trying to take first
    -- five elems from reconstructed infinite list
    let test foldrImpl = putStrLn . show . take 5 $ foldrImpl (:) [] [1..]
    -- Should work fine for normal forldr
    test foldrLazy
    -- The following should lead to stack space overflow
    -- because recursive call evaled strict (due to $!)
    -- trying to fold infinite list entirely
    test foldrStrict
