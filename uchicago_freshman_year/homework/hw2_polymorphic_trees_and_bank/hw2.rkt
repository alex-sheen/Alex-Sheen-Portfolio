#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")

;; Problem 1
(define-type (Tree A) (U 'Empty (Node A)))

(define-struct (Node A)
    ([val : A]
     [left : (Tree A)]
     [right : (Tree A)]))

;; example of a tree with ints as its node values
(define example-tree1 (Node 2
                      (Node 3 'Empty 'Empty)
                      (Node 4
                            (Node 5 'Empty 'Empty)
                            (Node 43 'Empty 'Empty))
                      ))

;; example of a tree with strings as its node values
(define example-tree2 (Node "a"
                      (Node "asdf" 'Empty 'Empty)
                      (Node "afew"
                            (Node "s" 'Empty 'Empty)
                            (Node "efq" 'Empty 'Empty))
                      ))
;; example of a tree with strings as its node values
(define example-tree3 (Node "a"
                      (Node "asdf"
                            (Node "afe" 'Empty 'Empty)
                            (Node "df" 'Empty 'Empty))
                      (Node "afew"
                            (Node "s" 'Empty 'Empty)
                            (Node "efq" 'Empty 'Empty))
                      ))


(: num-leafs : (All (A) ((Tree A) -> Integer)))
;; num-leafs: counts the number of leafs in a given tree
;; parameters: a Tree
;; output: numbrer of leafs in that tree
(define (num-leafs tree)
  (match tree
    ['Empty 0]
    [(Node _ 'Empty 'Empty) 1]
    [(Node _ left right) (+ (num-leafs left) (num-leafs right))]
  )
)
(check-expect (num-leafs example-tree1) 3)
(check-expect (num-leafs example-tree2) 3)
(check-expect (num-leafs example-tree3) 4)
(check-expect (num-leafs 'Empty) 0)

(: same-layout? : (All (A B) ((Tree A) (Tree B) -> Boolean)))
;; same-layout? evaluates whether two trees have the same structure
;; parameters: two trees
;; output: boolean, whether they have the same structure
(define (same-layout? tree_a tree_b)
  (match* (tree_a tree_b)
    [('Empty 'Empty) #t]
    [('Empty (Node _ _ _)) #f]
    [((Node _ _ _) 'Empty) #f]
    [((Node _ left_a right_a) (Node _ left_b right_b))
     (and (same-layout? left_a left_b) (same-layout? right_a right_b))]
  )
)
(check-expect (same-layout? example-tree1 example-tree2) #t)
(check-expect (same-layout? example-tree2 example-tree3) #f)

;; Problem 2
(define-type TransType (U 'Debit 'Credit 'Payment))

(define-struct Transaction
    ([type : TransType]
     [description : String]
     [amount : Integer]))

;; example of a Transaction list
(define example_transactions_list
(list (Transaction 'Debit "teststr1" 100)
      (Transaction 'Debit "teststr2" 600)
      (Transaction 'Credit "teststr3" 75)
      (Transaction 'Credit "teststr4" 25)
      (Transaction 'Payment "teststr5" 500)
      (Transaction 'Payment "teststr6" 100)
      )
)
;; example of a Transaction list that has no credit transactions
(define example_no_credits
(list (Transaction 'Debit "teststr1" 100)
      (Transaction 'Debit "teststr2" 600)
      (Transaction 'Payment "teststr5" 500)
      (Transaction 'Payment "teststr6" 100)
      )
)
;; example of a Transaction list that contains some negative transaction amounts
(define example_negative_transactions
(list (Transaction 'Debit "teststr1"-100)
      (Transaction 'Debit "teststr2" 600)
      (Transaction 'Payment "teststr5" -500)
      (Transaction 'Payment "teststr6" 100)
      )
)

;; example of a Transaction list that contains some zero transaction amounts
(define example_zero_transactions
(list (Transaction 'Debit "teststr1" 100)
      (Transaction 'Debit "teststr2" 0)
      (Transaction 'Payment "teststr5" 500)
      (Transaction 'Payment "teststr6" 100)
      )
)

;; example of a Transaction list that has under 1000 net purchases
(define under_1000
(list (Transaction 'Debit "teststr1" 1100)
      (Transaction 'Credit "teststr3" 200)
      )
)
;; example of a Transaction list that has 1000-2000 net purchases
(define under_2000
(list (Transaction 'Debit "teststr1" 2100)
      (Transaction 'Credit "teststr3" 200)
      )
)
;; example of a Transaction list that has over 2000 net purchases
(define over_2000
(list (Transaction 'Debit "teststr1" 3400)
      (Transaction 'Credit "teststr3" 200)
      )
)

(: balance : (Listof Transaction) -> Integer)
;; balance: sums all debits and subtracts all credits and payments
;; parameters: list of all transactions
;; output: balance in cents
(define (balance transactions_list)
 (cond
   [(all-valid? transactions_list)
    (match transactions_list
      ['() 0]
      [(cons (Transaction 'Debit _ amnt) rest) (+ amnt (balance rest))]
      [(cons (Transaction 'Credit _ amnt) rest) (- (balance rest) amnt)]
      [(cons (Transaction 'Payment _ amnt) rest) (- (balance rest) amnt)]
      )]
    [else (error "balance: transaction amounts must be positive")]
  )
)
(check-expect (balance example_transactions_list) 0)
(check-expect (balance example_no_credits) 100)
(check-error (balance example_negative_transactions)
             "balance: transaction amounts must be positive")

(: rewards : (Listof Transaction) -> Integer)
;; rewards: determines cash back rewards from a list of transactions
;; parameters: list of all transactions
;; output: rewards in cents
(define (rewards transactions_list)
  (local
    {

     (define net_purchases (compute_net_purchases transactions_list))
     }
    (cond
     [(all-valid? transactions_list)
      (cond
        [(> 1000 net_purchases) (exact-round (* net_purchases 0.01))]
        [(> 2000 net_purchases) (exact-round (* net_purchases 0.0125))]
        [else (exact-round (* net_purchases 0.015))]
       )]
     [else (error "rewards: transaction amounts must be positive")]
    )
  )
)
(check-expect (rewards example_transactions_list) 6)
(check-error (rewards example_negative_transactions)
             "rewards: transaction amounts must be positive")
(check-expect (rewards under_1000) 9)
(check-expect (rewards under_2000) 24)
(check-expect (rewards over_2000) 48)

(: compute_net_purchases : (Listof Transaction) -> Integer)
;; compute_net_purchases: computes net purchases from list of transactions
;; helper function
;; parameters: list of transactions
;; output: net purchases in cents
(define (compute_net_purchases transactions_list)

    (match transactions_list
      [(cons (Transaction 'Debit _ amnt) rest)
        (+ amnt (compute_net_purchases rest))]
      
      [(cons (Transaction 'Credit _ amnt) rest)
         (- (compute_net_purchases rest) amnt)]
      [else 0]
    )
)
(check-expect (compute_net_purchases example_transactions_list) 600)

(: credits? : (Listof Transaction) -> Boolean)
;; credits?: determines whether a list of transactions contains a credit transaction
;; parameters: list of transactions
;; output: boolean, if a credit transaction was found
(define (credits? transactions_list)
  (cond
   [(all-valid? transactions_list)
    (match transactions_list
      ['() #f]
      [(cons (Transaction 'Credit _ amnt) rest) #t]
      [(cons _ rest) (credits? rest)]
      )]
   [else (error "credits?: transaction amounts must be positive")]
   )
)
(check-expect (credits? example_transactions_list) #t)
(check-expect (credits? example_no_credits) #f)
(check-error (credits? example_negative_transactions)
             "credits?: transaction amounts must be positive")

(: all-valid? : (Listof Transaction) -> Boolean)
;; all-valid?: checks to ensure that all transactions are positive amounts
;; parameters: a list of transactions
;; output: boolean, if all transactions are valid
(define (all-valid? transactions_list)
   (match transactions_list
      ['() #t]
      [(cons (Transaction _ _ amnt) rest)
       (cond
           [(> amnt 0) (all-valid? rest)]
           [else #f]
           )]
   )
)
(check-expect (all-valid? example_transactions_list) #t)
(check-expect (all-valid? example_no_credits) #t)
(check-expect (all-valid? example_negative_transactions) #f)
(check-expect (all-valid? example_zero_transactions) #f)

(: transaction=? : Transaction Transaction -> Boolean)
;; transaction=?: compares two transactions for equality
;; parameters: two transactions
;; output: boolean, whether they are equal
(define (transaction=? trans1 trans2)
  (match* (trans1 trans2)
    [((Transaction type1 desc1 amnt1)(Transaction type2 desc2 amnt2))
     (and (symbol=? type1 type2) (string=? desc1 desc2) (= amnt1 amnt2))]
    [(_ _) #f]
  )
)
(check-expect (transaction=? (Transaction 'Debit "desc" 100)
                             (Transaction 'Debit "desc" 100)) #t)

(check-expect (transaction=? (Transaction 'Debit "desc" 200)
                             (Transaction 'Debit "desc" 100)) #f)

(check-expect (transaction=? (Transaction 'Debit "asdf" 100)
                             (Transaction 'Debit "desc" 100)) #f)

(check-expect (transaction=? (Transaction 'Credit "desc" 100)
                             (Transaction 'Debit "desc" 100)) #f)

(: trans-in-list? : Transaction (Listof Transaction) -> Boolean)
;; trans-in-list?: determines if a list of transactions contains a certain transaction
;; parameters: a given transaction and a list of transactions
;; output: boolean, whether the list contains that transaction
(define (trans-in-list? trans transactions_list)
  (cond
   [(all-valid? transactions_list)
    (match transactions_list
      ['() #f]
      [(cons first rest)
       (cond
         [(transaction=? first trans) #t]
         [else (trans-in-list? trans rest)]
       )]
      )]
   [else (error "trans-in-list?: transaction amounts must be positive")]
  )
)
(check-expect (trans-in-list? (Transaction 'Debit "teststr1" 100)
                              example_transactions_list) #t)

(check-expect (trans-in-list? (Transaction 'Debit "teststr1" 200)
                              example_transactions_list) #f)

(check-expect (trans-in-list? (Transaction 'Debit "teststr2" 100)
                              example_transactions_list) #f)

(check-expect (trans-in-list? (Transaction 'Credit "teststr1" 100)
                              example_transactions_list) #f)

(check-error (trans-in-list? (Transaction 'Credit "teststr1" 100)
                             example_negative_transactions)
             "trans-in-list?: transaction amounts must be positive")

(: find-desc : String (Listof Transaction) -> (Listof Transaction))
;; find-desc: takes a list of transactions
;;            and returns the subsection that contain a certain description
;; parameters: a string description and a list of transactions
;; output: a list of transactiosn with a certain description
(define (find-desc str transactions_list)
  (cond
   [(all-valid? transactions_list)
     (match transactions_list
       ['() '()]
       [(cons (Transaction t desc a) rest)
        (cond
          [(string=? desc str) (cons (Transaction t desc a) (find-desc str rest))]
          [else (find-desc str rest)]
        )]
    )]
   [else (error "find-desc: transaction amounts must be positive")]
  )
)
(check-expect (find-desc "teststr1" example_transactions_list)
              (list (Transaction 'Debit "teststr1" 100)))

(check-expect (find-desc "asedf" example_transactions_list) '())

(check-error (find-desc "asdf" example_negative_transactions)
             "find-desc: transaction amounts must be positive")

;; Problem 3

;; example list of ints
(define int_list (list 1 -1 2 -2 3 -4 5 6))

;; example list of strings and ints
(define string_int_list (list "asdf" -1 2 -2 3 -4 5 6))

(: count-flagged : (All (A) ((A -> Boolean) (Listof A) -> Integer)))
;; count-flagged: returns number of elements in a list that return
;;                true when passed through a given function
;; parameters: a function and a list of elements
;; output: number of elements that return true
(define (count-flagged f list)
  (match list
    ['() 0]
    [(cons first rest)
     (cond
      [(f first) (+ 1 (count-flagged f rest))]
      [else (count-flagged f rest)]
       )]
  )
)
(check-expect (count-flagged positive-integer? int_list) 5)
(check-expect (count-flagged string? string_int_list) 1)


;; example tree that has multiple types as its node values
(define example-tree-mixed (Node 2
                      (Node 3 'Empty 'Empty)
                      (Node "asdf"
                            (Node "4" 'Empty 'Empty)
                            (Node 43 'Empty 'Empty))
                      ))
;; end result of prune-tree on the example tree above
(define example-tree-mixed-pruned (Node 2
                      (Node 3 'Empty 'Empty)
                      'Empty
                      ))

;; example tree that has multiple types as its node values
(define example-tree-mixed2 (Node 2
                      (Node 3 'Empty 'Empty)
                      (Node 4
                            (Node "asdf" 'Empty 'Empty)
                            (Node 43 'Empty 'Empty))
                      ))
;; end result of prune-tree on the example tree above
(define example-tree-mixed-pruned2 (Node 2
                      (Node 3 'Empty 'Empty)
                       (Node 4
                            'Empty
                            (Node 43 'Empty 'Empty))
                      ))

(: prune-tree : (All (A) ((A -> Boolean) (Tree A) -> (Tree A))))
;; prune-tree: removes elements from a tree that satisfy the provided function
;; parameters: a tree and a similiar function
;; output: a tree with the true elements and their descendants removed
(define (prune-tree f tree)
  (match tree
    ['Empty 'Empty]
    [(Node v left right) (cond
                         [(f v) 'Empty]
                         [else (Node v (prune-tree f left) (prune-tree f right))]
                         )]
  )
)
(check-expect (prune-tree string? example-tree-mixed) example-tree-mixed-pruned)
(check-expect (prune-tree string? example-tree-mixed2) example-tree-mixed-pruned2)

(test)
