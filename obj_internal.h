#define MODULE_NAME	"test"

enum module_state{
	MODULE_STATE_LIVE,
	MODULE_STATE_COMING,
	MODULE_STATE_GOING,
	MODULE_STATE_UNFORMED,
};

struct module_kobject{
	struct kobject kobj;
	struct module  *mod;
	struct kobject *drivers_dir;
	char           __pad0[sizeof(void *)];
	char	       __pad1[sizeof(void *)];
};

struct rb_node{
	unsigned long item1;
	char __pad0[sizeof(void *) * 2];
}__attribute__((aligned(sizeof(long))));

struct latch_tree_node {
	struct rb_node	node[2];
};

struct mod_tree_node{
	char __pad0[sizeof(void *)];
	struct latch_tree_node node;
};

struct module_layout{
	void *base;
	unsigned int size;
	unsigned int text_size;
	unsigned int ro_size;
	unsigned int ro_after_init_size;
	struct mod_tree_node mtn;
};

struct module{
	enum   module_state state;
	struct list_head list;
	char name[sizeof(MODULE_NAME)];
	//struct module_kobject	mkobj;
	char __pad0[204 - ( sizeof(enum module_state) + sizeof(struct list_head) ) - sizeof(MODULE_NAME) - ( sizeof(unsigned int) + sizeof(struct exception_table_entry *))];
	unsigned int num_exentries;
	struct exception_table_entry *extable;
	void *init;
	struct module_layout core_layout;
	struct module_layout init_layout;
	char __pad1[500 - 204 - sizeof(void *) - sizeof(struct module_layout) * 2];
	void *exit;
	char __pad2[512 - 500 - sizeof(void *)];
}__attribute__((packed));

extern struct module __this_module;
