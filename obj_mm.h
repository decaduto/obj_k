#define __force		__attribute__((force))
#define __io_virt(x)	((void __force *)x)

typedef unsigned int gfp_t;
#define __GFP_FS	(gfp_t)0x80u
#define __GFP_IO	(gfp_t)0x40u

#define ___GFP_DIRECT_RECLAIM	0x400u
#define ___GFP_KSWAPD_RECLAIM	0x800u

#define __GFP_RECLAIM	(gfp_t)(___GFP_DIRECT_RECLAIM | ___GFP_KSWAPD_RECLAIM)
#define GFP_KERNEL	(__GFP_RECLAIM | __GFP_IO | __GFP_FS)

struct vma_area_struct{
	unsigned long vm_start;
	unsigned long vm_end;
	struct vm_area_struct *vm_next, *vm_prev;
	/* the other fields are irrelevant */
};

extern void *__vmalloc(unsigned long size, gfp_t mask);
extern void *vmalloc(unsigned long size);
