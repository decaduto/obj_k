/* basic API for interacting with filesystem */

#ifndef loff_t
	#define loff_t	off_t
#endif

struct path{
	struct vfsmount *mnt;
	struct dentry   *dentry;
};

struct inode{

};

#define TOTAL_SIZE_OF_STRUCT_FILE	160

struct file_operations{
	struct module 	*owner;
	char		__pad0[sizeof(void *)];
	size_t		(*read)(struct file*, char *, size_t, loff_t *);
	size_t		(*write)(struct file *, char *, size_t, loff_t *);
	/* other pointers aren't relevant, we use just the first 4 field */
};

struct file{
	char __pad0[8];
	struct path			f_path;
	struct inode			*f_inode;
	const struct file_operations 	*f_ops;
	char __pad1[TOTAL_SIZE_OF_STRUCT_FILE - 24];
}__attribute__((aligned(4)));

extern struct file 	*filp_open(const char *fname, int flags, unsigned short mode);
extern int 	   	filp_close(struct file *, void *);
extern size_t		vfs_write(struct file *, char *, size_t, loff_t *);
extern size_t		vfs_read(struct file *, char *, size_t, loff_t *);
