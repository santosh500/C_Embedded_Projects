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

		.global		asmCompute				; Declare entry point as a global symbol

		.text								; Program sections

asmCompute:									; Entry point

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

;;  Compute X
;;
		PUSH {R4,R5,R6,R7}
		MOV R6,R2
		MUL R6,R1
		SDIV R6,R6,R1
		AND R6,R3
		MOV R7,R0
		MUL R7,R7
		AND R6,R7


;;  Compute Y
		MOV R4,R0
		MOV	R5,R3
		ADDS R4,R4
		SUBS R4,R5
		MOV R5,R0
		SUBS R5,R2
		ORR R4,R5



;;  Compute RESULT
		ADD R6,R4
		MOV		R0,R6
		POP {R4,R5,R6,R7}

;;
;;	Return from the subroutine with the result in R0
;;
		BX			LR				; Branch to the program address in the Link Register

		.end

