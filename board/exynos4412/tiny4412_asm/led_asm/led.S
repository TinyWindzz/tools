.text
.globl _start

_start:
	ldr     r0, =0x110002E0		//GPM4CON Register
	ldr     r1, =0x00001111		//Configurate GPM4_0<A1>GPM4_1<A2>GPM4_2<A2>GPM4_3 output
	str     r1, [r0]

	mov     r1, #0xF0		//light All led on
	ldr     r0, =0x110002E4		//GPM4DAT Register
	str     r1, [r0]

halt_loop:
	b halt_loop
