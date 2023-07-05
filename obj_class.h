/*
	this header contains every 'struct class' invokation
*/

struct class{
	const char 		*class_name;
	struct module		*owner;
	char			__pad0[sizeof(const void **) * 2];
	struct kobject		*kobj;
	char			__pad1[sizeof(void *) * 5];
	char			__pad2[sizeof(const void *)];
	char			__pad3[sizeof(const void *)];
	char			__pad4[sizeof(const void *)];
	char			__pad5[sizeof(const void *)];
	struct subsys_private	*p;

};

extern struct class input_class;
