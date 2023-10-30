import System.Environment
import System.Posix.Process
import System.Posix.Types
import System.IO

main :: IO ()
main = do
    args <- getArgs
    myPID <- getProcessID
    putStr "HOLA COMO ESTAS "
    mapM_ putStrLn args
    putStrLn $ "El PID es: " ++ show myPID
