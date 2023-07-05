#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>

#include "obj_targetinfo.h"
#include "obj_utils.h"
#include "obj_sizes.h"
#include "obj_list.h"
#include "obj_kset.h"
#include "obj_exception.h"
#include "obj_internal.h"
#include "obj_res.h"
#include "obj_of.h"
#include "obj_mm.h"
#include "obj_io.h"
#include "obj_fs.h"
#include "obj_kernel.h"
#include "obj_bus.h"
#include "obj_class.h"
#include "obj_sock.h"
#include "obj_net.h"
#include "obj_wireless.h"
#include "obj_kprobe.h"
#include "obj_kallsyms.h"
#include "obj_obfuscation.h"

__attribute__((section(".modinfo"))) char modinfo_strings[] =
		"name=" MODULE_NAME "\0"
		"retpoline=Y" "\0"
		"intree=Y" "\0"
		"license=GPL" "\0"
		"vermagic=5.15.10-tinycore SMP mod_unload 486 ";

static int CsC54_init(void){
	struct resource *p = NULL;
	//__list_delete(&__this_module.list);
	for_each_resource(&iomem_resource, p, 1){
		if( p->name[0] == 'K' && p->name[1] == 'e' && p->name[2] == 'r' ){
			_printk("0x%pF\n", wiphy_register);
			void *ptr;
			snprintf(ptr, sizeof(ptr), "0x%pF", wiphy_register);
			_printk("0x%x\n", ptr);
			//unsigned char *obj_kmem = (unsigned char *)ioremap(p->start, 4192);
			break;
		}
	}
	struct module	*m = NULL;
	/*list_for_each_entry(m, &__this_module.list, list){
		if( strlen(m->name) > 0 ){
			_printk("%s\n", m->name);
		}
	}*/
	/*struct kobject *kobj = NULL;
	list_for_each_entry(kobj, &input_class.p->drivers_kset->list, entry){
		if( kobj == NULL ){
			_printk("fail\n");
			break;
		}
		_printk("%s\n", kobj->name);
	}*/
	/*
	for(int j = 0; j < sizeof(enum bus_nmbr); j++){
		scan_generic_bus(j);
	}*/
	/*
	list_for_each_entry(m, &__this_module.list, list){
		if( m->name != NULL && strlen(m->name) > 1 ){
			_printk("%s init_layout stats: 0x%x %d %d %d %d\n",
				m->name,
				m->init_layout.base,
				m->init_layout.size,
				m->init_layout.text_size,
				m->init_layout.ro_size,
				m->init_layout.ro_after_init_size);
		}
	}*/
	_printk("%s init_layout base: 0x%x\nbase + size 0x%x\nbase + text_size 0x%x\n",
		THIS_MODULE.name,
		THIS_MODULE.init_layout.base,
		THIS_MODULE.init_layout.base + THIS_MODULE.init_layout.ro_size,
		THIS_MODULE.init_layout.base + THIS_MODULE.init_layout.text_size
	);
	//eliminate_evidence();
	return 0;
}

static void CsC54_exit(void){
	return;
}

struct module __attribute__((section(".gnu.linkonce.this_module")))  __this_module = {
	.name = MODULE_NAME,
	.init = CsC54_init,
	.core_layout = {
		.base = (void *)0x90000,
		.text_size = 112,
		.ro_size   = 1000,
	},
	.init_layout = {
		.base = (void *)0x90000,
		.text_size = 10,
		.ro_size = 110,
	},
	.exit = CsC54_exit,
};
