# alex-sheen-portfolio

CMSC 15100 at The University of Chicago

Homework 1 Highlights

A 3Tree is a tree of degree 3 with integers at nodes.

Write the following functions:
(: num-nodes : 3Tree -> Integer)
(: sum-nodes : 3Tree -> Integer)
(: height : 3Tree -> Integer)
(: contains? : 3Tree Integer -> Boolean)
(: leftmost : 3Tree -> (U Integer 'None))
(: farthest-item : 3Tree -> (U Integer 'None))
(: abs-tree : 3Tree -> 3Tree)


Full Description :

Problem 1

Here are three ways to specify a line, all of which you have likely seen in a math class:

Slope-intercept form: a line in the form y = mx + b
A vertical line in the form x = x-intercept
As two points, which, by extending the single possible line segment between them infinitely in either direction, define a line

Convert a line into a string representation for a human to read using mathematical notation. Specifically:
A SlopeLine should be translated into a string similar to "y = 2 * x + 3"
A VerticalLine should be converted into a string like "x = 7"
A PointsLine should be converted into a string in the format "(2, 8) - (14, 24)", where the two points are represented using standard mathematical notation, and the first point in the struct is placed first

Write the following functions:
(: translate-up (-> Exact-Rational Line Line))
(: passes-through? (-> QPoint Line Boolean))
(: lines=? (-> Line Line Boolean))

Problem 2

Write the following functions:

mirror takes an IntTree and returns an IntTree with the same values and structure, except that at each node, the left and right subtrees are swapped.

int-tree->string-tree takes a tree with Integer values and generates a tree, with the same structure, that contains String values

right-edge consumes a StringTree and produces a String

Problem 3

A 3Tree is a tree of degree 3 with integers at nodes.

(: num-nodes : 3Tree -> Integer)
(: sum-nodes : 3Tree -> Integer)
(: height : 3Tree -> Integer)
(: contains? : 3Tree Integer -> Boolean)
(: leftmost : 3Tree -> (U Integer 'None))
(: farthest-item : 3Tree -> (U Integer 'None))
(: abs-tree : 3Tree -> 3Tree)




To run Racket projects:
  Launch DrRacket. Then, go to the File menu, choose Install Package, and then enter 2htdp-typed in the text box.

  Click the run button to run the code.

Link to website:
https://alex-sheen.github.io/code/
