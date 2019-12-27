# alex-sheen-portfolio

CMSC 15100 at The University of Chicago

Homework 3 is an exercise in application programming. The details of the code -- exactly which helper functions to write, with which names and which types -- are largely left up to you.

The goal of the present application is to be able to draw both monthly and yearly calendars according to formatting specifications. Calendar formatting details are packed into the following data structure:

(define-struct CalendarFormat
  ([cell-size : Integer]
   [banner-bg-color : Image-Color]
   [banner-text-color : Image-Color]
   [day-bg-color : Image-Color]
   [day-text-color : Image-Color]
   [border-color : Image-Color]
   [number-color : Image-Color]))
To run Racket projects:
  Launch DrRacket. Then, go to the File menu, choose Install Package, and then enter 2htdp-typed in the text box.

  Click the run button to run the code.

Link to website:
https://alex-sheen.github.io/code/
