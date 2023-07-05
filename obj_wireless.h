int wiphy_register(struct wiphy *wiphy);
int device_add(struct device *);

struct cfg80211_registered_device{
	const struct cfg80211_ops *ops;
	struct list_head list;
	char __pad0[1280 - sizeof(void *) - sizeof(struct list_head)];
};

static inline struct cfg80211_registered_device *cfg80211_iterate(void){
	/* obtain the pointer of cfg80211_rdev_list */
	void *ptr_to_wiphy_register = &wiphy_register;
	void *ptr_to_device_add     = &device_add;
	struct cfg80211_registered_device *p = NULL;
	void *ptr = (void *)memremap((volatile void *)ptr_to_wiphy_register, 120, 1 << 1);
	_printk("0x%x\n", ptr);
	/*list_for_each_entry(p, &cfg80211_rdev_list, list){
		if( p->ops != NULL ){
			return p;
		}
	}*/
	return NULL;
}
