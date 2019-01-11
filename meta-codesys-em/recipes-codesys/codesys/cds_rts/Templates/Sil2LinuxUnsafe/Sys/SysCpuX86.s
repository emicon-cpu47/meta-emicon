/* SysCpuHandling for X86
 */

/* exports */
.globl SysCpuCallIecFuncWithParams
.globl _SysCpuCallIecFuncWithParams
.globl syscpudebughandler
.globl _syscpudebughandler

/* imports */
.globl AppDebugHandler

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

	/* align size up */
	add    $0x3, %ecx
	and    $0xfffffffc,%ecx

	mov    $0, %edx
param_store_loop:
	/* counter >= size? */
	cmp    %ecx, %edx
	jge    after_store_loop
	mov    (%edi), %esi
	mov    %esi, (%ebx)
	add    $0x4, %edx
	add    $0x4, %ebx
	add    $0x4, %edi
	jmp    param_store_loop
after_store_loop:

	/* free buffer on the stack */
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

