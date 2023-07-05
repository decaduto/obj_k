extern struct kobject *kernel_kobj;


struct kobject{
	char 		 	*name;
	struct list_head 	entry;
	struct kobject   	*parent;
	struct kset	 	*kset;
	struct kobj_type 	*ktype;
	struct kernfs_node	*sd;
	char   			__pad0[12 - 4];
	//char __pad0[(sizeof(void *) * 3 ) + 4 + sizeof(unsigned int) * 5];
	/* where '4' is the size of 'struct kref' */
};

struct kset{
	struct list_head list;
	char __pad0[SIZE_OF_STRUCT_SPINLOCK];
	struct kobject kobj;
	char __pad1[sizeof(const void *)];
};

struct klist{
	char __pad0[SIZE_OF_STRUCT_SPINLOCK]; /* sizeof of spinlock_t */
	struct list_head k_list;
	void	(*get)(void *);
	void    (*put)(void *);
}__attribute__((aligned(sizeof(void *))));
