struct kprobe{
	struct hlist_node	hlist;
	struct list_head	list;
	unsigned long 		nmissed;
	#ifdef	__i386__
	uint8_t			kprobe_addr;
	#else if defined(__aarch64__)
	uint32_t		krobe_addr;
	#endif
	const char 		*symbol_name;
	int (*kprobe_pre_handler)(struct kprobe *, struct pt_regs *);
	int (*kprobe_post_handler)(struct kprobe *, struct pt_regs *, unsigned long flags);
	int (*kprobe_fault_handler)(struct kprobe *, struct pt_regs *, int trapnr);
	int (*kprobe_break_handler)(struct kprobe *, struct pt_regs *);
	#ifdef	__i386__
	uint8_t			kprobe_opcode;
	#else if defined(__aarch64__)
	uint32_t		kprobe_opcode;
	#endif
	/* other here is garbage, not interesting for us */
};

extern int register_kprobe(struct kprobe *);
extern void unregister_kprobe(struct kprobe *);
