MODULE BlinkLED; 
(* task: let the OK/ACT LED blink (on GPIO pin 16), use high level functions *)

IMPORT SYSTEM;

CONST
	GPIO = 020200000H;

VAR
	gpio* EXTERN GPIO: RECORD (* pinned to GPIO address *)
		GPFSEL: ARRAY 6 OF SET32;
		res0: SET32;
		GPFSET: ARRAY 2 OF SET32;
		res1: SET32;
		GPFCLR: ARRAY 2 OF SET32;
	END;

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
		gpio.GPFSET[0] := {16};
		Wait(512*1024); 
		gpio.GPFCLR[0] := {16};
		Wait(512*1024)
	END Blink;
	
BEGIN
	(* Select the OK/ACT LED *)
	gpio.GPFSEL[1] := {18};
END BlinkLED.

(* compile the module *)
Compiler.Compile -p=ARM BlinkLED.Mod
