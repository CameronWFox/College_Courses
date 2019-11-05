
Scheme Definition

(define (cart2 x y)
  (if (null? x) '()
      (append (couple (car x) y)
              (cart2 (cdr x) y)
       )
   )
 )


(define (couple x y)
  (if (null? y) '()
      (cons (list a (car y))
            (couple a (cdr y))
       )
   )
 )

Alternate Syntax : lambda

(define cart2
  (lambda (x y)
    (if (null? x) '()
        (append (couple
         )
     )

  )
)
  )

Clojure Syntax

(defn couple [a y]
  (if (empty
   )
  )
  )

Powerset

> (powerset '(2))
          (() (2))
> (powerset '(1 2))
   ( (1) (1 2) () (2) )
> (powerset '(0 1 2))
  ( (0 1) (0 1 2) (0) (0 2) )
    (1)   (1 2)   ()  (2)





(define (powerset s)
  (if (null? s) '(())
      (append (ins (car s)
                   (powerset (cdr s))
                   )
       )
    (powerset (cdr s))
   )
 )

(define (ins a ss)
  (if (null? ss) '()
      (cons (cons a (car ss))
            (ins a (cdr ss))
       )
   )
 )

Alternative Syntax : let

(define (powerset s)
  (if (null? s) '()
      (let ( (aux (powerset (cdr s))) )
        (append (ins (car s) aux)
                aux
         )
       )
   )
  )

(define (ins a ss)
  (if (null? ss) '()
      (cons (cons
       )
   )
 )
  )


Tweek the recursive definitions

Remove-First-TopLevel
  (define (rm-fst-top  sym lis)
    (if (null? lis) '()
        (if (eq? sym(car lis)) (cdr lis)
            (cons (car lis)
                  (rm-fst-top sym (cdr lis))
             )
         )
     )
   )
  >(rm-fst-top 'a '(b (b a)a b a)) = (b(b a) b a)

Alternative Syntax : if => cond
 (define (rm-fst-top  sym lis)
    (cond ((null? lis) '())
          ((eq? sym(car lis)) (cdr lis))
          (else
           (cons (car lis)
                  (rm-fst-top sym (cdr lis))
            )
     )
   )
  )
  >(rm-fst-top 'a '(b (b a)a b a)) = (b(b a) b a)

Remove-All-TopLevel
(define (rm-all-top sym lis)
  (cond ((null? lis) '())
        ((eq? sym(car lis))
         (rm-all-top sym (cdr lis)))
        (else (cons (car lis)
                    rm-all-top sym (cdr lis)))
        )
   )
  >(rm-all-top 'a '(b (b a)a b a)) = (b (b a) b)

Remove-All-Expression-TopLevel
(define (rm-all-top exp lis)
  (cond ( (null?
 )
          )))

Remove-All
(define (rm-all sym ll)
  (cond ( (null? ll) '())
        ( (symbol? (car ll))
          (if (eq? sym (car ll))
              (rm-all sym (cdr ll))
              (cons (car ll)
                    (rm-all sym (cdr ll))))
          )
        (else (cons (rm-all sym (car ll))
                    (rm-all sym (cdr ll))
               )
         )
   )
 )
>(rm-all 'a '(b (b a) a b a)) - (b (b) b)
- Double Recursion

Insertion Sort (Note: creates  sorted copy)

(define (insert n lon)
  (cond ((null? lon)(list n))
        ((> n (car lon))
         (cons (car lon) (insert n (cdr lon))))
        (else (cons n lon))
   )
 )
(define (ins-sort lon)
  (if (null? lon) '()
      (insert (car lon) (ins-sort (cdr lon)))
   )
 )
- Precondition: second arg to insert ordered.
- Postcondition: insert returns an ordered list.


Clojure Syntax
(defn insert [n lon]
  (cond (empty? lon) (list n)
        (> n (first lon))
        (cons (first lon) (insert n (rest lon)))
        :true (cons n lon))
   )
 )

(defn ins-sort [lon]
  (if (empty? lon) '()
      (insert (first lon) (ins-sort (rest lon)))
   )
 )
- Precondition: second arg to insert ordered.
- Postcondition: insert returns an ordered list.



Subset (uses OR and AND instead of IF)
(define (subset? ss s)
  (or (null? ss)
      (and (member (car ss) s)
           (subset? (cdr ss) s)))
 )

1=> (subset? '(a b c) '(A p 1 C 2 B q r))
#t
2=> (subset? '(a b c) '(p))
#f

- member(x, y) takes two values, a list of elms and a value.
(i.e. cdr or car of ss in this ex)



Subset in Clojure (cf. case sensitive Scheme)
(defn subset? [ss s]
  (or (empty? ss)
      (and (some #(= (first ss) %) s)
           (subset? (rest s)))
 ))
> (subset? '() '(A p 1 C 2 B q r))
  true



Example Expression Evaluation:
A simple syntax directed translation
expr-> x | y | z
expr-> (+ expr expr)
expr-> (if expr expr expr)

write a recurrsive definition for a function ops that counts the umber of "+"s.
(define (ops s)
  ; e is assumed to be a symbol or a list.
  (cond
    ((symbol? e) 0)
    ((eq? (car e) '+)
     (+ 1 (ops (cadr e))
        (ops (caddr.e))) )
    ((eq? (car e) 'if)
     (+ (ops (cadr e))
        (ops (caddr e))
        (ops (cadddr e))))
    (else (display 'ILLEGAL))
   )
 )


(defn third [x] (second (rest x)))
(defn ops [e] ; Clojure code.
  "e is assumed to be a symbol or a list"
  (cond
    (symbol? e) 0
    (= (first e) '+)
    (+ 1 (ops (second e))
       (ops (third e)) )
    (= (first e) 'if)
    (+ (ops (second e))
       (ops (third e))
       (ops (last e)))
    true 'ILLEGAL
    ))


(Alternative Scheme syntax with member and case-construct (not equivalent))
(define (ops e)
  ; e is assumed to be a  symbol or a list.
  (if (member e '(x y z)) 0
      (if (symbol? e) (display 'ILLEGAAL)
          (case (car e)
            ((+) (+ 1 (ops (cadr e))
                    (ops (caddr e))) )
            ((if) (+ (ops (cadr e))
                     (ops (caddr e))
                     (ops (cadddr e))) )
            (else (display 'ILLEGAL))) )
      ))




; High-Order Functions

; Equivalent Notations
; Both syntax of these code segments are correct and mean the same thing. 
(define (f x y) (...body...))
=
(define f
  (lambda (x y)
    (...body...)
    )
  )


;Function Values
(define tag
  (lambda (t l) (cons t l))
  )
(tag 'int '(1)) -> (int 1)
; What characterizes a function?
; Expression in the body of the

;Anonymous Functions

( (lambda (t  l) (cons t l))
 'int '(1) )
; name of the function is "irrelevant"
; Simplification:
; (define tag cons)

; Assigning function values is similar to asigning primitive values. (first-class values).


; In Scheme Higher-Order Functions
; - passed to other functions
; - returned from functions
; - stored in data structures
;   a. LISP/C++/Java support approximations in a round about way.
;     1. LISP : Meta-Programming, C++ Function pointers
;     2. Java : via Objects(Before JDK 7)
;   b. Scala, Python, Java (cloures) and C# (delegates) are multi-paradigm
; languages with support for higher-order functions.




; Applications
; - Abstracting commonly occuring patterns of control. (factoring)
; - Defining generic functions.
; - Instantiating generics.
; O


; Factoring Commonality

;(1 2 ... n) ->
;(1 4 ... n^2)
;
(define (sql L)
  (if (null? L) ()
      (cons
       (* (car L)
          (car L)
          )
       (sql (cdr L))
       )))

;(a b c) ->
;((a) (b) (c))
;
(define (brac L)
  (if (null? L) ()
      (cons
       (list
          (car L)
          )
       (brac (cdr L))
       )))
;
;
;
;
;
;

; The Map Function
; Map is a high order function.
; It take a function as an input.

(define (map fn lis)
  (if (null? lis) '()
      (cons (fn (car lis))
            (map fn (cdr lis))
            )
      )
  )
; 
; (map (lambda(x)  (* x x)) '(1 2 3))
; (map (lambda(x) (list x)) '(a b c))

; Built In Map:
; (map + '(1 2 3) '(4 5 6))   = (5 7 9)

; foldr (reduce and foldl (accumulate)
; (Racket:> Intermediate Level)

; foldr:
; takes exactly 3 arguments.
; - binary function, , a list function
; starts with processing variables from the right.
; ex: (foldr + 100 (lis 2 4 8))
; = 2 + 4 + 8 + 100
; = 114

; (foldr cons '(c) '(a b))
; = (a b c)

; foldl:
; processes variables from the left first instead of the right.

; ex: (foldl * 100 (list 2 4 8))
; = 8 * 4 * 2 * 100
; = 6400

; (foldl cons '(c) '(a b))
; = (b a c)


;Templates/Generics
(define (imax x y)
  (if (< x y) y x)
  y x )
; Instantiation
(define (maxg lt?)
  (lambda (x y)
    (max lt? x y))
)



; Function generating function.
; - closure construction.




; Recursion vs Higher-Order Functions

(define-struct cost ($))


(define (totalCost cl)
  )


; Scoping

; Rules governing the association of
; use of a variable with the corresponding declaration.

; Imperative Language: Local/non-local variables
; Functional Languages: Bound,free variables



; Scoping Rules: enable determination of
; declaration corrisponding to a non-local/free variable.

; Alternatives:

; - Fixed at function definition time
;  - Static/lexical scoping
;   - Scheme, Ada, C++, Java, C#, etc

; - Fixed at function call time
;  - Dynamic scoping
;   - Franz LISP, APL, etc
; Dynamic scoping came about by accident. Very staight forward to implement forward calls
; The use of dynamic scoping is contrdicting to our meaning of free variables

;Pascal Example:
proc p;
varz:int;
            proc  q;
            begin z := 5  end;
     proc r;
     var z:int;
     begin q end;
               proc s;
               var z:int;
               begin q end;
  begin...end;


; Higher-Order Functions

; Anonymous Function
( (lambda (t l) (cons tl))
  'int '(1) )
; Name of function is irrelevent




; Scoping Functional Style

(define y 5) ; Top Level
( (lambda (x) (+ x y))  3) ; x is bound to 3,then compute x + y, y is 5. We get 8

- Point of definition = Point of call.

(define (f x) (+ x y))
 (define (g y) (f y))
        (g 16); y and x are both set as 16, 
- Naming context of definition =/=
Naming context of call.


; Static Scoping
(g y) ; y <- 16
(f y) ; y <- 16
(+ x y) ; x <- 16
        ; y <- 5
; answer 21

; Dynamic Scoping
(g y) ; y <- 16
(f y) ; y <- 16
(+ x y) ; x <- 16
        ; y <- 16
        ; y <- 5
; answer 32


; Closure:

(define (addn n)
  (lambda (x) (+ x n) )
  )
(addn 5) = (lambda (x)
             (+ x n)    ; n <- 5
             )
; Closure = Function Definition + Creation-time environment
 ; (to enforce lexical scoping for free variables)





; Scoping in Clojure

; Application
;  Instantiating generic functions.
;  Object-oriented Programming
;    Using (1) let-construct (to introduce ocal variables and
;    (2) assignments, objects and classes can be simulated.

; Streams
;

; Lambda Expressions

(define (id x) x) ; id of the value return the same value
> x
(define id (lambda (x) x) ) ; same function as above, just written differently

(lambda (x) x)

(  (lambda (x) x)  5 )
; call expression has two members. the operator and operandor

(lambda () 5) ;


(lambda () 1) ; no value is being given. Also we just defined the function here.
( (lambda () 1) ) ; so we add another pair of parenthithese,
                  ; because we dont need an argument.
                  ; This is running the function.

; We have a function calling itself
( (lambda (x) x)
  (lambda (y) y)  )
;  and returns the id function
( (lambda (x)  (x x)) ; if this is applied on itself, it goes into a finite loop
  (lambda (y) y)  )

; Java: Design Goals

; A general purpose concurrent object-oriented language for the Internet
; Designed by James Gosling around 1995
; Framework-Oriented Programming


; Simplicity
; Programmer perspective








; Non-portability : gotcha.c


; Same program but in Java





; Posible outcomes

; SPARC: cc/gcc gotcha.c-idl; a.out
; - 6 1 6
; Alpha, MIPS: cc/gcc gotcha.c-idl; a.out
; - 5 1 6
; SUN-3: cc gotcha.c-idl; a.out
; - 6 1 5



; For the Exam:
; Rewrite the definitions done in class to help understand how everything works
; 


 ; Class Notes
Ways to Damage productivity and slow your computer and use up memory

Programmer Perspective
- When you agessively use memory creating dangling pointers
- Also when you are not watching memory consumtion and clearing out clutter

Implementer perspective
- no multiple inheretance of code
    a. 
- not allowing multiple overloads



Garbegd collection helps with two atribultes
Both Helps with memory management and clearing space to gve increased abstraction to the programmer
- Abstraction
  a. 
- Modularity
a. 

Portability
- Architecture-neutral
a. Size of integer, char, etc. and the meaning of floating point oporations fixed by the language

- Platform Independent
a. Independence from the underlying Operating System

This is achieved using Java Virtual Machine implemented as an interpreter/plugin running on different platforms/browzers





Java Collections: Interface

       Collections                Map
     /             \               /
   Set             List         Sorted Map
    /
Sorted List


List structures are ordered structures where duplicates make a difference

























Language called STringly typed if it is able to catch errors and will not miss them.
This is what strong typed language garentees



Correctness Criteria: When you satisfy the post conditions, are you done?
Have you done what was needed?





Java Compiler and Interpreter
                 source code
        javac     ;  |                   
           -------bytecode---------
  java   /      /    JIT     \     \
     /         /              \      \     native code
  mips    pentium (x86)    sparc    ARM










Next Topic:

- Smallest Program in Java must be a class (No Matter What)
- In any directory you must have one public class
- 

















