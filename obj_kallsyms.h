#ifdef CONFIG_KALLSYMS

struct mod_kallsyms{
	#ifdef TARGET_IS_32_BIT
		Elf32_Sym *symtab;
	#else
		Elf64_Sym *symtab;
	#endif
	unsigned int num_symtab;
	char *strtab;
	#ifdef TARGET_VERSION >= 515
	char *typetab;
	#endif
};

#endif
