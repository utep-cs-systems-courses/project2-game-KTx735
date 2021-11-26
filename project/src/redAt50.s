	.arch msp430g2553
	.p2align 1,0
	.text

	.extern red_on
	.global redAt50()
redAt50:
	sub #2, R1
	mov #0, 1(R1)
	cmp #0, 1(R1)
	jne second
	mov #1, &red_on
	mov #1, 1(R1)
second:
	cmp #1, 1(R1)
	jne out
	mov #0, &red_on
	mov #0, 1(R1)
out:
	call #led_update
	add #2, R1
	pop R0
