#include <stdio.h>
#include <stdlib.h>


int back[200];

/*
	.file	"mystery.c"
	.comm	num,1600,32
	.text
	.globl	add
	.type	add, @function
add:					//add function
*/
int add(int a,int b){
	return (a + b);
}	

/*
.LFB2:
	.cfi_startproc			//start add function
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
		
	movq	%rsp, %rbp		//normally sentence
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)		
	movq	%rsi, -16(%rbp)		
	movq	-16(%rbp), %rax		//first variable in %rax
	movq	-8(%rbp), %rdx		//second variable in %rdx
	addq	%rdx, %rax		//add the %rdx value in %rax
	popq	%rbp			
	.cfi_def_cfa 7, 8
	ret				//return
	.cfi_endproc			// end add function
	*/
	
int compute_fib(int a){
	/*
	.LFE2:
	.size	add, .-add
	.globl	compute_fib
	.type	compute_fib, @function
compute_fib:
*/
	int now = 0;
	
	if(back[a] == -1){
/*
.LFB3:
	.cfi_startproc			//start function	
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp		//normally sentence
	.cfi_def_cfa_register 6
	pushq	%rbx			
	subq	$40, %rsp		// - the literal "40" from the pointer
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)		//get %rdi to rbp
	movq	-40(%rbp), %rax	    	//move an data to %rax
	movq	num(,%rax,8), %rax	//move 8 times in %rax
	cmpq	$-1, %rax		//compare data in %rax to -1;
	je	.L4			// if compare to -1 true, jump to L4
	movq	-40(%rbp), %rax		
	movq	num(,%rax,8), %rax	//same as before
	jmp	.L5		//jump to L5, it may be fail when -1 = false
*/	
	if (a== 0){
/*
.L4:
	movq	$-1, -24(%rbp)
	cmpq	$0, -40(%rbp)		//let %rbp compare with 0
	jne	.L6			// go to L6 if not equal to 0
	movq	$0, -24(%rbp)		// make %rbp = 0
	jmp	.L7			// jump to L7
*/
	back[a] = 0;
	}
	
	else if(a == 1){
/*	
	.L6:
	cmpq	$1, -40(%rbp)
	jne	.L8			//jump to L8 if not equal to 1
	movq	$1, -24(%rbp)		//make %rbp = 1
	jmp	.L7			//jump to L7
*/
	back[a] = 1;
	}
	else{
/*
		.L8:
	movq	-40(%rbp), %rax
	subq	$2, %rax
	movq	%rax, %rdi
	call	compute_fib		
	movq	%rax, %rbx
	movq	-40(%rbp), %rax
	subq	$1, %rax		//it may be a recursion
	movq	%rax, %rdi		//since it calls compute again
	call	compute_fib		//and it calls it twice
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	add			//call the add function in the previous
	movq	%rax, -24(%rbp)
*/
		back[a] = compute_fib(a-2) + compute_fib(a-1);
	}
/*
	.L7:
	movq	-40(%rbp), %rax
	movq	num(,%rax,8), %rax
	cmpq	$-1, %rax		//compare to -1
	jne	.L9			//if not true, jump to L9
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, num(,%rax,8)	//same with LFB3
.L9:
	movq	-40(%rbp), %rax
	movq	num(,%rax,8), %rax	
*/
	}

	now = back[a];
	return now;
/*
	.L5:
	addq	$40, %rsp		//+ the literal "40" from the pointer
	popq	%rbx			//which get - in the before
	popq	%rbp			//return value
	.cfi_def_cfa 7, 8
	Ret				// return
	.cfi_endproc			// end the function
	.LFE3:
	.size	compute_fib, .-compute_fib
	.section	.rodata

*/
}
int main(int argc,char** argv){
/*
.LC0:
	.string	"Value:   %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc			//start the main function
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6	//normally sentence
*/
	int j;
	j = atoi(argv[1]);
	int k = 0;
	
/*
	subq	$32, %rsp		// - the literal "32" from the pointer
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	addq	$8, %rax		// + the literal "8" to %rax
	movq	(%rax), %rax
	movq	%rax, %rdi		
	call	atoi			//call atoi function with %rdi
	movl	%eax, -8(%rbp)		
	movl	$0, -4(%rbp)		//make %rbp become 0;
	jmp	.L11

*/
	while(k < 200){
/*
.L11:
	cmpl	$199, -4(%rbp)		//compare to 199
	jle	.L12			// if lower, jump to L12
	movl	-8(%rbp), %eax
	cltq
	movq	%rax, %rdi
*/
		back[k] = -1;
/*
.L12:
	movl	-4(%rbp), %eax
	cltq
	movq	$-1, num(,%rax,8)	//make some data become 1
	addl	$1, -4(%rbp)		//add 1 to %rbp lower
*/
		k= k+1;
	}
	printf("Value:%i\n",compute_fib(j));
	/*
		call	compute_fib		//call the computer function 
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax		
	call	printf			//print out the answer
*/
	return 0;
	/*
		movl	$0, %eax		//return 0;
	leave		
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc			//end the main function
*/
}

