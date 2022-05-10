/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __ASM_VDSO_PROCESSOR_H
#define __ASM_VDSO_PROCESSOR_H

#ifndef __ASSEMBLY__

#include <linux/jump_label.h>
#include <asm/barrier.h>
#include <asm/hwcap.h>

extern struct static_key_false riscv_pause_available;
static inline void cpu_relax(void)
{
	if (!static_branch_likely(&riscv_pause_available)) {
#ifdef __riscv_muldiv
		int dummy;
		/* In lieu of a halt instruction, induce a long-latency stall. */
		__asm__ __volatile__ ("div %0, %0, zero" : "=r" (dummy));
#endif
	}
	else {
		/* Encoding of the PAUSE instruction */
		__asm__ __volatile__ ("pause");
	}
	barrier();
}

#endif /* __ASSEMBLY__ */

#endif /* __ASM_VDSO_PROCESSOR_H */
