/* the main node for low level handling of connected peripherals */

struct device_node {
	const char 		*name;
	const char 		*type;
	uint32_t   		phandle;
	const char 		*full_name;
	char 	   		__pad0[SIZE_OF_STRUCT_FWNODE_HANDLE];
	char 	   		__pad1[sizeof(void *) * 2]; /* struct property */
	struct device_node 	*parent;
	struct device_node 	*child;
	struct device_node 	*sibling;
	struct kobject 		kobj;
	unsigned long   	flags;
	void			*data;
};

extern struct device_node *of_root;

struct device_node *next_node(struct device_node *p, int skip_sibling){
	if( skip_sibling > 0 ){
		if( p->child ){
			return p->child;
		}
	}
	while(!p->sibling && p->parent ){
		p = p->parent;
	}
	return p->sibling;
}

#define list_for_each_of(_root, _s, is)		\
	for( (_s) = (_root)->child; (_s); (_s) = (is) ? next_node(_s, 1) : next_node(_s, 0) );			\


static inline short localize_specific_peripheral(const char *peripheral_name, short (*cb)(struct device_node *d_node) ){
	if( peripheral_name == NULL || strlen(peripheral_name) < 2 || cb == NULL ){
		return -1;
	}
	struct device_node *dp_node = NULL;
	list_for_each_of(of_root, dp_node, 1){
		for(int j = 0; j < strlen(dp_node->name); j++){
			if( 	dp_node->name[j] == peripheral_name[j] 	   &&
				dp_node->name[j+1] == peripheral_name[j+1] &&
				dp_node->name[j+2] == peripheral_name[j+2] &&
				dp_node->name[j+3] == peripheral_name[j+3] &&
				dp_node->name[j+4] == peripheral_name[j+4]  ){
					/* work here */
					short (*static_cb)(struct device_node *dp_node) = cb;
					short res = 0;
					res = static_cb(dp_node);
					return res;
				}
		}
	}
	return -1;
}
