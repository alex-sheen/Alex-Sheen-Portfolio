#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")
(require "../include/cs151-image.rkt")

;; calc: approximates the integral of a function between given bounds
;; parameters: a function, bound a, bound b, and dx
;; output: approximate integral between a and b using step dx
(: calc ((Real -> Real) Real Real Real -> Real))
(define (calc f a b dx)
  (cond
    [(> a b) 0]
    [else (+ (* (f a) dx) (calc f (+ a dx) b dx))]
   )
)
(check-within (calc abs 0 10 0.1)
               50.499999999999996
                0.1)
(check-within (calc sin 0 pi 0.1)
               1.9995479597125971
                0.1)

;; f1: sample function
(: f1 (Real -> Real))
(define (f1 x)
  (+ 10
     (* 40 (cos (/ x 10)))
     (* 50 (sin (/ x 15))))
 )

;; draw-pos: draws the positive rectangles for a given function
;; parameters: a function
;;             the bounds for the integral
;;             the color of the image
;; output: an image approximation of the functin's integral
(: draw-pos ((Real -> Real) Real Real Real Image-Color -> Image))
(define (draw-pos f a b dx color)
  (cond
    [(> a b) empty-image]
    [(> (f a) 0) (beside/align "bottom" (rectangle dx (f a) "outline" color)
                               (draw-pos f (+ a dx) b dx color))]
    [else (beside/align "bottom" (rectangle dx 0 "outline" color)
                        (draw-pos f (+ a dx) b dx color))]
   )
)

;; draw-pos: draws the negative rectangles for a given function
;; parameters: a function
;;             the bounds for the integral
;;             the color of the image
;; output: an image approximation of the functin's integral
(: draw-neg ((Real -> Real) Real Real Real Image-Color -> Image))
(define (draw-neg f a b dx color)
  (cond
    [(> a b) empty-image]
    [(< (f a) 0) (beside/align "top" (rectangle dx (abs (f a)) "outline" color)
                               (draw-neg f (+ a dx) b dx color))]
    [else (beside/align "top" (rectangle dx 0 "outline" color)
                        (draw-neg f (+ a dx) b dx color))]
   )
)

;; draw-pos: draws the integral for a given function and its relevant information
;; parameters: a function
;;             the bounds for the integral
;;             the color of the image
;; output: an image approximation of the functin's integral
;;         as well as its bounds and its integral
(: draw-integral ((Real -> Real) Real Real Real Image-Color -> Image))
(define (draw-integral f a b dx color)
  (local
    {
     (define top_image (draw-pos f a b dx color))
     (define bottom_image (draw-neg f a b dx color))
     (define integral (text (number->string (calc f a b dx)) 16 'black))
     (define text_a (text (number->string a) 16 'black))
     (define text_b (text (number->string b) 16 'black))
     (define full_image (above top_image bottom_image))
     }
    (above (beside text_a full_image text_b) integral)
  )
)

;; visual tests
(draw-integral f1 -120 120 3 'blue)
(draw-integral f1 0 120 12 'blue)
(draw-integral f1 -120 120 12 'blue)

(test)