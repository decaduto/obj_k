struct task_struct{



};

extern struct task_struct init_task;


#define for_each_process(p)	\
	for( p = &init_task; (p = next_task(p) != &init_task); )

