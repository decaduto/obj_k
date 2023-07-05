#include <stdint.h>
#include <stddef.h>

struct resource{
	uint32_t	start;
	uint32_t 	end;
	const char 	*name;
	unsigned long 	flags;
	unsigned long 	desc;
	struct resource	*parent, *sibling, *child;
};


static struct resource *next_resource(struct resource *p, int skip_children){
	if( skip_children > 0 ){
		if( p->child ){
			return p->child;
		}
	}
	while ( !p->sibling && p->parent )
		p = p->parent;
	return p->sibling;
}

extern struct resource ioport_resource;
extern struct resource iomem_resource;

/* define macros and functions for iterating the linked list */
#define for_each_resource(_root, _p, _skip_children)	\
	for( (_p) = (_root)->child; (_p);		\
	(_p) = (_skip_children) ? next_resource(_p, 1) :	\
		next_resource(_p, 0))


static inline short localize_specific_resource(const char *resource_name, short (*cb)(struct resource *res)){
	if( resource_name == NULL || strlen(resource_name) < 2 || cb == NULL ){
		return -1;
	}
	struct resource *rs = NULL;
	for_each_resource(&ioport_resource, rs, 1){
		for(int j = 0; j < strlen(resource_name); j++){
			if(	rs->name[j]   == resource_name[j]   &&
				rs->name[j+1] == resource_name[j+1] &&
				rs->name[j+2] == resource_name[j+2] &&
				rs->name[j+3] == resource_name[j+3] &&
				rs->name[j+4] == resource_name[j+4] ){
					short (*static_cb)(struct resource *s);
					short res = static_cb(rs);
					return res;
				}
		}
	}
	return -1;
}
