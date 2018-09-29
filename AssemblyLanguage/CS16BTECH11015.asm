.main:
	movu r0,125


	mod r1,r0,10

	mod r2,r0,100
	div r2,r2,10

	mod r3,r0,1000
	div r3,r3,100

	mod r4,r0,10000
	div r4,r4,1000

	div r5,r0,10000


	cmp r5,0
	bgt .fact5
	cmp r4,0
	bgt .fact4
	cmp r3,0
	bgt .fact3
	cmp r2,0
	bgt .fact2
	cmp r1,0
	bgt .fact1


	mov r1,0
	.print r1

	b .dubey	
	
.fact5:
		mov r8,1
		mov r9,r5   @r5 factorial
		call .loop
		mov r5,r8
		b .fact4
	

.fact1:
		@.print r0,r1,r2,r3,r4,r5
		mov r8,1
		mov r9,r1  
		call .loop
		mov r1,r8 @r1 factorial

		add r4,r4,r5
		add r3,r3,r4
		add r2,r2,r3
		add r1,r1,r2  @r1 has sum


		cmp r1,r0
		beq .eq
		mov r1,0
		.print r1
		b .dubey
		b .end


.eq:
	mov r1,1
	.print r1
	b .dubey
	b .end

.fact2:
		mov r8,1
		mov r9,r2  
		call .loop
		mov r2,r8   @r2 factorial
		b .fact1

.fact3:	
		mov r8,1
		mov r9,r3  @r3 factorial
		call .loop
		mov r3,r8
		b .fact2


.fact4:

		mov r8,1
		mov r9,r4  @r4 factorial
		call .loop
		mov r4,r8
		b .fact3

.glabel:
		mul r8,r8,r9
		sub r9,r9,1
		cmp r9,0
		bgt .loop

	
.loop:
	cmp r9,0
	bgt .glabel
	ret

.dubey:
	mod r1,r0,10

	mod r2,r0,100
	div r2,r2,10

	mod r3,r0,1000
	div r3,r3,100

	mod r4,r0,10000
	div r4,r4,1000

	div r5,r0,10000



	
	add r4,r4,r5
	add r3,r3,r4
	add r2,r2,r3
	add r1,r1,r2  @r1 has sum


	mul r2,r1,r1
	mul r2,r2,r1  @r2 has cube



	cmp r2,r0
	beq .yay
	movu r2,0
	.print r2 

	b .end 


.yay:
	mov r2,1
	.print r2
	b .end


.end:
		
		



	
	


