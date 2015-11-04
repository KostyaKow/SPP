--haskell version of lisp interpreter

--parsef parsed
--foldl f collect []     = collect
--foldl f collect (x:xs) = foldl f (f collect x) xs

--data Lexeme a = O | C | STR String | N a | SYM String deriving (Show)
--data Lexeme = OpenParent | CloseParent | Symbol
data Lexeme = O | C | S String deriving (Show, Eq)

tokenize :: String -> [Lexeme]
tokenize s = tokenize' s []
--tokenize' input currLex
tokenize' :: String -> String -> [Lexeme]
tokenize' [] [] = []
tokenize' [] lex = [S lex]
tokenize' (x:xs) lex
   | x == ' ' && lex /= [] = S lex : tokenize' xs []
   | x == ' '  = tokenize' xs []
   | x == '('  = O : tokenize' xs []
   | x == ')' && lex /= [] = S lex : C : tokenize' xs []
   | x == ')'  = C : tokenize' xs []
   | otherwise = tokenize' xs (lex ++ [x])

getLevel :: Int -> [Lexeme] -> Maybe Int
getLevel pos lst = f lst 0 0
   where f xs curPos deep -- f [] _ _ = Nothing
            | length xs == 0  = Nothing
            | curPos == pos   = Just deep
            | head xs == O    = f (tail xs) (curPos+1) (deep+1)
            | head xs == C    = f (tail xs) (curPos+1) (deep-1)
            | otherwise       = f (tail xs) (curPos+1) deep

--left here
findMatching :: Int -> [Lexeme] -> Maybe Int
findMatching pos lst = findMatching' pos (getLevel pos lst) lst
findMatching' pos openParen lst
   where
      openDepth = getLevel pos lst


--data Sexp = Atom String | Cons Sexp Sexp | List [Sexp] | Nil | Bad deriving (Show)
data Sexp = Atom String | Cons Sexp Sexp | Nil | Bad deriving (Show)

parse :: [Lexeme] -> Sexp
parse [] = Bad
parse xs = parse' xs

parse' [S s] = Atom s
parse' (O:S s:xs) = Cons (Atom s) (parse' xs)
--parse' (C:xs) =



--( + 3 (+ 3 5) 34)
{- main = do
   --putStrLn "$"
   s <- getLine
   lexemes <- return $ map (\x -> x ++ ".") $ tokenize s
   mapM_ putStrLn lexemes
   main
-}

