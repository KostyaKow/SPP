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
            | curPos == pos && head xs == C  = Just (deep-1)
            | curPos == pos   = Just deep
            | head xs == O    = f (tail xs) (curPos+1) (deep+1)
            | head xs == C    = f (tail xs) (curPos+1) (deep-1)
            | otherwise       = f (tail xs) (curPos+1) deep

el :: Maybe Int -> Int
el (Just a) = a
el Nothing = 0

--Find matching close brace for current depth
--for posOpen, you gotta use positionOfParen+1
findMatching :: Int -> [Lexeme] -> Maybe Int
findMatching posOpen lst = f posOpen (drop posOpen lst) openDepth
   where openDepth = el $ getLevel posOpen lst
         f _ [] _ = Nothing
         f pos xs depth
            | depth == openDepth && head xs == C = Just pos
            | head xs == C = f (pos + 1) (tail xs) (depth-1)
            | head xs == O = f (pos + 1) (tail xs) (depth+1)
            | otherwise = f (pos + 1) (tail xs) depth
         -- f pos xs depth

--data Sexp = Atom String | Cons Sexp Sexp | List [Sexp] | Nil | Bad deriving (Show)
data Sexp = Atom String | Cons Sexp Sexp | Nil | Bad deriving (Show)

parse :: [Lexeme] -> Sexp
parse [] = Bad
parse xs = parse' xs

parse' [S s] = Atom s
parse' lst@(O:xs) = Cons (Atom s) (parse' xs)

--parse' (C:xs) =
--findMatching 0 $ tokenize "(+ 3 5 32)"

--( + 3 (+ 3 5) 34)
{- main = do
   --putStrLn "$"
   s <- getLine
   lexemes <- return $ map (\x -> x ++ ".") $ tokenize s
   mapM_ putStrLn lexemes
   main
-}

