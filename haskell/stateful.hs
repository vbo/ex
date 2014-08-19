import Control.Applicative

-- Define State type
data CompState = CompState
    { compVal :: Int
    , compLog :: [String]
    } deriving (Show)

setCompVal :: Int -> CompState -> CompState
setCompVal v s = s { compVal = v }

setCompLog :: [String] -> CompState -> CompState
setCompLog v s = s { compLog = v }

-- Type wrapper for state-operating functions CompState
newtype CompAction rettype = CompAction
    { compActionImpl :: CompState -> (rettype, CompState) }

-- Execute stateful action on given state
execCompAction :: CompAction rettype -> CompState -> (rettype, CompState)
execCompAction operation state = compActionImpl operation $ state

-- Implement Monad typeclass for stateful actions
instance Monad CompAction where
    return x = CompAction $ \s -> (x, s)
    (>>=) act receiver = CompAction $ \s ->
        let (out, s') = execCompAction act s in
            execCompAction (receiver out) s'

-- Implement Functor and Applicative in monadic style
instance Functor CompAction where
    fmap f act = act >>= return . f

instance Applicative CompAction where
    pure = return
    actF <*> actX = actF >>= flip fmap actX

-- Actions on state as a whole
getCompState :: CompAction CompState
getCompState = CompAction $ \s -> (s, s)

putCompState :: CompState -> CompAction ()
putCompState s' = CompAction $ \s -> ((), s')

modCompState :: (CompState -> CompState) -> CompAction ()
modCompState f = CompAction $ \s -> ((), f s)

-- Operations on particular state fields
getVal :: CompAction Int
setVal :: Int -> CompAction ()
setLog :: [String] -> CompAction ()
addLog :: String -> CompAction ()

-- func-style impl
getVal      = CompAction $ \s -> (compVal s, s)
setVal val  = CompAction $ \s -> ((), setCompVal val s)
setLog log  = CompAction $ \s -> ((), setCompLog log s)
addLog line = CompAction $ \s -> ((), setCompLog (line:compLog s) s)

-- reimpl in applicative/monadic style
getVal2      = compVal <$> getCompState
getLog2      = compLog <$> getCompState
setVal2 val  = setCompVal val <$> getCompState
setLog2 log  = setCompLog log <$> getCompState
addLog2 line = (line:) <$> getLog2 >>= setLog

-- Example user-level operation
operateOnState :: CompAction Int
operateOnState = do
    initVal <- getVal
    let logLine = "Initial val: " ++ (show initVal)
    addLog logLine
    (+) <$> getVal <*> getVal >>= setVal
    summed <- show <$> getVal
    addLog $ "Set to " ++ summed
    val <- getVal
    setVal $ val + 2
    result <- getVal
    addLog $ "Result: " ++ (show result)
    return result

main :: IO ()
main = do
    print "Hell"
    let op1 = operateOnState
    let initState = CompState 20 ["Start!"]
    let result = execCompAction op1 initState
    print result
  

