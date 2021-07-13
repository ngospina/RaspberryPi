MODULE BlinkLED; 
(* task: let the OK/ACT LED blink (on GPIO pin 16), use high level functions *)

CONST
	MMIO = 20000000H;
	GPIO = MMIO + 200000H;

VAR
	GPFSEL EXTERN GPIO +  0H : ARRAY 6 OF SET32;
	GPFSET EXTERN GPIO + 1CH : ARRAY 2 OF SET32;
	GPFCLR EXTERN GPIO + 28H : ARRAY 2 OF SET32;

	(* simple loop to wait for some cycles *)
	PROCEDURE Wait(n: INTEGER);
	VAR i: INTEGER;
	BEGIN
		FOR i := 1 TO n DO END;
	END Wait;

	(* Blink the OK/ACT LED *)
	PROCEDURE Blink*;
	VAR wait: INTEGER; 
	BEGIN
		GPFSET[0] := {16};
		Wait(512*1024); 
		GPFCLR[0] := {16};
		Wait(512*1024)
	END Blink;
	
BEGIN
	(* Select the OK/ACT LED *)
	GPFSEL[1] := {18};
END BlinkLED.

(* compile the module *)
Compiler.Compile -p=ARM BlinkLED.Mod
