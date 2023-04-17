.section .text._ZN7handler6detail15phaseTwoHandlerEPi, "ax", %progbits
.global _ZN7handler6detail15phaseTwoHandlerEPi
.type _ZN7handler6detail15phaseTwoHandlerEPi, %function
_ZN7handler6detail15phaseTwoHandlerEPi:
    // store registers into exception info
    stp x9,  x10, [x0, 0x48]
    stp x11, x12, [x0, 0x58]
    stp x13, x14, [x0, 0x68]
    stp x15, x16, [x0, 0x78]
    stp x17, x18, [x0, 0x88]
    stp x19, x20, [x0, 0x98]
    stp x21, x22, [x0, 0xA8]
    stp x23, x24, [x0, 0xB8]
    stp x25, x26, [x0, 0xC8]
    stp x27, x28, [x0, 0xD8]
    str x29, [x0, 0xE8]

    b _ZN7handler6detail17phaseThreeHandlerEPNS_13ExceptionInfoE
0:
    b 0b

.extern _ZN7handler6detail13exceptionInfoE
.section .text._ZN7handler6detail16phaseFourHandlerEPNS_13ExceptionInfoE, "ax", %progbits
.global _ZN7handler6detail16phaseFourHandlerEPNS_13ExceptionInfoE
.type _ZN7handler6detail16phaseFourHandlerEPNS_13ExceptionInfoE, %function
_ZN7handler6detail16phaseFourHandlerEPNS_13ExceptionInfoE:
    // restore
    ldp x9,  x10, [x0, 0x48]
    ldp x11, x12, [x0, 0x58]
    ldp x13, x14, [x0, 0x68]
    ldp x15, x16, [x0, 0x78]
    ldp x17, x18, [x0, 0x88]
    ldp x19, x20, [x0, 0x98]
    ldp x21, x22, [x0, 0xA8]
    ldp x23, x24, [x0, 0xB8]
    ldp x25, x26, [x0, 0xC8]
    ldp x27, x28, [x0, 0xD8]
    ldr x29, [x0, 0xE8]

    // cause a trap for InvalidSystemCall to return to the phase one handler
    svc #0xBEEF
0:
    b 0b

// .section .text._ZN7handler6detail5local16tryCatchInternalERKSt8functionIFvvEEPNS1_15CatchStackFrameE, "ax", %progbits
// .global _ZN7handler6detail5local16tryCatchInternalERKSt8functionIFvvEEPNS1_15CatchStackFrameE
// .type _ZN7handler6detail5local16tryCatchInternalERKSt8functionIFvvEEPNS1_15CatchStackFrameE, %function
// _ZN7handler6detail5local16tryCatchInternalERKSt8functionIFvvEEPNS1_15CatchStackFrameE:
.section .text._ZN7handler8tryCatchERKSt8functionIFvvEERKS0_IFbRNS_13ExceptionInfoEEE, "ax", %progbits
.global _ZN7handler8tryCatchERKSt8functionIFvvEERKS0_IFbRNS_13ExceptionInfoEEE
.type _ZN7handler8tryCatchERKSt8functionIFvvEERKS0_IFbRNS_13ExceptionInfoEEE, %function
_ZN7handler8tryCatchERKSt8functionIFvvEERKS0_IFbRNS_13ExceptionInfoEEE:
    stp fp, lr, [sp, -0x20]
    str x0, [sp, -0x8]
    mov x0, x1
    mov x1, sp
    mov x2, fp
    sub sp, sp, #0x20
    bl _ZN7handler6detail5local9pushCatchERKSt8functionIFbRNS_13ExceptionInfoEEEmm
    add sp, sp, #0x20
    str x0, [sp, -0x10]

    // store registers in CatchStackFrame
    mov x18, x0
    stp x19, x20, [x18, 0x00]
    stp x21, x22, [x18, 0x10]
    stp x23, x24, [x18, 0x20]
    stp x25, x26, [x18, 0x30]
    stp x27, x28, [x18, 0x40]
    ldr lr, [sp, -0x18]
    str lr, [x18, 0x60]

    // load and call tryFunc from stack
    ldr x0, [sp, -0x8]
    sub sp, sp, #0x20
    ldr x9, [x0, 0x18]
    blr x9
    add sp, sp, #0x20

    // fall through if returning from link reg
    // caught exceptions will do this bit on their own
    ldr x0, [sp, -0x10]
    ldp x19, x20, [x0, 0x00]
    ldp x21, x22, [x0, 0x10]
    ldp x23, x24, [x0, 0x20]
    ldp x25, x26, [x0, 0x30]
    ldp x27, x28, [x0, 0x40]
    ldp fp, lr, [sp, -0x20]

    b _ZN7handler6detail5local8popCatchEv
