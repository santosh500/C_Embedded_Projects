;;*****************************************************************************
;;
;;	Assembly language subroutine
;;
;;		Author: 		Gary J. Minden
;;		Organization:	KU/EECS/EECS 388
;;		Date:			2014-04-18
;;		Version:		1.0
;;
;;		Purpose:		Assembly language subroutine
;;
;;		Notes:			Modified by Brad Torrence
;;
;;*****************************************************************************
;;

;;
;;	This subroutine computes a value based on four input arguements.
;;	The arguments are assumed to be in CPU registers R0 - R3
;;	  (AKA A1 - A4)
;;

;;	Declare sections and external references

		.global		FIBcompute				; Declare entry point as a global symbol

		.text								; Program sections

FIBcompute:									; Entry point

;;
;;	Save necessary registers
;;
;;	Since this subroutine does not use registers other than R0 - R3,
;;	  and we do not call another subroutine, we don't need to save
;;	  any registers.
;;  If you modify the following code to use registers > R3,
;;    then you MUST save the registers to the stack before use,
;;    and you MUST restore these registers before returning to the caller

;;
;;	Allocate local variables on the Stack
;;
;;	Since this subroutine does not have local variables,
;;	  no Stack space need be allocated.
;;

;;
;;	For demonstration, this subroutine computes the following:
;;        X = R0 + R1
;;        Y = R2 + R3ADDS		R0,R1
;;        RESULT = X + Y
;;		ADDS		R2,R3

;;  Compute F10
;;


		PUSH {R2,R3,R4,R5,R6,R7,R8,R9,R10}
		MOV R2,R1
		ADD R2,R0
		MOV R3,R2
		ADD R3,R1
		MOV R4,R3
		ADD R4,R2
		MOV R5,R4
		ADD R5,R3
		MOV R6,R5
		ADD R6,R4
		MOV R7,R6
		ADD R7,R5
		MOV R8,R7
		ADD R8,R6
		MOV R9,R8
		ADD R9,R7
		MOV R10,R9
		ADD R10,R8


;;f0 is 58 and f1 is 35

;;  Compute Y



;;  Compute RESULT

		MOV	R0,R10
		POP {R2,R3,R4,R5,R6,R7,R8,R9,R10}

;;
;;	Return from the subroutine with the result in R0
;;
		BX			LR				; Branch to the program address in the Link Register

		.end

