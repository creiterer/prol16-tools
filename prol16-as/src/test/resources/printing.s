;; A listing of all PROL16 print instruction variants

equ DataAddress, 8080h

loadi r1, CAFEh

;; variant 1: printing a register
print r1

;; variant 2: printing a value
print BABEh

;; variant 3: printing a defined symbolic constant
print DataAddress

;; variant 4: printing the address of a label
label:
print label

;; TODO: variant 5: printing a string
