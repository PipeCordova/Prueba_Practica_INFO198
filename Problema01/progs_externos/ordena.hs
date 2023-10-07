import System.Environment
import Data.List
import System.Posix.Process
import System.Posix.Types
import System.IO

main :: IO ()
main = do
    args <- getArgs
    myPID <- getProcessID
    let vectorEntrada = map read args :: [Int]
        vectorOrdenado = sort vectorEntrada
    putStr "Vector de entrada: "
    print vectorEntrada
    putStr "Vector ordenado: "
    print vectorOrdenado
    putStrLn $ "El PID es: " ++ show myPID
