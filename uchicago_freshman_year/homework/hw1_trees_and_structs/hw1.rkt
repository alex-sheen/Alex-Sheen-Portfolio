#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")

;; Problem 1
(define-struct QPoint
    ([x : Exact-Rational]
     [y : Exact-Rational]))

(define-struct SlopeLine
    ([slope : Exact-Rational]
     [intercept : Exact-Rational]))

(define-struct VerticalLine
    ([x : Exact-Rational]))

(define-struct PointsLine
    ([a : QPoint]
     [b : QPoint]))

(define-type Line (U SlopeLine VerticalLine PointsLine))

;; line->string: convert a line into a string representation
;; parameter: Line
;; output: String representation
(: line->string (-> Line String))
(define (line->string line)
  (match line
    [(SlopeLine slope intercept)
         (string-append "y = " (number->string slope) " * x + "
                        (number->string intercept))]
    [(VerticalLine x) (string-append "x = " (number->string x))]
    [(PointsLine (QPoint x1 y1) (QPoint x2 y2))
         (string-append "(" (number->string x1) ", " (number->string y1)
              ") - (" (number->string x2) ", " (number->string y2) ")")]
  )
)
(check-expect (line->string (SlopeLine 3 4)) "y = 3 * x + 4")
(check-expect (line->string (VerticalLine 3)) "x = 3")
(check-expect (line->string (PointsLine (QPoint 3 4) (QPoint 5 6))) "(3, 4) - (5, 6)")

;; translate-up: shift a given line up by a specified number of coordinate units
;; parameters: An Exact-Rational and a Line
;; output: the Line shifted up (same representation as given Line)
(: translate-up (-> Exact-Rational Line Line))
(define (translate-up yshift line)
  (match line
    [(SlopeLine slope intercept) (SlopeLine slope (+ intercept yshift))]
    [(VerticalLine x) (VerticalLine x)]
    [(PointsLine (QPoint x1 y1) (QPoint x2 y2))
     (PointsLine (QPoint x1 (+ yshift y1)) (QPoint x2 (+ yshift y2)))]
   )
)
(check-expect (translate-up 3 (SlopeLine 3 4)) (SlopeLine 3 7))
(check-expect (translate-up 3 (VerticalLine 3)) (VerticalLine 3))
(check-expect (translate-up 3 (PointsLine (QPoint 3 4) (QPoint 5 6)))
              (PointsLine (QPoint 3 7) (QPoint 5 9)))
(check-expect (translate-up -3 (SlopeLine 3 4)) (SlopeLine 3 1))

;; passes-through?: evaluates if and only if the given line passes through the given point
;; parameter: a QPoint and a Line
;; output: whether the Line intersects the QPoint
(: passes-through? (-> QPoint Line Boolean))
(define (passes-through? point line)
  (local
    {(: get-slope (-> Exact-Rational Exact-Rational
                      Exact-Rational Exact-Rational Exact-Rational))
     (define (get-slope x1 y1 x2 y2) (/ (- y1 y2)(- x1 x2)))}
    
  (match* (point line)
    [((QPoint x y) (SlopeLine slope intercept)) (= y (+ (* slope x) intercept))]
    [((QPoint x _)(VerticalLine xint))(= x xint)]
    [((QPoint x y)(PointsLine (QPoint x1 y1) (QPoint x2 y2)))
      (cond
        [(= x1 x2) (= x1 x)] ;; checks to make sure that division with zero does not work
        [else (= (- y y1) (* (get-slope x1 y1 x2 y2)(- x x1)))]
      )]
   )
  )
)
(check-expect (passes-through? (QPoint 1 7) (SlopeLine 3 4)) #t)
(check-expect (passes-through? (QPoint 1 8) (SlopeLine 3 4)) #f)
(check-expect (passes-through? (QPoint 3 5) (VerticalLine 3)) #t)
(check-expect (passes-through? (QPoint 4 5) (VerticalLine 3)) #f)
(check-expect (passes-through? (QPoint 6 8)
                               (PointsLine (QPoint 3 4) (QPoint 9 12))) #t)
(check-expect (passes-through? (QPoint 6 9)
                               (PointsLine (QPoint 3 4) (QPoint 9 12))) #f)

;; lines=?: evaluate if two lines provided are exactly the same line
;; parameters: Line and a Line
;; output: whether they are the same line
(: lines=? (-> Line Line Boolean))
(define (lines=? line1 line2)
 (match line1
   [(SlopeLine slope intercept)
    (and (passes-through? (QPoint 3 (+ (* slope 3) intercept)) line2)
         (passes-through? (QPoint 2 (+ (* slope 2) intercept)) line2))]
   [(VerticalLine xint)
   (and (passes-through? (QPoint xint 3) line2)
        (passes-through? (QPoint xint 5) line2))]
   [(PointsLine point1 point2)
   (and (passes-through? point1 line2)
        (passes-through? point2 line2))]
 )
)
(check-expect (lines=? (VerticalLine 3) (SlopeLine 3 4)) #f)
(check-expect (lines=? (SlopeLine 2 2) (PointsLine (QPoint 2 6) (QPoint -1 0))) #t)
(check-expect (lines=? (VerticalLine 3) (PointsLine (QPoint 2 6) (QPoint 2 0))) #f)
(check-expect (lines=? (SlopeLine 2 2) (VerticalLine 3)) #f)


;; Problem 2
(define-type IntTree (U IntNode 'IEmpty))

(define-struct IntNode
  ([val   : Integer]
   [left  : IntTree]
   [right : IntTree]))

(define-type StringTree (U StringNode 'SEmpty))

(define-struct StringNode
  ([val   : String]
   [left  : StringTree]
   [right : StringTree]))


;; mirror: takes an IntTree and returns an IntTreem with the left and right subtrees swapped
;; parameters: an IntTree
;; output: an IntTree with swapped subtrees
(: mirror (-> IntTree IntTree))
(define (mirror tree)
  (match tree
    ['IEmpty 'IEmpty]
    [(IntNode val left right) (IntNode val (mirror right) (mirror left))]
  )
)
(check-expect (mirror (IntNode 2
                               (IntNode 3 'IEmpty 'IEmpty)
                               (IntNode 4 (IntNode 5 'IEmpty 'IEmpty) 'IEmpty)))
                      (IntNode 2
                               (IntNode 4 'IEmpty (IntNode 5 'IEmpty 'IEmpty))
                               (IntNode 3 'IEmpty 'IEmpty)))


;; int-tree->string-tree: takes an IntTree and returns a StringTree with the same values
;; parameters: IntTree
;; output: StringTree with same values as IntTree
(: int-tree->string-tree (-> IntTree StringTree))
(define (int-tree->string-tree tree)
  (match tree
    ['IEmpty 'SEmpty]
    [(IntNode v  left right)
     (StringNode (number->string v)
                 (int-tree->string-tree left)
                 (int-tree->string-tree right))]
  )
)
 (check-expect (int-tree->string-tree (IntNode 2 (IntNode 3 'IEmpty 'IEmpty)
                      (IntNode 4 (IntNode 5 'IEmpty 'IEmpty) 'IEmpty)))
               (StringNode "2" (StringNode "3" 'SEmpty 'SEmpty)
                      (StringNode "4" (StringNode "5" 'SEmpty 'SEmpty) 'SEmpty)))

;; right-edge: takes a StringTree and produces a String
;; Returns a String that is the concatenation of all the right edge strings, root-to-leaf order
;; parameters: StringTree
;; output: String of all right edge strings
(: right-edge (-> StringTree String))
(define (right-edge tree)
  (match tree
   [(StringNode s _ 'SEmpty) s]
   [(StringNode s _ right) (string-append s (right-edge right))]
  )
)
(check-expect (right-edge
              (StringNode "x"
                          (StringNode "b"
                                      (StringNode "a" 'SEmpty 'SEmpty) 'SEmpty)
                          (StringNode "yy"
                                      (StringNode "w" 'SEmpty 'SEmpty)
                                      (StringNode "z" 'SEmpty 'SEmpty)))
              )
              "xyyz")

;; Problem 3
(define-type 3Tree (U 3Node '3Empty))

(define-struct 3Node
  ([root : Integer]
   [lsub : 3Tree]
   [msub : 3Tree]
   [rsub : 3Tree]))

(define example-tree (3Node 1
       (3Node 2
              (3Node 3 '3Empty '3Empty '3Empty)
              (3Node 4 '3Empty '3Empty '3Empty)
              '3Empty)
       (3Node 8
              '3Empty
              (3Node 7
                     (3Node 5 '3Empty '3Empty '3Empty)
                     '3Empty
                     (3Node 6 '3Empty '3Empty '3Empty))
              '3Empty)
       (3Node 9
              '3Empty
              '3Empty
              (3Node 0 '3Empty '3Empty '3Empty))))

(define neg-example-tree (3Node 1
       (3Node 2
              (3Node -3 '3Empty '3Empty '3Empty)
              (3Node 4 '3Empty '3Empty '3Empty)
              '3Empty)
       (3Node -8
              '3Empty
              (3Node 7
                     (3Node 5 '3Empty '3Empty '3Empty)
                     '3Empty
                     (3Node -6 '3Empty '3Empty '3Empty))
              '3Empty)
       (3Node -9
              '3Empty
              '3Empty
              (3Node 0 '3Empty '3Empty '3Empty))))

;; num-nodes: computes number of nodes in a 3Tree
;; parameter: 3Tree
;; output: number of nodes in 3Tree
(: num-nodes : 3Tree -> Integer)
(define (num-nodes tree)
  (match tree
    ['3Empty 0]
    [(3Node _ lsub msub rsub)
     (+ 1 (num-nodes lsub) (num-nodes msub) (num-nodes rsub))]
  )
)
(check-expect (num-nodes example-tree) 10)

;; sum-nodes computes sum of the nodes in a 3Tree
;; parameter: 3Tree
;; output: sum of the values in nodes in 3Tree
(: sum-nodes : 3Tree -> Integer)
(define (sum-nodes tree)
  (match tree
    [(3Node v '3Empty '3Empty '3Empty) v]
    ['3Empty 0]
    [(3Node v lsub msub rsub) (+ v (sum-nodes lsub) (sum-nodes msub) (sum-nodes rsub))]
  )
)
(check-expect (sum-nodes example-tree) 45)

;; height: measures the height of a tree
;; parameter: 3Tree
;; output: height of the 3Tree
(: height : 3Tree -> Integer)
(define (height tree)
  (match tree
    [(3Node _ '3Empty '3Empty '3Empty) 1]
    ['3Empty 0]
    [(3Node _ lsub msub rsub) (+ 1 (max (height lsub) (height msub) (height rsub)))]

  )
)
(check-expect (height example-tree) 4)

;; contains?: evaluates if a tree contains the given integer anywhere among its node values.
;; parameter: 3Tree and an Integer
;; output: if a tree contains the integer
(: contains? : 3Tree Integer -> Boolean)
(define (contains? tree i)
  (match tree
    ['3Empty #f]
    [(3Node v lsub msub rsub) (cond
                                [(= v i) #t]
                                [else (or (contains? lsub i)
                                          (contains? msub i) (contains? rsub i))]
                                )]
  )
)
(check-expect (contains? example-tree 5) #t)
(check-expect (contains? example-tree 100) #f)

;; leftmost: returns the item farthest to the left in the tree
;; parameter: 3Tree
;; output: leftmost value
(: leftmost : 3Tree -> (U Integer 'None))
(define (leftmost tree)
  (match tree
   [(3Node v '3Empty '3Empty '3Empty) v]
   [(3Node v '3Empty '3Empty _) v]
   [(3Node _ '3Empty msub _) (leftmost msub)]
   [(3Node _ lsub _ _) (leftmost lsub)]
   ['3Empty 'None]
  )
)
(check-expect (leftmost example-tree) 3)
(check-expect (leftmost '3Empty) 'None)
(check-expect (leftmost (3Node 1
                     '3Empty
                     (3Node 5 '3Empty '3Empty '3Empty)
                     '3Empty
                )) 5 )
(check-expect (leftmost (3Node 1
                     '3Empty
                     '3Empty
                     (3Node 5 '3Empty '3Empty '3Empty)
                )) 1 )

;; farthest-item: returns the item farthest from the root of a tree
;; favors the left leaf if any ties
;; parameters: 3Tree
;; output: farthest item
(: farthest-item : 3Tree -> (U Integer 'None))
(define (farthest-item tree)
  (match tree
    [(3Node v '3Empty '3Empty '3Empty) v]
    [(3Node v '3Empty msub rsub) (cond
                              [(= (height msub) (height rsub))
                               (farthest-item msub)]
                              [(> (height rsub) (height msub))
                               (farthest-item rsub)]
                              [else (farthest-item msub)]
                              )]
    [(3Node v '3Empty '3Empty rsub) (farthest-item rsub)]
    [(3Node v lsub msub rsub) (cond
                              [(= (height lsub) (height msub) (height rsub))
                               (farthest-item lsub)]
                              [(and (> (height rsub) (height lsub))
                                    (> (height rsub) (height msub)))
                               (farthest-item rsub)]
                              [(and (> (height msub) (height lsub))
                                    (> (height msub) (height rsub)))
                               (farthest-item msub)]
                              [else (farthest-item lsub)]
                               )]
    
  )
)
(check-expect (farthest-item example-tree) 5)
(check-expect (farthest-item (3Node 1
                     '3Empty
                     (3Node 5 '3Empty '3Empty '3Empty)
                     '3Empty
                )) 5 )
(check-expect (farthest-item (3Node 1
                     '3Empty
                     (3Node 4 '3Empty '3Empty '3Empty)
                     (3Node 5 '3Empty '3Empty '3Empty)
                )) 4 )
(check-expect (farthest-item (3Node 1
                     (3Node 3 '3Empty '3Empty '3Empty)
                     (3Node 4 '3Empty '3Empty '3Empty)
                     (3Node 5 '3Empty '3Empty '3Empty)
                )) 3 )


;; abs-tree: takes a tree and returns a new tree with the absolute values of the first
;; parameter: 3Tree
;; output: absolute value of 3Tree
(: abs-tree : 3Tree -> 3Tree)
(define (abs-tree tree)
 (match tree
    [(3Node v '3Empty '3Empty '3Empty) (3Node (abs v) '3Empty '3Empty '3Empty)]
    ['3Empty '3Empty]
    [(3Node v lsub msub rsub)
     (3Node (abs v) (abs-tree lsub) (abs-tree msub) (abs-tree rsub))]
 )
)
(check-expect (abs-tree neg-example-tree) example-tree)

(test)