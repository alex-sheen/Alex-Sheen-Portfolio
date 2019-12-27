# alex-sheen-portfolio

CMSC 15100 at The University of Chicago

Homework 2 Highlights

Problem 1

Binary tree functions
(: num-leafs : (All (A) ((Tree A) -> Integer)))
(: same-layout? : (All (A B) ((Tree A) (Tree B) -> Boolean)))

Problem 2

You are on an internship at UsuryBank, which is about to introduce a new credit card, the VigorousRewards Plutonium Card. It is your job to write some of the bookkeeping software for this product.

Like all credit cards, customers can make purchases, return merchandise, resulting in a refund, and make a payment towards their balance due.

The VigorousRewards Plutonium Card offers customers cash back for using their cards. In particular:

Customers who spend less than $1000 in a cycle receive 1% cash back.
Customers who spend at least $1000 and less than $2000 in a cycle receive 1.25% cash back.
Customers who spend $2000 or more in a cycle receive 1.5% cash back.


Problem 3

The following two functions work with polymorphic lists or trees and are higher-order functions, that is, they take in a function as a parameter.
(: count-flagged : (All (A) ((A -> Boolean) (Listof A) -> Integer)))

This function takes in a list of values and a function that, given a single value from the list, returns true or false. It should return the number of elements in the list for which the provided function returned true.
(: prune-tree : (All (A) ((A -> Boolean) (Tree A) -> (Tree A))))

To run Racket projects:
  Launch DrRacket. Then, go to the File menu, choose Install Package, and then enter 2htdp-typed in the text box.

  Click the run button to run the code.

Link to website:
https://alex-sheen.github.io/code/
