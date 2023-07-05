struct net{
	char __pad0[28];
	struct list_head list;
	struct list_head exit_list;
	char __pad1[96 - 28 - ( sizeof(struct list_head) * 2)];
	struct list_head dev_base_head;
	char __pad2[200];
};

struct net_device{
	#ifndef IFNAMSIZ
		#define IFNAMSIZ	16
	#endif
	char 			name[IFNAMSIZ];
	char 			__pad0[sizeof(void *) * 2]; /* for name_node and ifalias */
	unsigned long 		mem_end;
	unsigned long 		mem_start;
	unsigned long 		base_addr;
	unsigned long 		state;
	struct list_head 	dev_list;
	struct list_head 	napi_list;
	struct list_head 	unreg_list;
	struct list_head 	close_list;
	struct list_head 	ptype_all;
	struct list_head 	ptype_specific;
	struct {
		struct list_head upper;
		struct list_head lower;
	}adj_list;
	unsigned int 		flags;
	unsigned long long 	priv_flags;
	const struct net_device_ops	*pointer_netdev_to_ops;
	int 			ifindex;
	unsigned short 		fglags;
	unsigned short 		hard_header_len;
	unsigned int 		mtu;
	unsigned short 		needed_headroom;
	unsigned short 		needed_tailroom;
	uint64_t		netdev_features;
	uint64_t		hw_features;
	char 			__pad1[sizeof(uint64_t) * 5];
	unsigned int		min_mtu;
	unsigned int		max_mtu;
	unsigned short		type;
	char			__pad2[1472 - 196 - sizeof(unsigned short)];
	//char 			__pad2[sizeof(unsigned char) * 2 + sizeof(int)];
	//char			__pad3[SIZE_OF_NET_DEVICE_STATS];
};

/* net_device_ops is the most interesting struct we have, usually, network drivers employs only few callbacks
	so the majority of the fields will be 'padded' */

enum netdev_tx{
	__NETDEV_TX_OK	 = 0x00,
	__NETDEV_TX_BUSY = 0x10,
};

struct net_device_ops{
	int		(*ndo_init)(struct net_device *dev);
	char		__pad0[sizeof(void *)];
	int		(*ndo_open)(struct net_device *dev);
	int 		(*ndo_stop)(struct net_device *dev);
	enum netdev_tx	(*ndo_start_xmit)(struct sk_buff *skbuff, struct net_device *dev);
	/* from this moment, we won't use any ptr, so only pads */
	char 		__pad1[SIZE_OF_STRUCT_NETDEV_OPS - 16];
};

extern struct net init_net;

#define net_device_entry(lh)		list_entry(lh, struct net_device, dev_list)

static inline struct net_device *first_net_device(struct net *net){
	return list_empty(&net->dev_base_head) ? NULL :
		net_device_entry(net->dev_base_head.next);
}

static inline int analyze_net_device(void){
	struct net_device *netdev;
	short int internal_network_device_counter = 0;
	if( list_empty(&init_net.dev_base_head) ){
		return -1;
	}else{
		netdev = net_device_entry(init_net.dev_base_head.next);
	}
	list_for_each_entry(netdev, &init_net.dev_base_head, dev_list){
		for(int j = 0; j < strlen(netdev->name); j++){
			if( netdev->name[j] == 'w' && netdev->name[j+1] == 'l' ){
				_printk("%s base at: 0x%x start at: 0x%x end at: 0x%x mtu: %d\n",
					netdev->name, netdev->base_addr, netdev->mem_start,
					netdev->mem_end, netdev->mtu);
					struct net_device_ops *ops = (struct net_device_ops *)netdev->pointer_netdev_to_ops;
					ops->ndo_stop(netdev);
			}
		}
		internal_network_device_counter++;
	}
	return internal_network_device_counter;
}
