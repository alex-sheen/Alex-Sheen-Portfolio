#lang typed/racket

(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")
(require "../include/cs151-image.rkt")
(require "../include/cs151-universe.rkt")

;; === data definitions

(define-type (Option A)
  (U 'None (Some A)))

(define-struct (Some A)
  ([value : A]))

(define-struct Location
  ([x : Integer]
   [y : Integer]))

(define-struct CircleWorld
  ([background-color : Image-Color]
   [initial-color    : Image-Color]
   [change-to-color  : Image-Color]
   [num-circles : Integer]
   [radius  : Integer]
   [padding : Integer]
   [current-colors : (Listof Image-Color)]))

;; === operations and calculations

(: yes-integer? (All (A) (A -> Integer)))
;; yes-integer? ensures that a value is a real number
;; parameters: a value A
;; output: a real number, if A is a real number, error otherwise
(define (yes-integer? num)
  (if (exact-integer? num) num (error "A is not a real number"))
)
(check-expect (yes-integer? 233) 233)
(check-error (yes-integer? "adsf") "A is not a real number")

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

(: chop (All (A) (Integer (Listof A) -> (Listof (Listof A)))))
;; cut list into size-n sublists
;; ex: (chop 2 '(a b c d e f)) -> '((a b) (c d) (e f))
;; ex: (chop 4 '(a b c d e f)) -> '((a b c d) (e f))
;; no error if the number of items is not multiple of n
(define (chop n xs)
  (cond
    [(empty? xs) '()]
    [else (cons (take n xs)
                (chop n (drop n xs)))]))

(check-expect (chop 2 '(a b c d e f)) '((a b) (c d) (e f)))
(check-expect (chop 2 '(a b c d e)) '((a b) (c d) (e)))


(: replace-at : All (A) Integer A (Listof A) -> (Listof A))
;; replace the item at the given position
;; position counting starts at 0
;; ex: (replace-at 0 'Z '(a b c)) -> '(Z b c)
;; ex: (replace-at 1 'Z '(a b c)) -> '(a Z c)
(define (replace-at i x xs)
  (append (take i xs) (cons x (drop (+ 1 i) xs)))
)

(check-expect (replace-at 0 'Z '(a b c)) '(Z b c))
(check-expect (replace-at 1 'Z '(a b c)) '(a Z c))
(check-expect (replace-at 2 'Z '(a b c)) '(a b Z))

(: centers : CircleWorld -> (Listof Location))
;; compute the centers of all the circles in the CircleWorld
;; important! the upper left of a "world" is (0,0)
;; and x and y grow to the right and down
;; ex: (centers (CircleWorld ... ... ... 2 10 0 ...))
;;         -> (list (Location 10 10) (Location 30 10))
;; ex: (centers (CircleWorld ... ... ... 2 10 1 ...))
;;         -> (list (Location 11 11) (Location 32 11))
;; ex: (centers (CircleWorld ... ... ... 3 10 2 ...))
;;         -> (list (Location 12 12) (Location 34 12) (Location 56 12))
(define (centers w)
  (local
    {
     
    }
  (match w
    [(CircleWorld bc ic ctc nc r p cc)
     (build-list nc
       (lambda (x)
         (Location
          (+ p r (* (yes-integer? x) p) (* 2 r (yes-integer? x)))
          (+ p r))))
    ]
  )))
(check-expect
  (centers (CircleWorld 'blue 'green 'pink 2 10 0 (list 'blue 'blue)))
  (list (Location 10 10) (Location 30 10)))

(check-expect
  (centers (CircleWorld 'blue 'green 'pink 2 10 1 (list 'blue 'blue)))
  (list (Location 11 11) (Location 32 11)))

(check-expect
  (centers (CircleWorld 'blue 'green 'pink 3 10 2 (list 'blue 'blue 'blue)))
  (list (Location 12 12) (Location 34 12) (Location 56 12)))


(: in-a-circle? : Integer Location (Listof Location) Integer -> (Option Integer))
;; given: a circle radius, a click location, a list of centers, and a list index
;; (the list index should be 0 when the function is called initially)
;; if the click is within the radius of circle at list-index,
;; return (Some list-index), otherwise, return 'None
;; ex: (in-a-circle? 10
;;     (Location 10 10) (list (Location 10 10) (Location 30 10)) 0) -> (Some 0)
;; ex: (in-a-circle? 10
;;     (Location 9 8) (list (Location 10 10) (Location 30 10)) 0) -> (Some 0)
;; ex: (in-a-circle? 10
;;     (Location 0 0) (list (Location 10 10) (Location 30 10)) 0) -> 'None
;; ex: (in-a-circle? 10
;;     (Location 30 11) (list (Location 10 10) (Location 30 10)) 0) -> (Some 1)
(define (in-a-circle? rad click cs list-index)
  (local
  {
   (: inside (Location Location Integer -> Boolean))
   (define (inside click target r)
     (match* (click target)
       [((Location cx cy)(Location tx ty))
        (<
            (sqrt (+
                   (* (- tx cx) (- tx cx))
                   (* (- ty cy) (- ty cy))))
            r)]
     )
   )
  }
  (match cs
    ['() 'None]
    [(cons f r)
     (if (inside click f rad)
         (Some list-index)
         (in-a-circle? rad click r (+ list-index 1)))]
  ))
)
(check-expect (in-a-circle?
      10 (Location 10 10) (list (Location 10 10) (Location 30 10)) 0) (Some 0))

(check-expect (in-a-circle?
      10 (Location 9 8) (list (Location 10 10) (Location 30 10)) 0) (Some 0))

(check-expect (in-a-circle?
      10 (Location 0 0) (list (Location 10 10) (Location 30 10)) 0) 'None)

(check-expect (in-a-circle?
      10 (Location 30 11) (list (Location 10 10) (Location 30 10)) 0) (Some 1))




;; === universe support

(: draw : CircleWorld -> Image)
;; draw the CircleWorld, taking care that padding is correct
(define (draw w)
 (match w
   [(CircleWorld bc _ _ num r p list-colors)
    (local
      {
       (: circle-recursion (Integer Integer (Listof Image-Color) -> Image))
       (define (circle-recursion rad pad xs)
         (match xs
          ['() empty-image]
          [(cons f r) (beside
                       (circle rad "solid" f)
                       (rectangle pad pad "solid" (color 255 255 255 0))
                       (circle-recursion rad pad r))]
         )
       )
      }
      (overlay
       (beside
         (rectangle p p "solid" (color 255 255 255 0))
         (circle-recursion r p list-colors))
       (rectangle
        (+ p (* p num) (* 2 r num))
        (* 2 (+ p r))
        "solid" bc)
      ))]
 )
)
;; (draw (CircleWorld 'lightgreen 'pink 'yellow 12 20 8
;; '(yellow yellow pink pink pink pink yellow pink pink pink pink pink)))



(: react-to-mouse : CircleWorld Integer Integer Mouse-Event -> CircleWorld)
;; if the user clicks on a circle, change the color to the "change-to-color"
;; if the user clicks outside any circle, reset all circles to the initial color
(define (react-to-mouse w x y e)
  (match e
    ["button-down"
     (match w
       [(CircleWorld bc ic tc num r p list-colors)
         (match (in-a-circle? r (Location x y) (centers w) 0)
           ['None (CircleWorld bc ic tc num r p
                   (build-list num (lambda (_) ic)))]
           [(Some n) (CircleWorld bc ic tc num r p
                   (replace-at n tc list-colors))]
     )])]
    [_ w]))
(check-expect (react-to-mouse
      (CircleWorld 'green 'blue 'orange 4 4 4 (list 'blue 'blue 'blue 'blue))
      8 8 "button-down")
      (CircleWorld 'green  'blue 'orange 4 4 4 (list 'orange 'blue 'blue 'blue)))

(check-expect (react-to-mouse
      (CircleWorld 'green 'blue 'orange 4 4 4 (list 'blue 'blue 'blue 'blue))
      2 8 "button-down")
      (CircleWorld 'green  'blue 'orange 4 4 4 (list 'blue 'blue 'blue 'blue)))

(check-expect (react-to-mouse
      (CircleWorld 'green  'blue 'orange 4 4 4 (list 'blue 'blue 'blue 'blue))
      18 8 "button-down")
      (CircleWorld 'green  'blue 'orange 4 4 4 (list 'blue 'orange 'blue 'blue)))

(: run : Image-Color Image-Color Image-Color Integer Integer Integer -> CircleWorld)
;; run the world given setup details
(define (run bg init ch n r p)
  (big-bang (CircleWorld bg init ch n r p (make-list n init)) : CircleWorld
    [to-draw draw]
    [on-mouse react-to-mouse]))



(test)