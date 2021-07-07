MODULE BlinkOkLED; 
(* task: let the Ok LED blink (on GPIO pin 16), use high level functions *)

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

	(* the stack pointer has to be set up before any procedure call happens *)
	PROCEDURE {OPENING} Entry;
	CODE
		MOV SP, 0x8000 ; setup stack pointer
	END Entry;

	PROCEDURE {CLOSING} Exit;
	BEGIN
	END Exit;

	(* simple loop to wait for some cycles *)
	PROCEDURE Wait(n: INTEGER);
	VAR i: INTEGER;
	BEGIN
		FOR i := 1 TO n DO END;
	END Wait;

	(* Select the Ok LED *)
	PROCEDURE Select;
	BEGIN
		gpio.GPFSEL[1] := {18};
	END Select;

	(* Blink the Ok LED *)
	PROCEDURE Blink;
	VAR wait: INTEGER; 
	BEGIN
		gpio.GPFSET[0] := {16};
		Wait(512*1024); 
		gpio.GPFCLR[0] := {16};
		Wait(512*1024)
	END Blink;
	
BEGIN
	Select;
	LOOP
		Blink
	END
END BlinkOkLED.

(* compile the module *)
Compiler.Compile -p=ARM BlinkOkLED.Mos

(* link the kernel *)
Linker.Link -p=RPI BlinkOkLED ~

(* disassemble the kernel *)
FoxARMInstructionSet.Disassemble kernel.img  ~
