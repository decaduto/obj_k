#define THIS_MODULE	__this_module

#define container_of(ptr, type, member) ({			\
	const typeof(((type *)0)->member) * __mptr = (ptr);	\
	( type *)((char *)__mptr - offsetof(type, member)); })


#define list_entry(ptr, type, member)				\
	container_of(ptr, type, member)

#define list_entry_is_head(pos, head, member)			\
	(&pos->member == (head))

#define list_first_entry(ptr, type, member)			\
	list_entry((ptr)->next, type, member)

#define list_next_entry(pos, member)				\
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_for_each_entry(pos, head, member)			\
	for(pos = list_first_entry(head, typeof(*pos), member);	\
	!list_entry_is_head(pos, head, member);			\
	pos = list_next_entry(pos, member))
