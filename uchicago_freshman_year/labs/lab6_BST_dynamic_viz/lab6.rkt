#lang typed/racket

(require typed/test-engine/racket-tests)

(require "../include/cs151-core.rkt")
(require "../include/cs151-image.rkt")
(require "../include/cs151-universe.rkt")

(: alphabet (Listof Symbol))
(define alphabet '(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z))

;; ====== data definitions

(define-struct (Some S) 
  ([value : S]))

(define-type (Option S) 
  (U 'None (Some S)))

(define-type BST
  (U 'E Node))

(define-struct Node
  ([root : Symbol]
   [lsub : BST]
   [rsub : BST]))

(define-struct BSTWorld
  ([cell-size : Integer]
   [bst : BST]))

;; ----- BST examples ------
(define bst-example1
  (Node 'M
        (Node 'G
              (Node 'C 'E 'E)
              (Node 'K 'E 'E))
        (Node 'V 'E 'E)
        ))

(define bst-example2
  (Node 'M
        (Node 'G
              (Node 'C
                    'E
                    (Node 'D 'E 'E))
              (Node 'K 'E 'E))
        (Node 'V 'E 'E)
        ))

(define empty-bst
  'E)

;; ====== basic BST operations

(: size : BST -> Integer)
;; compute the number of nodes in the BST
(define (size bst)
  (match bst
    ['E 0]
    [(Node _ lsub rsub) (+ 1 (size lsub) (size rsub))]
  )
)
(check-expect (size bst-example1) 5)
(check-expect (size bst-example2) 6)
(check-expect (size empty-bst) 0)

(: height : BST -> Integer)
;; compute the number of levels in the BST
(define (height bst)
  (match bst
    ['E 0]
    [(Node _ lsub rsub) (+ 1 (max (height lsub) (height rsub)))]
  )
)
(check-expect (height bst-example1) 3)
(check-expect (height bst-example2) 4)
(check-expect (height empty-bst) 0)

(: insert : Symbol BST -> BST)
;; insert the symbol in place into the BST
;; if the symbol is present already, return the tree as is (no error)
;; use symbol<? to compare symbols
(define (insert s bst)
  (match bst
    ['E (Node s 'E 'E)]
    [(Node r 'E 'E) (cond
         [(symbol<? s r) (Node r (Node s 'E 'E) 'E)]
         [(symbol=? s r) (Node r 'E 'E)]
         [else (Node r 'E (Node s 'E 'E))]
                         )]
    [(Node r lsub rsub) (cond
         [(symbol<? s r) (Node r (insert s lsub) rsub)]
         [(symbol=? s r) (Node r lsub rsub)]
         [else (Node r lsub (insert s rsub))]
                         )]
  )
)
(check-expect (insert 'G bst-example1) bst-example1)

(check-expect (insert 'Q bst-example1)
     (Node 'M
        (Node 'G
              (Node 'C 'E 'E)
              (Node 'K 'E 'E))
        (Node 'V
              (Node 'Q 'E 'E)
              'E)
        ))
(check-expect (insert 'H bst-example2)
     (Node 'M
        (Node 'G
              (Node 'C
                    'E
                    (Node 'D 'E 'E))
              (Node 'K
                    (Node 'H 'E 'E)
                    'E))
        (Node 'V 'E 'E)
        ))
(check-expect (insert 'W empty-bst) (Node 'W 'E 'E))

;; ====== BST visualizations

(: cell : Symbol Integer -> Image)
;; creates a box-cell with a given symbol and cell-size
(define (cell s w)
  (overlay
   (text (symbol->string s) 25 'black)
   (rectangle w
              25 "outline" 'black)
   (rectangle w
              25 "solid" "mistyrose")
   )
)

(: empty : Image)
;; creates a transparent padding rectangle of size 15 by 25
(define empty
   (rectangle 15
              25 "solid" (color 255 50 255 0))
  
)
(: viz : BST -> Image)
;; creates the visualization for a given BST
(define (viz bst)
  (match bst
    ['E empty-image]
    [(Node v 'E 'E) (cell v 30)]
    [(Node v l r)
     (local
       {(define lsub : Image (viz l))
        (define rsub : Image (viz r))
        (define wlsub : Integer (image-width lsub))
        (define wrsub : Integer (image-width rsub))
        }
       (above
           (cell v (+ wlsub 15 wrsub))
           (beside/align "top"
             lsub empty rsub))

       )]
    
  )
)
;; ----- Visual Tests -----
;;(viz (insert 'O (insert 'Z (insert 'N bst-example2))))
;;(viz (insert 'A (insert 'B (insert 'O (insert 'Z (insert 'N bst-example2))))))
;;(viz bst-example2)

(: inorder : BST -> Image)
;; produce an image showing the letters in _inorder traversal_ order
(define (inorder bst)
  (match bst
    ['E empty-image]
    [(Node r 'E 'E) (cell r 30)]
    [(Node r lsub rsub) (beside (inorder lsub) (cell r 30) (inorder rsub))]
  )
)
;; ----- Visual Tests -----
;;(inorder bst-example1)
;;(inorder bst-example2)
;;(inorder (insert 'A (insert 'B (insert 'O (insert 'Z (insert 'N bst-example2))))))
;;(inorder empty-bst)

;; ====== universe programming

(define-struct Location
  ([x : Integer]
   [y : Integer]))

(: yes-byte? (All (A) (A -> Byte)))
;; yes-byte? ensures that a number is a byte
;; parameters: a value A
;; output: a byte, if A is a byte, error otherwise
(define (yes-byte? num)
  (if (byte? num) num (error "A is not a byte"))
)
(check-expect (yes-byte? 233) 233)
(check-error (yes-byte? "adsf") "A is not a byte")
(check-error (yes-byte? 99999) "A is not a byte")

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

(: clicked-upon : Integer Integer Integer -> (Option Symbol))
;; the arguments are the x and y of a click, and the size of each letter cell
;; the return value is the symbol clicked on, if any
(define (clicked-upon x y s)
(if (< y 25)
  (Some (get-element (- (exact-round (/ x s)) 1) alphabet))
  'None)
)

(: react-to-mouse : BSTWorld Integer Integer Mouse-Event -> BSTWorld)
;; if the user clicks on a symbol cell, add that symbol to the BST
(define (react-to-mouse w x y e)
(match e
    ["button-down"
     (match w
       [(BSTWorld size bst) (match (clicked-upon x y size)
                              ['None w]
                              [(Some letter) (BSTWorld size (insert letter bst))]
       )]
       )]
    [_ w]))

(: alphabet-cells : (Listof Symbol) Integer -> Image)
;; creates the cells displaying the letters of the alphabet in order
(define (alphabet-cells list size)
  (match list
  ['() empty-image]
  [(cons f r) (beside
               (overlay
               (text (symbol->string f) (yes-byte? size) 'black)
               (square size "outline" 'black)
                )
              (alphabet-cells r size))]
))

(: draw : BSTWorld -> Image)
;; draw the BSTWorld
(define (draw w)
  (match w
    [(BSTWorld s bst)
     (if (< s 30)
     (error "Please choose a cell-size greater than or equal to 30")
     (overlay/align "middle" "top"
         (above
                (alphabet-cells alphabet s)
                (rectangle 400 10 "solid" 'white)
                (text
                 (string-append
                  "size : " (number->string (size bst))
                  ", height : " (number->string (height bst)))
                  25 'black)
                (rectangle 400 10 "solid" 'white)
                (viz bst)
                (rectangle 400 10 "solid" 'white)
                (inorder bst))
         (rectangle (* s 27) (* 25 30) "solid" 'white)))]
   )
)

(: do-key : BSTWorld String -> BSTWorld)
;; called by on-key, clears the BST if the "r" key is pressed
(define (do-key w event)
  (cond
    [(string=? event "r")  (match w
                         [(BSTWorld size _) (BSTWorld size 'E)])]
    [else w])
)

(: run : Integer -> BSTWorld)
;; run the world given setup details
(define (run cell-size)
  (big-bang (BSTWorld cell-size 'E) : BSTWorld
    [to-draw draw]
    [on-mouse react-to-mouse]
    [on-key do-key]))
;; the argument to run is the cell size for the row of symbols at the top of the window

(test)