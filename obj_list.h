struct list_head{
	struct list_head *next, *prev;
};

struct hlist_node{
	struct hlist_node *next, **prev;
};

#ifndef LIST_POISON1
	#define LIST_POISON1	((void *)0x100)
	#define LIST_POISON2	((void *)0x122)
#endif

static void __write_once_size(volatile void *p, void *res, int size){
		switch(size){
			case 1:
				*(volatile uint8_t  *)p = *(uint8_t  *)res;
				break;
			case 2:
				*(volatile uint16_t *)p = *(uint16_t *)res;
				break;
			case 4:
				*(volatile uint32_t *)p = *(uint32_t *)res;
				break;
			case 8:
				*(volatile uint64_t *)p = *(uint64_t *)res;
				break;
			default:
				#ifndef barrier
					#define barrier()	\
						__asm__ __volatile__("": : :"memory")
				#endif
				barrier();
				memcpy((void *)p, (const void *)res, size);
				barrier();
		}
}

static void __read_once_size(const volatile void *p, void *res, int size){
	switch(size){
		case 1:
			*(uint8_t *)	res = *(volatile uint8_t  *)p;
			break;
		case 2:
			*(uint16_t *)	res = *(volatile uint16_t *)p;
			break;
		case 4:
			*(uint32_t *)	res = *(volatile uint32_t *)p;
			break;
		case 8:
			*(uint64_t *)	res = *(volatile uint64_t *)p;
			break;
		default:
			#ifndef barrier
				#define barrier()	\
					__asm__ __volatile__("": : :"memory")
			#endif
			barrier();
			memcpy((void *)res, (const void *)p, size);
			barrier();
		}
}

#ifndef WRITE_ONCE
	#define WRITE_ONCE(x, val) ({					\
			union { typeof(x) __val; char __c[1]; } __u =	\
				{ .__val = (val) };			\
			__write_once_size(&(x), __u.__c, sizeof(x));	\
			__u.__val;					\
})

#endif

#ifndef READ_ONCE
	#define READ_ONCE(x)	({					\
			union { typeof(x) __val; char __c[1]; } __u =   \
				{ .__c = { 0 } };			\
			__read_once_size(&(x), __u.__c, sizeof(x));	\
			__u.__val;					\
		})
#endif

#define list_entry_rcu(ptr, type, member)	\
	container_of(READ_ONCE(ptr), type, member)

static inline void __list_del(struct list_head *prev, struct list_head *next){
	next->prev = prev;
	WRITE_ONCE(prev->next, next);
}

static inline void __list_delete(struct list_head *list){
	__list_del(list->prev, list->next);
	list->next = LIST_POISON1;
	list->prev = LIST_POISON2;
}

static inline int list_empty(struct list_head *head){
	return READ_ONCE(head->next) == head;
}
