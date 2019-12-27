# alex-sheen-portfolio

CMSC 15100 at The University of Chicago

Lab 1 :

The citizens of Computonia are governed by a representative democracy and pay a federal income tax as described in this document. (1 thunk = 1 dollar)

The Computonian tax code is similar to the tax code of the United States in a few key ways.

Income tax
  Family units file for taxes as a group. Family income = sum of members' incomes.
  On tax day, each Computonian family unit computes what its taxes should have been for the year, which is usually different than the withheld amount, and settles the bill.

Marginal Tax Rate
  Computonia has the following marginal tax rate. There is no tax paid on money earned up to and including 24,000 thunks. The next 16,000 thunks earned are taxed at the rate of 12% (rounded up to the nearest thunk). After that, the next 35,000 thunks are taxed at 24%. Finally, all income over 75,000 thunks is taxed at the rate of 48%. Any fractional thunks in any of these computations are always rounded up.

Deductables
  Computonians are allowed to deduct from their income according to certain features of their lives that are deemed to have positive social value. In Computonia, this is whether or not they have installed solar panels at their home(s), and whether or not they grow their own produce in a home garden or farm. After the deductions have been subtracted from the income, the marginal tax rate determines how much tax they owe.

  The solar panel deduction is as follows. The unit is allowed to deduct 10 thunks per every square centimeter of solar panels installed, but they are not allowed to deduct more than 20% of their pre-deduction income.

  The garden deduction is as follows. The yield of food from the home garden is measured in pounds-per-year. The measure of pounds-per-year-per-person is computed by dividing the pounds-per-year by the number of people, rounding up to the nearest integer. That number is multiplied by 12. The unit can deduct that many thunks from their pre-deduction income, but the maximum garden deduction is 8,000 thunks.

Should they itemize their deductable?
  If Computonians choose to deduct for their solar panels and/or gardens, they are said to itemize their deductions. The alternative to itemizing deductions is to take the standard deduction. The standard deduction is computed simply according to the number of people in the family unit: it is 1,200 thunks for each person in the unit.


Example
  Let's posit a family unit of 3 people, earning 80,000 thunks per year, having 100 square centimeters of solar panels on their roof, and producing 150 pounds of fruits and vegetables per year in their home garden. Assume, furthermore, that this unit has had 12,000 thunks withheld from their pay during the year, all of which has already been paid to the CRS.

  In this case, it is preferable for the family unit to take the standard deduction and thus owe the lower amount of tax. Because, via withheld wages, they have already paid 12,000 to the CRS and owe only 10,992, the unit's tax outcome for the year is a refund from the CRS in the amount of 1,008 thunks.

  If you're thinking to yourself, wow, this is pretty complicated, and it would be nice for someone to write a computer program to figure it out, well, yes.

Complete the functions as specified below:

;; marginal-tax: compute the amount of tax owed on the given income.
(: marginal-tax (-> Integer Integer))

;; solar-panel-deduction: compute deduction of 10 thunks per
;;   square cm, but not more than 20% of income
(: solar-panel-deduction (-> Integer Integer Integer))

;; garden-deduction: compute deduction of lbs-per-year-per-person
;;   in thunks times 12, but not more than 8000
(: garden-deduction (-> Integer Integer Integer))

;; itemized: compute itemized deduction on income
(: itemized (-> Integer Integer Integer Integer Integer))

;; standard: compute the standard deduction for a family unit,
(: standard (-> Integer Integer))

;; should-itemize?: should family unit itemize or take standard?
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "solar-panels": area in square cm of solar panels
;; parameter "lbs-per-year": garden yield
;; output: #t if itemized deduction is larger than standard, #f otherwise
(: should-itemize? (-> Integer Integer Integer Integer Boolean))

;; tax-return: Determine the negative (refund) or positive (payment) due
;;   family unit, given their income as well as the amount withheld.
;; output: positive or negative debt to the CRS (negative debt is a refund)
(: tax-return (-> Integer Integer Integer Integer Integer Integer))

To run Racket projects:
  Launch DrRacket. Then, go to the File menu, choose Install Package, and then enter 2htdp-typed in the text box.

  Click the run button to run the code.

Link to website:
https://alex-sheen.github.io/code/
