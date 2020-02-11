#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")
(require "../include/cs151-image.rkt")

(define-struct MovieEdge
  ([actor1 : String]
   [movie : String]
   [actor2 : String]))

(define-type MovieGraph
  (Listof MovieEdge))

(define-type MST
  (U 'E Node))

(define-struct Node
  ([root : String]
   [before : MST]
   [after : MST]))

;; My code outputs the same list but in a different order than
;; the code on Piazza. It contains the same entries but in a different order
(define data-movie-edges
(list
 (MovieEdge "Tommy Lee Jones" "Men in Black" "Will Smith")
 (MovieEdge "Linda Fiorentino" "Men in Black" "Will Smith")
 (MovieEdge "Linda Fiorentino" "Men in Black" "Tommy Lee Jones")
 (MovieEdge "Chris Evans" "Captain America: The First Avenger" "Tommy Lee Jones")
 (MovieEdge "Hayley Atwell" "Captain America: The First Avenger"
            "Tommy Lee Jones")
 (MovieEdge "Hugo Weaving" "Captain America: The First Avenger"
            "Tommy Lee Jones")
 (MovieEdge "Chris Evans" "Captain America: The First Avenger" "Hayley Atwell")
 (MovieEdge "Chris Evans" "Captain America: The First Avenger" "Hugo Weaving")
 (MovieEdge "Hayley Atwell" "Captain America: The First Avenger" "Hugo Weaving")
 (MovieEdge "Hugo Weaving" "The Fellowship of the Ring" "Ian McKellen")
 (MovieEdge "Hugo Weaving" "The Fellowship of the Ring" "Liv Tyler")
 (MovieEdge "Cate Blanchett" "The Fellowship of the Ring" "Hugo Weaving")
 (MovieEdge "Ian McKellen" "The Fellowship of the Ring" "Liv Tyler")
 (MovieEdge "Cate Blanchett" "The Fellowship of the Ring" "Ian McKellen")
 (MovieEdge "Cate Blanchett" "The Fellowship of the Ring" "Liv Tyler")))

(: take (All (A) (Integer (Listof A) -> (Listof A))))
;; take n items from the front of the list
;; ex: (take 3 '(a b c d e f)) -> '(a b c)
;; no error if too many items are requested
(define (take n xs)
  (cond
    [(<= n 0) '()]
    [(empty? xs) '()]
    [else (cons (first xs)
                (take (sub1 n) (rest xs)))]))

(check-expect (take 3 '(a b c d e)) '(a b c))
(check-expect (take 0 '(a b c)) '())
(check-expect (take 1 '(a b c)) '(a))
(check-expect (take 99 '(x y z)) '(x y z))

(: drop (All (A) (Integer (Listof A) -> (Listof A))))
;; drop n items from the front of the list
;; ex : (drop 3 '(a b c d e f)) -> '(d e f)
;; no error if too many items are requested
(define (drop n xs)
  (cond
    [(<= n 0) xs]
    [(empty? xs) '()]
    [else (drop (sub1 n) (rest xs))]))

(check-expect (drop 3 '(a b c d e f)) '(d e f))
(check-expect (drop 99 '(a b c)) '())
(check-expect (drop 0 '(a b c)) '(a b c))



(: get-segment-len : Char (Listof Char) Integer -> Integer)
;; get-segment-len: computes the length of the first segment
;; in a list of characters
;; ex: (get-segment-len #\@ "abc@xy") -> 3
;; ex: (get-segment-len #\@ "xy") -> 2
;; parameters: target character and a list of characters
;; output: the number of characters before the target character
(define (get-segment-len c xs count)
  (match xs
    ['() count]
    [(cons f r) (if (char=? c f)
                   count
                   (get-segment-len c r (+ 1 count))
                    )]    
  )
)

(: split : Char String -> (Listof String))
;; split: chops a string at a given character into a list of strings
;; ex: (split #\@ "abc@de@xyz") -> (list "abc" "de" xyz")
;; parameters: a character and a starting string
;; output: a list of strings with the character removed
(define (split c str)
(local
  {(define list-chars (string->list str))
  }
  (match list-chars
    ['() '()]
    [else (cons
             (list->string (take (get-segment-len c list-chars 0) list-chars))
             (split c
                    (list->string (drop (+ 1 (get-segment-len c list-chars 0))
                    list-chars)))
           )]
  )
))
(check-expect (split #\@ "abc@de@xyz") (list "abc" "de" "xyz"))
(check-expect (split #\Z "abcdZdZxyz") (list "abcd" "d" "xyz"))

(: get-element (All (A) (Integer (Listof A) -> A)))
;; get-element: gets the element in a list at a given index
;; parameters: an integer index and a list of A
;; output: the element A at the given index in the list
(define (get-element num xs)
  (match xs
  [(cons f r) (if (<= num 0)
                  f
                  (get-element (- num 1) r)
                  )]
))
(check-expect (get-element 1 (list 1 2 3 4 5)) 2)
(check-expect (get-element 0 (list 1 2 3 4 5)) 1)
(check-expect (get-element 1 (list "a" "b" "c" "d")) "b")


(: construct-movie-graph ((Listof String) -> MovieGraph))
;; construct-movie-graph: creates a MovieGraph from a list of Strings
;; (lines of data)
;; parameters: List of Strings -> contain line entries for each movie
;; output: a MovieGraph containing the connections between actors
(define (construct-movie-graph xs)
  (match xs
  ['() '()]
  [(cons f r)
   (local
    {(: movie String)
     (define movie
       (get-element 0 (split #\@ f)))
     
     (: actors (Listof String))
     (define actors
        (split #\| (get-element 1 (split #\@ f))))
    }
    (if (string=? f "")
        (construct-movie-graph r)
        (append (movie-edges movie actors) (construct-movie-graph r)))
  )]
))
;; Tested visually by looking at the .png created by graphviz


(: movie-edges : String (Listof String) -> (Listof MovieEdge))
;; movie-edges: creates a list of MovieEdges from a given movie and its actors
;; parameters: a given movie and its actors
;; output: a list of MovieEdges representing the connections between those actors
(define (movie-edges movie actors)
  (local
   {(: make-edges : String (Listof String) -> (Listof MovieEdge))
    (define (make-edges actor actors)
      (match actors
      ['() '()]
      [(cons f r) (if (string<? actor f)
                      (cons (MovieEdge (string-trim actor) (string-trim movie)
                                      (string-trim f)) (make-edges actor r))
                      (cons (MovieEdge (string-trim f) (string-trim movie)
                                     (string-trim actor)) (make-edges actor r)))]
     ))
   }
   (match actors
   ['() '()]
   [(cons f r) (append (make-edges f r) (movie-edges movie r))]

  ))
)
;; Tested visually by looking at the .png created by graphviz


(: read-movie-data : String -> MovieGraph)
;; Creates a MovieGraph from a given file
;; parameters: the string location of the initial file
;; output: a MovieGraph using the data from that file
(define (read-movie-data str)
  (local
    {(define file (file->lines str))
    }
    (construct-movie-graph file)
))
(check-expect
(read-movie-data "movie.data")
data-movie-edges)

(: movie-graph->graphviz : MovieGraph -> String)
;; movie-graph->graphviz: creates a data file from a MovieGraph that contains the
;; graph data for that MovieGraph. Formatted so that graphviz can visualize the
;; data
;; parameter: MovieGraph
;; output: String containing graph data for a MovieGraph
(define (movie-graph->graphviz graph)
  (local
    {
     (define q (string #\"))
     (define nl (string-append (string #\\) (string #\n)))
    }
    (match graph
     ['() ""]
     [else (string-append
           "graph {\n  "
           (graphviz-entries graph)
           "}"
            )]
)))
;; Tested visually by looking at the .png created by graphviz

(: graphviz-entries : MovieGraph -> String)
;; graphviz-entries: creates the entries from a MovieGraph for the graphviz data
;; file
;; parameter: MovieGraph
;; output: String containing the entries for the graphviz data file
(define (graphviz-entries graph)
  (local
    {
     (define q (string #\"))
    }
    (match graph
     ['() ""]
     [(cons (MovieEdge a1 m a2) r)
       (string-append
       (string-append
        q a1 q " -- " q a2 q " [label=" q m q "];\n  "
       )
       (graphviz-entries r))]
)))
;; Tested visually by looking at the .png created by graphviz

;;(display-to-file (movie-graph->graphviz (read-movie-data "movie.data")) "movies.gv")
;;(display-to-file (movie-graph->graphviz (read-movie-data "movie2.data")) "movies2.gv")
(test)