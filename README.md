# 42cursus-ft_irc
42's project which requires to create an Internet Relay Chat (IRC) server


## A - Introduction

### I - Understand the IRC

**IRC (Internet Relay Chat)** is a text-based chat system for *instant messaging*. IRC is designed for *group communication* in discussion forums, called channels, but also allows one-on-one communication via *private messages* as well as chat and data transfer, including *file sharing*.

IRC follows **client-server model**. It means that both client and server software are required in order to use it. 

### II - Requirements

As we have IRC Client `Konverstation` in 42. We will take it like the reference IRC Client.

#### 1 - 🔑 Authentication

When you connect with the password in Konversation, check your server log:
it should accept only if password matches ./ircserv <port> <password>.

/pass <password> → Check before allowing other commands.
/nick <nickname> → Set nickname, must be unique.
USER <username> <mode> <unused> :<realname> → Set username.


#### 2 - Messaging

JOIN #channel [key] → Create or join channel.
PART #channel → Leave channel.
PRIVMSG <target> :message → Send to user or channel.
NOTICE <target> :message → Like PRIVMSG but no auto-replies.

#### 3 - Channel Operator Commands

KICK #channel <nick> → Remove user.
INVITE <nick> #channel → Invite user.
TOPIC #channel [:topic] → View/change topic.
MODE #channel <flags>:

+i/-i Invite only
+t/-t Only ops can change topic
+k/-k <key> Set/remove password
+o/-o <nick> Op privileges
+l/-l <limit> Limit users

### III - Functions

#### 1 - `socket`

`socket()` creates an endpoint for communication of a specified type (such as stream or datagram) and returns a file descriptor that refers to that endpoint (and `-1` if error)

```c
int	socket(int domain, int type, int protocol);
```
- `domain`: specifies the communication domain or address familly for the socket. Common values include `AF_INET` (IPv4), `AF_INET6` (IPv6)
- `type`: specifies the type of communication sematics for socket. Common values include `SOCK_STREAM` (TCP, providing reliable, bidirectional, byte-stream communication), `SOCK_DGRAM` (UDP, providing datagram-oriented communication)
- `protocol`: specifies protocol to be used with socket, default `0` indicating that system should choose an appropriate protocol based on specified domain and type.

#### 2 - `setsockopt`

`setsockopt()` configures socket options (e.g., reuse address). It allows us to set various socket-level options to control the behavior of socket.

```c
int	setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
```

- `level`: indicates protocol level at which the option resides. Common values include `SOL_SOCKET` indicates that option being set is a socket-level option and should be applied to socket itself. Other values as `IPPROTO_TCP` for TCP-specific options or IPPROTO-IP for IP-specific options.
- `option_name`: `SO_REUSEADDR` allows for immediate reuse of local addresses and ports.
- `option_value`: a pointer to the value that needs to be set for the option.
- `option_len`: size of `option_value`.

#### 3 - `getsockname`

`getsockname()` gets local address of socket into `address`. It returns `0` if successful and `-1` if error.

```c
int	getsockname(int socket, struct sockadd *restrict address, socklen_t *restrict address_len);
```

- `address_len`: should be initialized to indicate size of space pointed to by `address`.

#### 4 - `getprotobyname`

`getprotobyname()` gets protocol info by `name` (e.g., "tcp" or "udp"). It returns a structure containning network protocol data base.

```c
struct protoent	*getprotobyname(const char *name);
```

#### 5 - `getaddrinfo`, `freeaddinfo`

`getaddrinfo()` resolves hostname and service into an usable socket address `sockaddr` structure.
`freeaddrinfo()` frees memory allocated by `getaddrinfo`

```c
int	getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res);

void	freeaddrinfo(struct addrinfo *ai);
```

#### 6 - `bind`

`bind()` assigns the address `addr`, which has the size `addrlen`, to the socket `sockfd`.

```c
int	bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

#### 7 - `connect`

`connect()` connects a client socket to a server.

```c
int	connect(int sockfd, const struct sockaddr *serv_addr, socklen_t serv_addr_len);
```

#### 8 - `listen`, `accept` (in Server)

`listen()` listen for connections on a passive socket, ready to `accept()` incomming connections.

```c
int	listen(int sockfd, int backlog);

int	accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addr_len);
```

- `backlog`: the maximum number of connection requests that can be queued by the operating system while the server is handling existing connections.

#### 9 - `htons()` / `htonl()` and `ntohs()` / `ntohl()`

`htons()` / `htonl()` and `ntohs()` / `ntohl()`: convert values between host and network byte order.

```c
uint16_t	htons(uint16_t hostshort);
uint32_t	htonl(uint32_t hostlong);

uint16_t	ntohs(uint16_t netshort);
uint32_t	ntohl(uint32_t netlong);
```

#### 10 - `inet_addr()`, `inet_ntoa()`

`inet_addr()` interprets character strings representing numbers expressed in the Internet standard '.' notation `in_addr_t` type.
`inet_ntoa()` takes an Internet address and returns an ASCII string representing the address in '.' notation.

```c
in_addr_t	inet_addr(const char *cp);

char	*inet_ntoa(struct in_addr in);
```

#### 11 - `send()`

`send()` is used to transmit data to another socket `sockfd` in connected state.

```c
ssize_t	send(int sockfd, const void *buffer, size_t length, int flags);
```

#### 12 - `recv()`

`recv()` is used to receive data from connected socket. It's commonly used in TCP socket communication to read data sent by remote peer.

```c
ssize_t	recv(int sockfd, void *buffer, size_t length, int flags);
```

- `sockfd`: the file descriptor of socket from which to receive data.
- `buffer`: a pointer to the buffer where the received data will be stored.
- `length`: buffer size.
- `flags`: optional flags to control the behavior of the function: `MSG_WAITALL`, `MSG_DONTWAIT`, `MSG_PEEK`, `MSG_TRUNC`.

#### 13 - fcntl()

`fcntl()` performs various control operations `cmd` on file descriptors `fd`. In this case, we want to set non-blocking.

```c
int	fcntl(int fd, int cmd, ...);

fcntl(sockfd, F_SETFL, O_NONBLOCK);
```

#### 14 - poll()

`poll()` examines a set of file descriptors `fds` to see if some of them are ready for I/O or if certain events have occurred on them.

```c
#include <poll.h>

int	poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

- `nfds`: numbers of elements in the `fds` array.
- `timeout`: maximum time to wait for an event to occur, in milliseconds. `-1` means wait indefinitely, `0` means return immediately, and positive value specifies a timeout period in millisecond.

#### 15 - lseek()

`lseek()` repositions the offset of the opened file descriptor `fd` to the argument `offset`, according to the directive `whence`.

```c
#include <unistd.h>

off_t	lseek(int fd, off_t offset, int whence);
```

#### 16 - fstat()

`fstat()` obtains the information about an open file known by file descriptor `fd` and saves into a stat structure `buf`.

```c
#include <sys/stat.h>

int	fstat(int fd, struct stat *buf);
```

## B - Pseudo Code

### Phase 0 — Setup

Goal: A clean project skeleton with Makefile.

Tasks:

Write Makefile (all, clean, fclean, re).

Create core classes:

Server (manages socket, clients, channels).

Client (tracks fd, nick, username, auth status).

Channel (tracks users, operators, topic, modes).

Initialize server socket:

socket, setsockopt, bind, listen.

Use poll() for handling multiple fds.

Test:

```bash
./ircserv 6667 password
nc localhost 6667 #→ should connect and not hang.
```

### Phase 1 — Connection & Authentication

Goal: Clients connect and authenticate with password.

Features:

On connect, client is in unauthenticated state.

Require PASS, NICK, and USER before marking client as “registered”.

Store nick/username inside Client.

Tests:

Netcat:

PASS password
NICK tat
USER tat 0 * :Tat Hoang


→ Should see welcome message (001).

Wrong PASS → disconnect.

### Phase 2 — Basic Commands

Goal: Implement fundamental IRC flow.

Features:

PING / PONG (keepalive).

QUIT (clean disconnect).

JOIN <#chan>: create channel if not exists, add user.

PART <#chan>: leave channel.

PRIVMSG <target> <msg>:

Target = nick → send direct.

Target = channel → broadcast to channel.

Tests:

Run 2 Konversation clients.

Both JOIN #42school.

Send “hello” → both should see it.

/msg <nick> hi → only target sees it.

### Phase 3 — Operators and Privileges

Goal: Implement operator roles inside channels.

Features:

First client joining a channel becomes operator.

Track operators with a set in Channel.

Allow operators to promote/demote with MODE +o/-o.

Tests:

Two users in #42school.

Operator runs /mode #42school +o alice.

Alice should appear with @ in Konversation.

### Phase 4 — Operator Commands

Goal: Implement required commands.

Features:

KICK <#chan> <nick> :reason

INVITE <nick> <#chan>

TOPIC <#chan> [topic]

No arg → show topic.

With arg → set topic (only ops if +t mode).

MODE <#chan> flags:

+i / -i (invite only).

+t / -t (topic only ops).

+k / -k (channel key).

+o / -o (operator).

+l / -l (user limit).

Tests:

With Konversation:

/kick someone → they’re removed.

/invite works if channel is +i.

/topic changes and syncs to all.

/mode toggles correctly.

### Phase 5 — Robustness

Goal: Make server stable & evaluable.

Tasks:

Handle partial messages (IRC messages end with \r\n).

Ensure non-blocking I/O (fcntl).

Implement poll loop correctly.

Clean disconnect on client quit or socket close.

Tests:

Connect 10+ Netcat sessions, join one channel.

Send one message → all receive.

Close one Netcat → server cleans it up.

### Phase 6 — Validation

Goal: Confirm compliance.

Tasks:

Run against your reference client (Konversation).

Compare behavior with a real IRC network (e.g., libera.chat).

Tests:

Every required feature must behave the same.

Use Netcat for debugging raw protocol.

### 🚀 Final Notes

Always test new features first with Netcat (to see raw protocol),
then confirm with Konversation (real client).

Stick to port 6667 (safe, expected for IRC).

Don’t forget signals: handle SIGINT (Ctrl+C) gracefully → close sockets.


## C - Testing

## D - Issues and Bugs


#### References

- [IRC]
- [Client nc - NetCat](https://www.geeksforgeeks.org/linux-unix/practical-uses-of-ncnetcat-command-in-linux/)
- [Client irssi](https://irssi.org/)
- [Client weechat](https://weechat.org/)
- [Internet Relay Chat: Server Protocol - RFC2813](https://datatracker.ietf.org/doc/html/rfc2813)