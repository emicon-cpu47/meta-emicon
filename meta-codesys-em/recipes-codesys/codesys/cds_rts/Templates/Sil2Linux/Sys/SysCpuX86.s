/* SysCpuHandling for X86
 */

/* exports */
.globl SysCpuCallIecFuncWithParams
.globl _SysCpuCallIecFuncWithParams
.globl syscpudebughandler
.globl _syscpudebughandler

/* imports */
.globl AppDebugHandler
.globl SIL2OEMGetOperationMode
.globl SysExceptGenerateException

/**
 * RTS_RESULT CDECL SysCpuCallIecFuncWithParams(void* pfIECFunc, void* pParam, int iSize);
 */
_SysCpuCallIecFuncWithParams:
SysCpuCallIecFuncWithParams:
	/* 0x08(esp) -> eax : pfIECFunc */
	/* 0x0c(esp) -> ebx : pParam */
	/* 0x10(esp) -> ecx : iSize (4 byte aligned) */
	/* edx : counter */
	/* esi : helper */
	/* edi : base of the local buffer */

	/* stack frame */
	push   %ebp
	mov    %esp, %ebp

	/* save globbered registers */
	push %ebx
	push %ecx
	push %edx
	push %esi
	push %edi

	/* move parameters to local registers */
	mov    0x08(%ebp), %eax 
	mov    0x0c(%ebp), %ebx
	mov    0x10(%ebp), %ecx

	/* Check parameters */
	/* pfIECFunc == NULL? */
	cmp    $0, %eax
	je     return_error

	/* pParam == NULL? */
	cmp    $0, %ebx
	jne    params_ok

	/* iSize > 0? */
	cmp    $0, %ecx
	je     params_ok

	jmp    return_error
params_ok:

	/* Check if pfIECFunc points to the beginning of a stackframe */
	mov    0x00(%eax), %bl
	mov    $0x55, %cl
	cmp    %bl, %cl
	jne    return_ok

	mov    0x08(%ebp), %eax 
	mov    0x0c(%ebp), %ebx
	mov    0x10(%ebp), %ecx

	
	/* align size up */
	add    $0x3, %ecx
	and    $0xfffffffc,%ecx

	/* reserve buffer on the stack */
	subl   %ecx, %esp
	mov    %esp, %edi

	mov    $0, %edx
param_load_loop:
	/* counter >= size? */
	cmp    %ecx, %edx
	jge    after_load_loop
	mov    (%ebx), %esi
	mov    %esi, (%edi)
	add    $0x4, %edx
	add    $0x4, %ebx
	add    $0x4, %edi
	jmp    param_load_loop
after_load_loop:
	mov    %esp, %edi

	/**
	 * Under normal circumstances we would like to pass the parameter %edi
	 * to the function, using the CDECL calling convention. But our code-
	 * generator doesn't await this parameter, but takes the buffer directly
	 * from the stack.
	 */
	/* CDECL Parameter Passing:
	 * subl   $0x4, %esp
	 * mov    %edi, (%esp)
	 */
	 call   *%eax

	/* CDECL Cleanup:
	 * addl   $0x4, %esp
	 */

	/* reload parameters to local registers (may be modified in the call) */
	mov    0x08(%ebp), %eax 
	mov    0x0c(%ebp), %ebx
	mov    0x10(%ebp), %ecx
	mov    $0, %edx

	/* align size down for 4-byte copy */
	and    $0xfffffffc,%ecx

	mov    $0, %edx
param_store_loop:
	/* counter >= size? */
	cmp    %ecx, %edx
	jge    after_dword_store_loop
	mov    (%edi), %esi
	mov    %esi, (%ebx)
	add    $0x4, %edx
	add    $0x4, %ebx
	add    $0x4, %edi
	jmp    param_store_loop

after_dword_store_loop:
	/* get original iSize for byte copy*/
	mov    0x10(%ebp), %ecx

byte_store_loop:
	/* counter >= size? */
	cmp    %ecx, %edx
	jge    after_byte_store_loop
	movb    (%edi), %al
	movb    %al, (%ebx)
	add    $0x1, %edx
	add    $0x1, %ebx
	add    $0x1, %edi
	jmp    byte_store_loop

after_byte_store_loop:

	/* free buffer on the stack */
	add    $0x3, %ecx
	and    $0xfffffffc,%ecx
	addl   %ecx, %esp

	/* ERR_OK */
	mov $0, %eax
	jmp return_ok

return_error:
	/* ERR_PARAMETER */
	mov $2, %eax
return_ok:

	/* restore globbered registers */
	pop %edi
	pop %esi
	pop %edx
	pop %ecx
	pop %ebx

	/* stack frame */
	leave
	ret    

	/* mark this as a function and calculate the size of it */
	.type	_SysCpuCallIecFuncWithParams,@function
	.size	_SysCpuCallIecFuncWithParams, . - _SysCpuCallIecFuncWithParams
	.type	SysCpuCallIecFuncWithParams,@function
	.size	SysCpuCallIecFuncWithParams, . - SysCpuCallIecFuncWithParams

/**
 * void CDECL CDECL_EXT syscpudebughandler(void);
 *
 * <description>
 *	<p>Routine is the entry of the IEC code debugger. Is called out of the IEC task if breakpoint is reached.</p>
 *	<p>IMPLEMENTATION NOTE: In this routine, the AppDebugHandler() function of CmpApp must be called with
 *	the appropriate parameters. See CmpAppItf.h for detailed information. The return value of
 *	AppDebugHandler() must be used to set the return address in the IEC code. To this address we will return
 *	when leaving syscpudebughandler().</p>
 * </description>
 * <return>no return value</return>
 */
syscpudebughandler:
_syscpudebughandler:
	/* Setup the stack frame */
	pushl %ebp			
	movl  %esp, %ebp
	
	/* push everything (including floating point registers) on the stack*/
	pusha
	pushf

	/* check current operation mode */
	call SIL2OEMGetOperationMode
	/* opmode == safe? */
	cmp $0xAABB, %eax
	jne syscpudebughandler_continue
	/* safe context => throw exception */
	/* third param: {0,0,0} on stack */
	movl $0, %edx
	pushl %edx
	pushl %edx
	pushl %edx
	/* second param: {0,RTSEXCPT_UNKNOWN} */
	movl $0, %edx
	pushl %edx
	movl $-1, %edx
	pushl %edx
	/* first param: RTS_INVALID_HANDLE */
	movl $-1, %edx
	pushl %edx
	call SysExceptGenerateException
	popl %edx
	popl %edx
	popl %edx
	popl %edx
	popl %edx
	popl %edx
	jmp syscpudebughandler_end
		

syscpudebughandler_continue:
	/* load old ebp */
	movl (%ebp), %eax
	pushl %eax /* parameter 3, EBP */
	movl %ebp, %eax
	addl $8, %eax
	pushl %eax /* parameter 2, ESP */

	/* load current instruction address */
	movl 4(%ebp), %eax
	subl $5, %eax
	pushl %eax /* parameter 1, EIP */

	/* Call to AppDebugHandler */
	call AppDebugHandler

	/* remove parameters from stack */
	addl $12, %esp
	
	/* new return address is passed by AppDebugHandler!*/
	movl %eax, 4(%ebp)
syscpudebughandler_end:
	/* Restore all registers */
	popf
	popa
	popl %ebp
	ret

	/* mark this as a function and calculate the size of it */
	.type	_syscpudebughandler,@function
	.size	_syscpudebughandler, . - _syscpudebughandler
	.type	syscpudebughandler,@function
	.size	syscpudebughandler, . - syscpudebughandler
