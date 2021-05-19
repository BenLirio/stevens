.LC1:
	.string	"PI: %f\n"
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	.LC0(%rip), %rax
	movq	%rax, %xmm0
	leaq	.LC1(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
.LC0:
	.long	1374389535
	.long	1074339512
