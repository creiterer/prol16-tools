;; This example is taken from the label section (page 6) in the PROL16 assembler manual

	loadi r0, 3			; 0x0800, 0x0003
loop: 
	nop					; 0x0000
	dec r0				; 0x6C00
	loadi r5, loop		; 0x08A0, 0x0002
	loadi r6, end		; 0x08C0, 0x000A
	jumpz r6			; 0x2CC0
	jump r5				; 0x20A0
end:
	nop					; 0x0000
	
;; resulting memory layout
;; 		_____________________
;; 	0x0	|		0x0800		|
;; 		---------------------
;; 	0x1	|		0x0003		|
;; 		---------------------
;; 	0x2	|		0x0000		|	-> loop
;; 		---------------------
;; 	0x3	|		0x6C00		|
;; 		---------------------
;; 	0x4	|		0x08A0		|
;; 		---------------------
;; 	0x5	|		0x0002		|
;; 		---------------------
;; 	0x6	|		0x08C0		|
;; 		---------------------
;; 	0x7	|		0x000A		|
;; 		---------------------
;; 	0x8	|		0x2CC0		|
;; 		---------------------
;; 	0x9	|		0x20A0		|
;; 		---------------------
;; 	0xA	|		0x0000		|	-> end
