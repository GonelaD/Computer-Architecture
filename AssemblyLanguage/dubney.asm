.main:
	@dubney

	
	movu r0,60000


	mod r1,r0,10

	mod r2,r0,100
	div r2,r2,10

	mod r3,r0,1000
	div r3,r3,100

	mod r4,r0,10000
	div r4,r4,1000

	div r5,r0,10000

	.print r0,r1,r2,r3,r4,r5

	
	add r4,r4,r5
	add r3,r3,r4
	add r2,r2,r3
	add r1,r1,r2  @r1 has sum

	.print r1

	mul r2,r1,r1
	mul r2,r2,r1  @r2 has cube

	.print r2

	cmp r2,r0
	beq .yay
	movu r2,0
	.print r2  


.yay:
	mov r2,1
	