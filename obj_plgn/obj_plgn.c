/* this is the obfuscator plugin made for obj.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gcc-plugin.h>
#include <coretypes.h>
#include <tree.h>
#include <gimple.h>
#include <tree-pass.h>
#include <plugin-version.h>
#include <rtl.h>
#include <print-rtl.h>
#include <memmodel.h>
#include <emit-rtl.h>
#include <cgraph.h>
#include <stringpool.h>
#include <gimple-iterator.h>
#include <cfgloop.h>
#include <output.h>

#include <sys/mman.h>

#include "colors.h"

int plugin_is_GPL_compatible = 1;

/*
static void obj_passes(void *gcc_data, void *user_data){
	struct function 	*f    = NULL;
	struct symtab_node 	*sym  = NULL;
	struct cgraph_node	*node = NULL;
	basic_block		bb;
	gimple_stmt_iterator	gsi;
	gphi_iterator pi;
	FOR_EACH_FUNCTION(node){
		f = node->get_fun();
		if( f != NULL ){
			FOR_EACH_BB_FN(bb, f){
			}
		}else{
			/* do nothing */
	/*FOR_EACH_SYMBOL(sym){
		printf("%s\n", sym->name());
		section *sec = get_section(".text", SECTION_CODE, NULL);
		switch_to_section(sec);
		//output_section_asm_op('a');
		// encrypt strings
		char *ncrypted_str = (char *)xmalloc(strlen(sym->name()));
		strcpy(ncrypted_str, sym->name());
		for(int i = 0; i < strlen(ncrypted_str); i++){
			ncrypted_str[i] = ncrypted_str[i] ^ 0xff;
		}
		assemble_string( ncrypted_str, strlen(sym->name()) );
	}*/
namespace {
	const pass_data pass_data_munger = {
		RTL_PASS,
		"munger",
		OPTGROUP_ALL,
		TV_NONE,
		0,
		0,
		0,
		0,
		TODO_dump_symtab
	};
	class pass_munger : public rtl_opt_pass{
		public:
			pass_munger() : rtl_opt_pass(pass_data_munger, NULL){
				rtx_insn *insn, *next;
				for(insn = get_insns(); insn; insn = next){
					next = NEXT_INSN(insn);
					printf("1");
				}
			}
		};
}

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version){
	printf(PLUGIN_COLOR_RED "using the encryption obfuscation offered by " PLUGIN_COLOR_GREEN "obj_plgn!\n" PLUGIN_COLOR_RESET);
	struct register_pass_info pass = { 0 };
	pass.pass = new pass_munger();
	pass.reference_pass_name = "pro_and_epilogue"; //"*rest_of_compilation";
	pass.ref_pass_instance_number = 1;
	pass.pos_op = PASS_POS_INSERT_AFTER;
	register_callback("munger", PLUGIN_PASS_MANAGER_SETUP, NULL, &pass);
	//register_callback("obj", PLUGIN_ALL_IPA_PASSES_END, obj_passes, NULL);
	return 0;
}
