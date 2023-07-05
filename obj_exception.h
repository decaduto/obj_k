/* this must be included BEFORE obj_internal.h */

struct exception_table_entry{
	int insn;
	int fixup;
	#ifdef __x86__
	int handler;
	#endif
}__attribute__((aligned(4)));

__attribute__((optimize("Os"))) static inline struct exception_table_entry *search_exception_table(struct exception_table_entry *e, size_t num, long value){
	const char *pivot = NULL;
	int result = 0;
	/* define our searching function here */
	auto int compare_extable_entries(const void *, const void *);
	__attribute__((optimize("Os"))) int compare_extable_entries(const void *key, const void *elt){
		const struct exception_table_entry *_elt = elt;
		unsigned long _key = *(unsigned long *)key;
		/* avoid overflow */
		if( _key > _elt->insn ){
			return 1;
		}
		if( _key < _elt->insn ){
			return -1;
		}
		return 0;
	}
	while(num > 0 ){
		pivot = (const char *)e + (num >> 1 ) * sizeof(struct exception_table_entry);
		result = compare_extable_entries(&value, pivot);
		if( result == 0 ){
			return (struct exception_table_entry *)pivot;
		}
		if( result > 0 ){
			e = pivot + sizeof(struct exception_table_entry);
			num--;
		}
		num >>= 1;
	}
	return (struct exception_table_entry *)NULL;
}
