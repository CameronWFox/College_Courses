; Goal is to create an output from symbols to numbers.
; All the symbols at the begining and the numbers at the end.
; We want to keep the order of the symbols and the order of numbers.

; We can not use a loop construct. We cant use anything that we have not covered in class.
; We cant code in C++ or C. Only use Scheme coding.
; Use the functional subset of the language, stick to recurssion.


; CONTRACT:1 Write a symNumSep Function.

; PURPOSE: It will take a flat list L of symbols and numbers, separates the members based
; on their type, and produces a flat list containing the same numbers but with the symbols
; in the same order preceding the numbers in the same order.

; CODE FUNCTIONS/STEPS:
;        Step 01: I take in a single (flat) list of symbols and numbers.

;        Step 02: I check if the list is null/empty.

;        Step 03: I check and find the symbols and numbers in the list.
;                 Starting with the first value in the list and keep testing.

;        Step 04: I then sort the list values into groups.
;                 One group for numbers and one group for symbols
;                 while keeping the order they are taken from the flat list.

;        Step 05: Then I send out the symbols in the same order followed by
;                 the number in the same order as well. 

; CODE:
;Step 01
(define (symNumSep L)
  (define (rm-all-sym L)
    ;Steps 02-03-04
    (cond ((null? L) '())
              ( (symbol? (car L))
                (rm-all-sym (cdr L) ) )
              (else (cons (car L)
                          (rm-all-sym (cdr L)))
                    )
              )
    )
  (define (rm-all-num L)
    ;Steps 02-03-04
    (cond ((null? L) '())
          ( (number? (car L))
                (rm-all-num (cdr L) ) )
          (else (cons (car L)
                          (rm-all-num (cdr L)))
                    )
          )
    )
  ;Step 05
  (append (rm-all-num L) (rm-all-sym L))
  )

; TEST CASES and EXPECTED OUTCOMES:
; From these example inputs for the function, the test case boundaries for this function
; would be if the function can order the symbols and numbers in the correct order. 
; (symNumSep  '(0 b 2 d)) (Ex 1)
; (symNumSep  '(a 1 c 8 5 e d f)) (Ex 2)
; Test Cases for Invalid Results:
; Ex 1: (0 2 b d) ; returning the list but the numbers are listed first
; Ex 1: (b 0 2 d) ; The list sorted the first symbol first but couldnt sort everything else
; Ex 2: (a c e d f) (1 8 5) : sorts the symbols and numbers but doesnt bring them together
; Ex 2: (1 8 5) (a c e d f) ; Similar result from the last test but the numbers are first
; Test Case for Correct Results
; Ex 1: (b d 0 2)
; Ex 2: (a c e d f 1 8 5)


; CONTRACT:2 Write a dupSymSpl Function.

; PURPOSE: It will take a nested list of symbols, strings, and numbers L, and produces a
; nested list of symbols and numbers by eliminating strings, and "immediately duplicating"
; each symbol at all levels.

; CODE:
(define (dupSymSpl L)
  (cond ((null? L) '())
        ((number? (car L))
         (cons (car L) (dupSymSpl (cdr L))))
        ((string? (car L))
         (dupSymSpl (cdr L)))
        (symbol? (car L)
                 (cons (car L) (cons (car L) (dupSymSpl (cdr L)))))
        )
  )


; TEST CASES and EXPECTED OUTCOMES:
;(dupSymSpl  '(a 1 b "a2" c 3)) =  (a a 1 b b  c c 3)
;(dupSymSpl  '( (a 1) b (("c" c)) 2 "2") = ( (a a 1) b b ((c c)) 2)

; CONTRACT:3 Write a dotProduct Function.

; PURPOSE: It will take two lists of numbers representing vectors, and produces their
; dot product (or reports their incompatibility if they are of unequal lengths).
; Extra Credit: Give another definition of dotProduct that uses higher-order functions
; map and foldr (reduce) given below.

; CODE:
(define (dotProduct l1 l2)
  (cond ((null? l1) (null? l2) 0)
        (else
         (+ (* (car l1) (car l2))
            (dotProduct (cdr l1) (cdr l2))))
   )
  )

; EXTRA CREDIT CODE:

; TEST CASES and EXPECTED OUTCOMES:
;(dotProduct   '(1 2) '(3 4) )  =  11
;(dotProduct   '(1 2 3) '(4 5 6))   =  32
;(Extra Credit: Give another definition of dotProduct that uses higher-order functions map and foldr (reduce) given below.)

; CONTRACT:4 Write a postfix Function out of a prefix Arithmetic Expression.

; PURPOSE: Given a prefix arithmetic expression built using +, *, variables (as symbols)
; and numbers, write a function postfix that transforms it into postfix form.

; CODE:
(define (postfix expr)
  (cond ((null? expr)'())
        ((number? expr) expr)
        ((symbol? (car expr))
         (append (cdr expr) (list (car expr))))
        ((list? expr)
            (list (postfix (cadr expr)) (postfix (caddr expr)) car expr))
  (else
   (append (postfix (cadr expr)) (postfix (caddr expr)) car expr))
 )
  )

; TEST CASES and EXPECTED OUTCOMES:
;(postfix   '(+ (* 1 2) (+ x y) ) ) =   ( (1 2 *) (x y +) +)
;(postfix   '(* z 6) ) =   (z 6 *)
;(postfix   '5)  =   5

; CONTRACT:5 Write a Foldr Function.

; PURPOSE: Foldr function is defined in the "Intermediate Student"-language in Racket IDE
; (but is not avalible in R5RS Scheme). Experiment with the following examples and their
; variants to understand its behavior.

; Examples to Experiment with:
; (foldr + 0(list-15-342))
; (foldr cons empty(list-15-342))
; (foldr cons empty(list 'a 'b)(list "x")empty(list 812)))

; Now define the higher-order function foldr in R5RS Scheme that satisfies the following
; template and test it at least on the R5RS-Scheme-compatible variants
; of the above examples (obtained by replacing empty with '()):

; (foldr f base '(x1 x2 ... xn))=(f'x1 (f'x2 ... (f'xn base)))

; CODE:
(define (foldr fn num lis)
      (cond ((null? lis) num)
                 (else (fn  (car lis) (foldr fn num (cdr lis))))
    )
)

; TEST CASES and EXPECTED OUTCOMES:
; (foldr + 12 '(1 2 3 4 5))
; (foldr * 6 '(4 6 8))
; (foldr - 24 '(1 2 3 4 5 6 7 8 9))

; CONTRACT:6(a) Write a function fib(using recursion).
; CONTRACT:6(b) Write a function recursiveCallCountFib.

; PURPOSE: 6(a) Compute Fibonacci sequence 0, 1, 2, 3, ...
; That is, (fib 0)=0, (fib 1)=1, and (fib 9)=34.
; PURPOSE: 6(b) Takes as input n and counts the number of recursive calls
; made to fib for n.
; That is, (map recursiveCallCountFib '(0 1 2 3 4 5 6)) = (0 0 2 4 8 14 24)

; CODE:
(define (fib n)
  (cond
      ((= n 0) 0)
      ((= n 1) 1)
      (else
        (+ (fib (- n 1))
           (fib (- n 2)))))
  )

; TEST CASES and EXPECTED OUTCOMES:

