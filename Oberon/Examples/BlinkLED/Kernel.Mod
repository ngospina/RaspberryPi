MODULE Kernel; 
(* task: let the LED blink *)

IMPORT SYSTEM, BlinkLED;

	(* the stack pointer has to be set up before any procedure call happens *)
	PROCEDURE {OPENING} Entry;
	CODE
		MOV SP, 0x8000 ; setup stack pointer
	END Entry;

	PROCEDURE {CLOSING} Exit;
	BEGIN
	END Exit;

BEGIN
	LOOP
		BlinkLED.Blink
	END
END Kernel.

(* compile the module *)
Compiler.Compile -p=ARM Kernel.Mod

(* link the kernel *)
Linker.Link -p=RPI Kernel ~

(* disassemble the kernel *)
FoxARMInstructionSet.Disassemble kernel.img  ~
