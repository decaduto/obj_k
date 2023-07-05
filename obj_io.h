#ifndef __OBJ__IO__H
#define __OBJ__IO__H

#ifdef __aarch64__
	#define PAGE_SIZE	4096
#endif

#ifdef __i386__
	#define	PAGE_SIZE	4096
#endif

static inline void writew(uint16_t val, volatile void *addr);
static inline void writeb(uint8_t  val, volatile void *addr);
static inline void writel(uint32_t val, volatile void *addr);


#ifdef __arm__
	static inline  void writew(uint16_t val, volatile void *addr){
		asm volatile("strh %1, %0"
				: : "Q" (*(volatile uint16_t *)addr), "r" (val));
	}
	static inline void writel(uint32_t val, volatile void *addr){
		asm volatile("str %1, %0"
				: : "Qo" (*(volatile uint32_t *)addr), "r", (val));
	}
	static inline void writeb(uint8_t val, volatile void *addr){
		asm volatile("strb %1, %0"
				: : "Qo" (*(volatile uint8_t *)addr), "r" (val));
	}

#endif

#ifdef __aarch64__
	static inline void writew(uint16_t val, volatile void *addr){
		asm volatile("strh %w0, [%1]" : : "rZ" (val), "r" (addr));
	}
	static inline void writel(uint32_t val, volatile void *addr){
		asm volatile("str %w0, [%1]" : : "rZ" (val), "r" (addr));
	}
	static inline void writeb(uint8_t val, volatile void *addr){
		asm volatile("strb %w0, [%1]" : : "rZ" (val), "r" (addr));
	}
#endif


/* for x86 */

#define build_mmio_read(name, size, type, reg, barrier)		\
	static inline type name(const volatile void *addr)	\
		{ type ret; asm volatile("mov" size " %1, %0":reg (ret)	\
		: "m" (*(volatile type *)addr) barrier); return ret; }

#define build_mmio_write(name, size, type, reg, barrier)	\
	static inline void name(type val, volatile void *addr)	\
		{ asm volatile("mov" size " %0,%1": :reg (val), \
		"m" (*(volatile type *)addr) barrier); }

build_mmio_read(readb, "b", unsigned char, "=q", :"memory")
build_mmio_read(readl, "l", unsigned int, "=r",  :"memory")
build_mmio_read(readw, "w", unsigned short, "=r", :"memory")


build_mmio_write(writeb, "b", unsigned char,  "q", :"memory")
build_mmio_write(writel, "l", unsigned int,   "r", :"memory")
build_mmio_write(writew, "w", unsigned short, "r", :"memory")


/* define phys_to_virt and virt_to_phys */
#ifndef __pa
	#define __pa
#endif

#ifndef __va
	#define __va(x)		((void *)((unsigned long)(x) + PAGE_OFFSET )
#endif

#define virt_to_phys(x)		__pa(unsigned long)x);
#define phys_to_virt(x)		__va(x);

#endif



static unsigned char *dump_memory_layout(void){
	size_t count = 0;
	unsigned char *buffer = (unsigned char *)__kmalloc(PAGE_SIZE, GFP_KERNEL);

	while( count > 0 ){
		//probe_kernel_read();

	}
	return buffer;
}
