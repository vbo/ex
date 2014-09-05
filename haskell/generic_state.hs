-- Stateful: datatype of wrapped calculation
data Stateful statetype restype = Stateful { runState :: (statetype -> (restype, statetype)) }

-- Monad implementation
instance Monad (Stateful statetype) where
    return val = Stateful $ \inState -> (val, inState)
    sender >>= receiver = Stateful bound 
      where
        bound inState = (outResult, outState)
          where
            (interResult, interState) = runState sender inState
            (outResult, outState) = runState (receiver interResult) interState

-- Monad usage simplification
eval :: Stateful statetype restype -> statetype -> restype
eval comp input = result
  where (result, _) = runState comp input

exec :: Stateful statetype restype -> statetype -> statetype
exec comp input = lastState
  where (_, lastState) = runState comp input

-- Generic monadic helpers
get :: Stateful statetype statetype
get = Stateful $ \s -> (s, s)

set :: statetype -> Stateful statetype ()
set x = Stateful $ \s -> ((), x)

-- User-level code (lib)
type IntState = Int

add :: Int -> Stateful IntState ()
add x = do
    orig <- get
    set $ orig + x

type Stack a = [a]

pop :: Stateful (Stack a) a
pop = do
    orig <- get
    case orig of
        (x:xs) -> do
            set xs
            return x
        _      -> error "Pop from empty stack"

push :: a -> Stateful (Stack a) ()
push x = do
    orig <- get
    set $ x:orig

-- User-level code (script)
userCode :: Stateful IntState String
userCode = do
    start <- get
    if start < 42
        then do
            add $ 42 - start
            return "Fixed"
        else return "Already 42+"

userCode2 :: Stateful (Stack Int) ()
userCode2 = do
    top <- pop
    case top of
        42 -> do
            push 20
            push 22
        12 -> do
            next <- pop
            push next
            push next
        _ -> push 42

main = do
    print $ eval userCode 20
    print $ exec userCode 86
    print $ runState userCode 40

    print $ exec userCode2 [42]
    print $ exec userCode2 [12, 20]
    print $ exec userCode2 [7]
