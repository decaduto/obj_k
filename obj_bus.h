struct bus_type{
	const char 	*name;
	const char 	*dev_name;
	struct device 	*dev_root;
	char __pad0[sizeof(void **)  * 3];
	char __pad1[sizeof(void * )  * 12]; /* 13 */
	char __pad2[sizeof(const void *) * 2];
	struct subsys_private *p; /* the struct subsys_private contains the list to iterate */
	char __pad3[1];
};

struct subsys_private{
	struct kset subsys;
	struct kset *device_kset;
	struct list_head interfaces;
	char   __pad0[SIZE_OF_STRUCT_MUTEX]; /* sizeof of mutex */
	struct kset *drivers_kset;
	struct klist klist_devices;
	struct klist klist_drivers;
	char   __pad1[SIZE_OF_STRUCT_BLOCKING_NOTIFIER_HEAD]; /* sizeof of blocking_notifier_head */
	unsigned int drivers_autoprobe : 1;
	struct bus_type *bus;
	struct kset glue_dirs;
	struct class *class;
};

enum bus_nmbr{
	BUS_TYPE_USB,
	BUS_TYPE_PCI,
	BUS_TYPE_SERIO,
	BUS_TYPE_I2C,
	BUS_TYPE_PLATFORM,
	/*
	BUS_TYPE_AMBA,
	BUS_TYPE_CORESIGHT,
	BUS_TYPE_CPU,
	BUS_TYPE_EISA,
	BUS_TYPE_IIO,
	BUS_TYPE_SPI,*/
};

extern struct bus_type 	serio_bus;
extern struct bus_type	pci_bus_type;
extern struct bus_type	usb_bus_type;
extern struct bus_type	i2c_bus_type;
extern struct bus_type	platform_bus_type;
/*
extern struct bus_type  amba_bustype;
extern struct bus_type	coresight_bustype;
extern struct bus_type	cpu_subsys;
extern struct bus_type	dio_bus_type;
extern struct bus_type	eisa_bus_type;
extern struct bus_type  iio_bus_type;
extern struct bus_type	spi_bus_type;
*/
extern struct list_head pci_root_buses;

/* PCI BUS SPACE */

struct pci_bus{
	struct list_head node;
	struct pci_bus   *parent;
	struct list_head children;
	struct list_head devices;
	struct pci_dev	 *self;
	struct list_head slots;
	#ifndef PCI_BRIDGE_RESOURCE_NUM
		#define PCI_BRIDGE_RESOURCE_NUM	4
	#endif
	struct resource  *resource[PCI_BRIDGE_RESOURCE_NUM];
	struct list_head resources;
	struct resource busn_res;
	struct pci_ops	*ops;
	void   *sysdata;
	char __pad0[sizeof(void *)];
	unsigned char number;
	unsigned char primary;
	unsigned char max_bus_speed;
	unsigned char cur_bus_speed;
	char name[48];
	char __pad1[624 - 112];
};


/* USB BUS SPACE */

struct usb_bus{
	struct device *controller;
	struct device *sysdev;
	int busnumber;
	const char *bus_name;
	uint8_t uses_pio_for_control;
	uint8_t usb_otg_port;
	/* etc.. */


};

/* SERIO BUS SPACE */
	/* this must be complete cause the big number of keyboard drivers which employ communication via serio bus */

struct serio{
	void *port_data;
	char name[32];
	char phys[32];
	char fw_id[128];
	bool manual_bind;
	struct serio_device_id{
		uint8_t type;
		uint8_t extra;
		uint8_t id;
		uint8_t proto;
	}id;
	char __pad0[SIZE_OF_STRUCT_SPINLOCK]; /* sizeof spinlock_t */
	int (*write)(struct serio *, unsigned char *);
	int (*open)(struct serio *);
	int (*close)(struct serio *);
	int (*start)(struct serio *);
	int (*stop)(struct serio *);
	struct serio *parent;
	struct list_head child_node;
	struct list_head children;
	unsigned int depth; /* depth of this node in the serio-tree */
	struct serio_driver *drv;
	char __pad1[SIZE_OF_STRUCT_MUTEX]; /* sizeof of mutex */
	char __pad2[SIZE_OF_STRUCT_DEVICE]; /* sizeof of struct device */
	struct list_head node;
	char __pad3[sizeof(void *)]; /* it should be the ptr of ps2_cmd_mutex, not interesting for now */
};

static inline void scan_generic_bus(enum bus_nmbr bus_number){
	struct kobject *kobj = NULL;
	struct bus_type selected_bus = { 0 };
	switch(bus_number){
		case BUS_TYPE_PCI:
			selected_bus = pci_bus_type;
		break;
		case BUS_TYPE_SERIO:
			selected_bus = serio_bus;
		break;
		case BUS_TYPE_I2C:
			selected_bus = i2c_bus_type;
		break;
		/*
		case BUS_TYPE_CPU:
			selected_bus = cpu_subsys;
		break;
		case BUS_TYPE_AMBA:
			selected_bus = amba_bustype;
		break;
		case BUS_TYPE_CORESIGHT:
			selected_bus = coresight_bustype;
		break;
		case BUS_TYPE_EISA:
			selected_bus = eisa_bus_type;
		break;
		case BUS_TYPE_IIO:
			selected_bus = iio_bus_type;
		break;
		case BUS_TYPE_SPI:
			selected_bus = spi_bus_type;
		break;
		*/
		case BUS_TYPE_PLATFORM:
		default:
			selected_bus = platform_bus_type;
		break;
	}
	_printk("selected bus %s\n", selected_bus.name);
	list_for_each_entry(kobj, &selected_bus.p->drivers_kset->list, entry){
		_printk("%s\n", kobj->name);
	}
	return;
}

