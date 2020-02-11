#lang typed/racket
(require typed/test-engine/racket-tests)

;; Alex Sheen's Lab 1

;;(require "../include/cs151-core.rkt")
;; I just switched into the class, and for some reason I could not pull the cs151-core.rkt file from the Github
;; I have commented it out since my code runs without it

;; marginal-tax: compute the amount of tax owed on the given income.
;; parameter "income": an integer number of thunks
;; output: the amount of marginal tax owed
(: marginal-tax (-> Integer Integer))
(define (marginal-tax i)
   (cond
     [(<= i 24000) 0]
     [(<= i 40000) (exact-ceiling (* 0.12 (- i 24000)))]
     [(<= i 75000) (exact-ceiling(+ (* 0.12 16000) (* .24 (- i 40000))))]
     [else (exact-ceiling(+ (* .12 16000) (* .24 35000) (* .48 (- i 75000))))]
   )
)
(check-expect (marginal-tax 23000) 0)      ;; deductable under 24000
(check-expect (marginal-tax 25000) 120)    ;; deductable btwn 24000 and 40000
(check-expect (marginal-tax 41000) 2160)   ;; deductable btwn 40000 and 75000
(check-expect (marginal-tax 78000) 11760)  ;; deductable over 75000

;; solar-panel-deduction: compute deduction of 10 thunks per
;;   square cm, but not more than 20% of income
;; parameter "income": an integer number of thunks
;; parameter "area": the area in square cm of the solar panels
;; output: deduction as described above
(: solar-panel-deduction (-> Integer Integer Integer))
(define (solar-panel-deduction income area)
  (local
    {
       (define compute-solar-panel-deduction (* 10 area))
       (define compute-20%-income (exact-ceiling(* 0.2 income)))
    }

    (min compute-solar-panel-deduction compute-20%-income)
  )
)
(check-expect (solar-panel-deduction 25000 20) 200)    ;; deductable under 20% of income
(check-expect (solar-panel-deduction 20000 400) 4000)  ;; deductable equal to 20% of income
(check-expect (solar-panel-deduction 18000 400) 3600)  ;; deductable over 20% of income

;; garden-deduction: compute deduction of lbs-per-year-per-person
;;   in thunks times 12, but not more than 8000
;; parameter "lbs-per-year": the garden yield in pounds per year
;; parameter "num-people": the number of people in the family unit
;; output: deduction as described above
(: garden-deduction (-> Integer Integer Integer))
(define (garden-deduction lbs-per-year num-people)
  (local
    {
     (define lbs-per-year-per-person (/ lbs-per-year num-people))
     (define compute-garden-deduction (exact-ceiling(* 12 lbs-per-year-per-person)))
    }
    
    (min 8000 compute-garden-deduction)
  ) 
)
(check-expect (garden-deduction 10 2) 60)      ;; deductable under 8000
(check-expect (garden-deduction 5000 2) 8000)  ;; deductable over 8000

;; itemized: compute itemized deduction on income
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "solar-panels": area in square cm of solar panels
;; parameter "lbs-per-year": garden yield
;; output: total itemized deduction for this family unit
(: itemized (-> Integer Integer Integer Integer Integer))
(define (itemized income num-people solar-panels lbs-per-year)
  (local
    {
      (define compute-solar-panel-deduction (solar-panel-deduction income solar-panels))
      (define compute-garden-deduction (garden-deduction lbs-per-year num-people))
    }
    
    (+ compute-solar-panel-deduction compute-garden-deduction)
  )
)
(check-expect (itemized 80000 3 100 150) 1600) ;; using example given

;; standard: compute the standard deduction for a family unit,
;;   which is just 1200 thunks per person
;; parameter "num-people"
;; output: the deduction for that number of people
(: standard (-> Integer Integer))
(define (standard people)
  (* people 1200)
)
(check-expect (standard 3) 3600)


;; should-itemize?: should family unit itemize or take standard? 
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "solar-panels": area in square cm of solar panels
;; parameter "lbs-per-year": garden yield
;; output: #t if itemized deduction is larger than standard, #f otherwise
(: should-itemize? (-> Integer Integer Integer Integer Boolean))
(define (should-itemize? income num-people solar-panels lbs-per-year)
  (local
    {
      (define compute-itemized-deduction (itemized income num-people solar-panels lbs-per-year))
      (define compute-standard (standard num-people))
    }
    
    (if (> compute-itemized-deduction compute-standard) #t #f)
  )
)
(check-expect (should-itemize? 80000 3 100 150) #f)  ;; using example given
(check-expect (should-itemize? 80000 3 100 9999) #t) ;; if itemized deduction is clearly greater than standard


;; tax-return: Determine the negative (refund) or positive (payment) due
;;   family unit, given their income as well as the amount withheld.
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "solar-panels": area in square cm of solar panels
;; parameter "lbs-per-year": garden yield
;; parameter "withheld": amount of thunks already withheld
;; output: positive or negative debt to the CRS (negative debt is a refund)
(: tax-return (-> Integer Integer Integer Integer Integer Integer))
(define (tax-return income num-people solar-panels lbs-per-year withheld)
  (local
    {
      (define compute-itemized-deduction (itemized income num-people solar-panels lbs-per-year))
      (define compute-standard-deduction (standard num-people))
      (define income-after-itemized-deduction (- income compute-itemized-deduction))
      (define income-after-standard-deduction (- income compute-standard-deduction))
    }

    (cond
      [ (should-itemize? income num-people solar-panels lbs-per-year)
        (- (marginal-tax income-after-itemized-deduction) withheld)
      ]
      [else (- (marginal-tax income-after-standard-deduction) withheld)]
    )
  )
)
(check-expect (tax-return 80000 3 100 150 12000) -1008) ;; using given example

(test)