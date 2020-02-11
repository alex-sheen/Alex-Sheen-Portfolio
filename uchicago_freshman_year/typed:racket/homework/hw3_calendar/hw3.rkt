#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")
(require "../include/cs151-image.rkt")

;; ----------------------- Beginning of Lab 2 -----------------------------------

(define-struct Date
  ([m : Integer]
   [d : Integer]
   [y : Integer]))

;; note: for the month, 1 means January, 2 means February, etc.

(define-type Day
  (U 'Su 'M 'Tu 'W 'Th 'F 'Sa))

;; leap?: compute whether or not a year is a leap year.
;; a year is a leap year if it is divisible by 4 and not divisible by 100
;; or if it is divisible by 400.
;; parameter "income": an integer number of years
;; output: boolean, whether the year is a gap year
(: leap? (-> Integer Boolean))
(define (leap? year)
   (cond
     [(= 0 (modulo year 400)) #t]
     [(and (= 0 (modulo year 4)) (not (= 0 (modulo year 100)))) #t]
     [else #f]
   )
)
(check-expect (leap? 3) #f)
(check-expect (leap? 16) #t)
(check-expect (leap? 400) #t)
(check-expect (leap? 200) #f)


;; smart-date?: considers whether a date is reasonable
;; parameters : month, day, and year
;; output : error or the given date
(: smart-date (Integer Integer Integer -> Date))
(define (smart-date m d y)
  (cond
    [(or (< m 1) (> m 12)) (error "month out of range")]
    [(or (< y 1900) (> y 2099)) (error "year out of range")]
    [(and (= m 1) (or (< d 1) (> d 31))) (error "day out of range")]
    ;; if Feb and leap year
    [(and (= m 2) (leap? y) (or (< d 1) (> d 29))) (error "day out of range")]
    ;; if Feb and not leap year
    [(and (= m 2) (or (< d 1) (> d 28))) (error "day out of range")]
    [(and (= m 3) (or (< d 1) (> d 31))) (error "day out of range")]
    [(and (= m 4) (or (< d 1) (> d 30))) (error "day out of range")]
    [(and (= m 5) (or (< d 1) (> d 31))) (error "day out of range")]
    [(and (= m 6) (or (< d 1) (> d 30))) (error "day out of range")]
    [(and (= m 7) (or (< d 1) (> d 31))) (error "day out of range")]
    [(and (= m 8) (or (< d 1) (> d 31))) (error "day out of range")]
    [(and (= m 9) (or (< d 1) (> d 30))) (error "day out of range")]
    [(and (= m 10) (or (< d 1) (> d 31))) (error "day out of range")]
    [(and (= m 11) (or (< d 1) (> d 30))) (error "day out of range")]
    [(and (= m 12) (or (< d 1) (> d 31))) (error "day out of range")]
    
    [else (Date m d y)]
   )
)
(check-error (smart-date 99 2 2019) "month out of range")
(check-error (smart-date -10 2 2019) "month out of range")
(check-error (smart-date 10 2 1890) "year out of range")
(check-error (smart-date 10 2 2200) "year out of range")
(check-error (smart-date 10 49 2019) "day out of range")
(check-error (smart-date 10 -2 2019) "day out of range")
(check-expect (smart-date 4 2 2019) (Date 4 2 2019))

;; day-of-week: computes day of the week from a given date
;; parameter: a date
;; output: a day of the week
(: day-of-week (Date -> Day))
(define (day-of-week date)
 (local
    {
     (define (compute-n date) (match date ;; returns the n value of a date
                         [(Date m d y)
                         (+ (- y 1900) (compute-j date) d (exact-floor (/ y 4)))]
                           ))
     (define (compute-j date) (match date ;; returns the j of a month
                         [(Date 1 _ y) (cond
                              [(leap? y) 0]
                              [else 1]
                              )]
                         
                         [(Date 2 _ y) (cond
                              [(leap? y) 3]
                              [else 4]
                              )]
                         
                         [(Date 3 _ _) 4]
                         [(Date 4 _ _) 0]
                         [(Date 5 _ _) 2]
                         [(Date 6 _ _) 5]
                         [(Date 7 _ _) 0]
                         [(Date 8 _ _) 3]
                         [(Date 9 _ _) 6]
                         [(Date 10 _ _) 1]
                         [(Date 11 _ _) 4]
                         [(Date 12 _ _) 6]
                         [else (error "month out of range")]
                         ))
     ;; returns the remainder of 1 / n for a given date
     (define (compute-day-number date) (remainder (compute-n date) 7 ))
     ;; takes the remainder of 1 / n and turns it into a Day
     (define (number-to-day num) (match num
                                 [0 'Su]
                                 [1 'M]
                                 [2 'Tu]
                                 [3 'W]
                                 [4 'Th]
                                 [5 'F]
                                 [6 'Sa]
                                ))
    }
    
    (number-to-day (compute-day-number date)) ;; returns the Day
  ) 
)
(check-expect (day-of-week (Date 1 1 2019)) 'Tu)
(check-expect (day-of-week (Date 2 18 2002)) 'M)
(check-expect (day-of-week (Date 3 3 2009)) 'Tu)
(check-expect (day-of-week (Date 4 4 2031)) 'F)
(check-expect (day-of-week (Date 5 11 2080)) 'Sa)
(check-expect (day-of-week (Date 6 24 2001)) 'Su)
(check-expect (day-of-week (Date 7 27 2061)) 'W)
(check-expect (day-of-week (Date 8 7 2099)) 'F)
(check-expect (day-of-week (Date 9 29 2034)) 'F)
(check-expect (day-of-week (Date 10 18 2040)) 'Th)
(check-expect (day-of-week (Date 11 19 2087)) 'W)
(check-expect (day-of-week (Date 12 9 2077)) 'Th)

;; yesterday: computes day before a given date
;; parameter: a Date
;; output: the Date before
(: yesterday (Date -> Date))
(define (yesterday date)
 (match date
   [(Date m d y)
    (cond
       
       [(and (= m 1) (= d 1)) (Date 12 31 (- y 1))] 
       [(and (= m 2) (= d 1)) (Date (- m 1) 31 y)]
       [(and (= m 3) (= d 1) (leap? y)) (Date (- m 1) 29 y)] ;; if leap year
       [(and (= m 3) (= d 1)) (Date (- m 1) 28 y)]    ;; if not a leap year 
       [(and (= m 4) (= d 1)) (Date (- m 1) 31 y)] 
       [(and (= m 5) (= d 1)) (Date (- m 1) 30 y)] 
       [(and (= m 6) (= d 1)) (Date (- m 1) 31 y)] 
       [(and (= m 7) (= d 1)) (Date (- m 1) 30 y)] 
       [(and (= m 8) (= d 1)) (Date (- m 1) 31 y)] 
       [(and (= m 9) (= d 1)) (Date (- m 1) 31 y)] 
       [(and (= m 10) (= d 1)) (Date (- m 1) 30 y)] 
       [(and (= m 11) (= d 1)) (Date (- m 1) 31 y)] 
       [(and (= m 12) (= d 1) (Date (- m 1) 30 y))]
       [else (Date m (- d 1) y)]
     )]
  )
)
(check-expect (yesterday (Date 12 9 2077)) (Date 12 8 2077))
(check-expect (yesterday (Date 1 1 2077)) (Date 12 31 2076))
(check-expect (yesterday (Date 5 1 2077)) (Date 4 30 2077))
(check-expect (yesterday (Date 3 1 2077)) (Date 2 28 2077))
(check-expect (yesterday (Date 3 1 2004)) (Date 2 29 2004))

;; tomorrow computes day after a given date
;; parameter: a Date
;; output: the Date befafterore
(: tomorrow (Date -> Date))
(define (tomorrow date)
 (match date
   [(Date m d y)
    (cond
       
       [(and (= m 1) (= d 31)) (Date (+ m 1) 1 y)] 
       [(and (= m 2) (leap? y) (= d 29)) (Date (+ m 1) 1 y)] ;; if leap year
       [(and (= m 2) (= d 28)) (Date (+ m 1) 1 y)]       ;; if not leap year
       [(and (= m 3) (= d 31)) (Date (+ m 1) 1 y)]          
       [(and (= m 4) (= d 30)) (Date (+ m 1) 1 y)] 
       [(and (= m 5) (= d 31)) (Date (+ m 1) 1 y)] 
       [(and (= m 6) (= d 30)) (Date (+ m 1) 1 y)] 
       [(and (= m 7) (= d 31)) (Date (+ m 1) 1 y)] 
       [(and (= m 8) (= d 31)) (Date (+ m 1) 1 y)] 
       [(and (= m 9) (= d 30)) (Date (+ m 1) 1 y)] 
       [(and (= m 10) (= d 31)) (Date (+ m 1) 1 y)] 
       [(and (= m 11) (= d 30)) (Date (+ m 1) 1 y)] 
       [(and (= m 12) (= d 31) (Date 1 1 (+ y 1)))]
       [else (Date m (+ d 1) y)]
     )]
  )
)
(check-expect (tomorrow (Date 12 9 2077)) (Date 12 10 2077))
(check-expect (tomorrow (Date 1 31 2077)) (Date 2 1 2077))
(check-expect (tomorrow (Date 5 31 2077)) (Date 6 1 2077))
(check-expect (tomorrow (Date 2 28 2077)) (Date 3 1 2077))
(check-expect (tomorrow (Date 2 29 2004)) (Date 3 1 2004))
(check-expect (tomorrow (Date 12 31 2004)) (Date 1 1 2005))

(: add-days (Integer Date -> Date))
(define (add-days num date)
  (match* (num date)
    [(0 (Date m d y)) (Date m d y)]
    [(num (Date m d y)) (cond
                         [(> num 0) (add-days (- num 1) (tomorrow (Date m d y)))]
                         [else (add-days (+ num 1) (yesterday (Date m d y)))]
                          )]
  )
)
(check-expect (add-days 1 (Date 12 31 2004)) (Date 1 1 2005))
(check-expect (add-days 5 (Date 12 1 2004)) (Date 12 6 2004))
(check-expect (add-days 5 (Date 12 30 2004)) (Date 1 4 2005))
(check-expect (add-days -5 (Date 12 30 2004)) (Date 12 25 2004))



;; ----------------------- Beginning of Homework 3 ------------------------------

(: yes-byte? (Integer -> Byte))
;; yes-byte?: ensures that a number is a byte
;; parameters: an integer
;; output: a byte, if the integer is a byte, error otherwise
(define (yes-byte? num)
  (if (byte? num) num (error "num is not a byte"))
)
(check-expect (yes-byte? 233) 233)
(check-error (yes-byte? 23002) "num is not a byte")


;; CalendarFormat Struct
(define-struct CalendarFormat
  ([cell-size : Integer]
   [banner-bg-color : Image-Color]
   [banner-text-color : Image-Color]
   [day-bg-color : Image-Color]
   [day-text-color : Image-Color]
   [border-color : Image-Color]
   [number-color : Image-Color]))

;; CalendarFormat Examples
(define example-calendar
  (CalendarFormat 75 'gray 'blue 'green 'black 'green 'pink))
(define example-calendar2
  (CalendarFormat 70 'red 'green 'blue 'orange 'pink 'black))
                                         


(: month-string (Integer -> String))
;; month-string: converts a number of month to string of month
;; parameters: a number of month
;; output: a string of that month
(define (month-string m)
  (match m
    [1 "January"]
    [2 "February"]
    [3 "March"]
    [4 "April"]
    [5 "May"]
    [6 "June"]
    [7 "July"]
    [8 "August"]
    [9 "September"]
    [10 "October"]
    [11 "November"]
    [12 "December"]
    [else (error "month out of range")]
    
  )
)
(check-expect (month-string 1) "January")
(check-expect (month-string 2) "February")
(check-expect (month-string 3) "March")
(check-expect (month-string 4) "April")
(check-expect (month-string 5) "May")
(check-expect (month-string 6) "June")
(check-expect (month-string 7) "July")
(check-expect (month-string 8) "August")
(check-expect (month-string 9) "September")
(check-expect (month-string 10) "October")
(check-expect (month-string 11) "November")
(check-expect (month-string 12) "December")
(check-error (month-string 50) "month out of range")

(: draw-month (CalendarFormat Integer Integer -> Image))
;; draw-month: produces a calendar image for a given month
;; parameters: CalenderFormat, month, year
;; output: image of calender for that month and year
(define (draw-month cal m y)
(local
  {
   (: draw-rect (Integer -> Image))
   ;; draw-rect: draws each day cell
   ;; parameters: the number of day of month of the cell
   ;; output: an image of text of the day overlayed on its cell
   (define (draw-rect d)
     (overlay
        (text
             (if ;; places blanks for days prior to given month
                (> (- d get-month-offset) 0)
                (number->string (- d get-month-offset))
             "")
            (yes-byte? (exact-round (/ (CalendarFormat-cell-size cal) 6)))
            (CalendarFormat-number-color cal))
        (rectangle
          (CalendarFormat-cell-size cal)
          (exact-round (/ (CalendarFormat-cell-size cal) 4))
          "outline" (CalendarFormat-border-color cal))))

 
   (: build-day-list (Integer Integer -> (Listof Integer)))
   ;; build-day-list: constructs list of ints representing the days since the
   ;;                 first day of that week, contains 7 ints to make 1 week
   ;;                 e.g. if 4/5/2020 is Sunday, then 4/7/2020 -> 2 in the list
   ;;                 -1 represents days outside of initial month
   ;; (build-day-list 10 2020) -> (0, 1, 2, 3, 4, 5, 6)
   ;; (build-day-list 11 2020) -> (0, 1, -1, -1, -1, -1, -1)
   ;; parameters: the starting day (number) of that week and a counting number x
   ;; output: list of ints representing the offset for the days of that week
   (define (build-day-list start-d x)
     (if (< x 7)
      ;; checks if all the days in the next week are still within the given month
      (if (= m (Date-m (tomorrow (Date m (+ x (- start-d get-month-offset)) y))))
         (cons (+ start-d x) (build-day-list start-d (+ x 1)))
         (cons (+ start-d x) (build-list (- 7 x 1) (lambda ([i : Integer]) -1))))
       '())
   )

   ;; get-month-offset: returns number of day of week
   ;; parameters: day of week symbol
   ;; output: integer day of week
   (define get-month-offset
     (match (day-of-week (Date m 1 y))
       ['Su 0]
       ['M 1]
       ['Tu 2]
       ['W 3]
       ['Th 4]
       ['F 5]
       ['Sa 6]
     )
   )
   
   (: build-rows (Integer Integer -> Image))
   ;; build-rows: builds list of rows of the calendar
   ;;             another function can then stack build-rows lists
   ;;             to make the completed calendar
   ;; parameters: given month, and the current day to start recursion on
   ;; output: list of images, where each image is one row of the calendar
   (define (build-rows m current-d)
     ;; checks if all the days in the next week are still within the given month
     (if (= m (Date-m (add-days 7 (Date m current-d y))))
         (above (foldr beside empty-image
                       (map draw-rect (build-day-list current-d 0)))
                (build-rows m (+ 7 current-d)))
         
         (foldr beside empty-image
                       (map draw-rect (build-day-list current-d 0))))
   )


   ;; banner: constructs the month banner image
   ;; parameters: none
   ;; output: image containing banner background and text
   (define banner (overlay (text (string-append
                                  (month-string m) " " (number->string y))
                                  (yes-byte?
                                   (exact-round
                                    (/ (CalendarFormat-cell-size cal) 6)))
                                  (CalendarFormat-banner-text-color cal))
                           (rectangle
                            (* 7 (CalendarFormat-cell-size cal))
                            (exact-round (/ (CalendarFormat-cell-size cal) 4)) "solid"
                            (CalendarFormat-banner-bg-color cal))))
   
  (: day-box (String -> Image))
  ;; day-box: constucts a cell to label the columns for the days of the week
  ;; parameters: string of day of the week
  ;; output: an image of text overlayed on a cell
  (define (day-box str)
    (overlay
      (text str
         (yes-byte? (exact-round (/ (CalendarFormat-cell-size cal) 6)))
         (CalendarFormat-day-text-color cal))
      (draw-box (CalendarFormat-day-bg-color cal))
  ))
  
  (: draw-box (Image-Color -> Image))
  ;; draw-box: constructs a day cell for labeling the day columns
  ;; parameters: color of cell
  ;; output: cell of the given color
  (define (draw-box color)
    (rectangle
      (CalendarFormat-cell-size cal)
      (exact-round (/ (CalendarFormat-cell-size cal) 4)) "solid"
      color)
  )

  ;; months: constructs the row of cells labeling the days of the week columns
  ;; parameters: none
  ;; output: an image containing the day label cells
  (define months (beside
                  (day-box "Su")
                  (day-box "M")
                  (day-box "Tu")
                  (day-box "W")
                  (day-box "Th")
                  (day-box "F")
                  (day-box "Sa")
                 ))
   }
  ;; constructs final image by putting together
  ;; the month banner, day cells, and day number cells
  (above banner months (build-rows m 1))
  )
)
;; ------------ testing ---------------
;;(draw-month example-calendar 4 2020)
;;(draw-month example-calendar2 4 2020)
;; example-calendar2
;; cell-size : 70
;; banner-bg-color : red
;; banner-text-color : green
;; day-bg-color :  blue
;; day-text-color : orange
;; border-color : pink
;; number-color : black

(: draw-year (CalendarFormat Integer Integer -> Image))
;; draw-year: produces an image of the months for the whole year
;; parameters: CalendarFormat, padding in pixels, and a year
;; output: 3x4 image of months for that year
(define (draw-year cal padding y)
  (local
    {
     (: build-row (Integer -> Image))
     ;; build-row: constructs row of month images
     ;; parameters: initial month
     ;; output: image containing 3 months of the year in a row
     (define (build-row m) (beside/align "top"
                            (draw-month cal m y)
                            (make-padding padding)
                            (draw-month cal (+ 1 m) y)
                            (make-padding padding)
                            (draw-month cal (+ 2 m) y)
                            ))
     (: make-padding (Integer -> Image))
     ;; make-padding: returns a transparent image for padding
     ;; parameters: dimensions of the padding in pixels
     ;; output: transparent padding image
     (define (make-padding p)
       (rectangle p p "solid" (color 255 255 255 0))
     )
   }
   ;; constructs final image by alternative month rows and padding
   (above (build-row 1)
          (make-padding padding)
          (build-row 4)
          (make-padding padding)
          (build-row 7)
          (make-padding padding)
          (build-row 10))

))
(draw-year example-calendar2 7 2020)
;; example-calendar2
;; cell-size : 70
;; banner-bg-color : red
;; banner-text-color : green
;; day-bg-color :  blue
;; day-text-color : orange
;; border-color : pink
;; number-color : black


(test)