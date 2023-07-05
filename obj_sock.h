enum socket_state{
	SS_FREE,
	SS_UNCONNECTED,
	SS_CONNECTING,
	SS_CONNECTED,
	SS_DISCONNECTING,
};

struct socket{
	enum socket_state state;
	short type;
	unsigned long flags;
	char __pad0[sizeof(const void *)];
	struct sock *sock;
	const struct proto_ops	*ops;
	char __pad1[SIZE_OF_SOCKET_WQ];
};

struct msghdr{
	void		*msg_name;
	int		msg_namelen;
	struct{
		int type;
		size_t iov_offset;
		size_t count;
		union{
			char __pad0[sizeof(const void *) * 4];
		};
		union{
			unsigned long nr_segs;
			struct {
				int idx;
				int start_idx;
			};
		};
	}msg_iter;
};

int sock_create(int family, int type, int protocol, struct socket **res);
int sock_create_kern(struct net *net, int family, int type, int protocol, struct socket **res);
int sock_sendmsg(struct socket *sock, struct msghdr *msghdr);
int sock_recvmsg(struct socket *sock, struct msghdr *msghdr, int flags);

/* socket families */
#define AF_UNSPEC	0
#define AF_UNIX		1
#define AF_LOCAL	1
#define AF_INET		2
#define AF_QIPCRTR	42
