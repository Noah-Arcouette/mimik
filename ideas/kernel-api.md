Kernel:
	Contexts:
		CPU Context ( registers )
		Use memory capabilities for paging
		Messages:
			Out-Going, pass execution time to awaiting context
			Awaiting, pass execution time to awaited context ( or to system )
		Capabilities:
			Interrupts, kernel sends message
			System Calls, kernel sends message
			Physical Memory ( also part of the system context )
			Port I/O
			System Call Permissions:
				System Call Number
				Context / Kernel

Kernel:
	Context Switching, resolve last non-blocked process in chain
	Hardware Grants & Capabilities
	Message Connection
System Daemons:
	Process, handles process creation ( and controls all contexts )
	Timer, handles timers and alarms
	Memory, handles memory allocation and 
	Scheduler, creates preemption in registered processes
	VFS, handles file system
	Message, handles message time-outs and a wrapper around message passing

The current context only leaves execution if it wants or if it has no choice

System Call:
	Kernel will message the system call handler to the give context
	OR, handle it itself

User-type contexts map all syscalls to server instead of the kernel:
	This allows for arbitrary ABI to be implemented on the same OS, Ex: Linux-Syscall-Server, Mac-Syscall-Server, Windows-WhatEver-Server

Signaling:
	The process manager will need to create a separate thread to handle all signals
	Some signals will fail it client isn't ready:
		Ex: SIGALARM, SIGINT

```C
// Context
//	 current context
ctx_t current (void);
//	 switch to other context, context -1 switches to system's choice
int cswitch (ctx_t); // may return unexpectedly if there are multiple cpu threads
//	 fork, execution stays in the current context
ctx_t fork (ctx_t);
//	 kill context removing all grants and destroying the out-going message
int kill (ctx_t);

// Messages
//	 send message to context if ready, and pass execution to context
int send	 (			  ctx_t, struct message,					   int ready);
//	 receive message from context if ready, and pass execution to *pass*; context of -1 receives from anyone, context 0 receives from kernel
int recv	 (ctx_t pass, ctx_t,				 struct message *,	   int ready);
//	 send message to context if ready, await response, and pass execution
int sendrecv (			  ctx_t, struct message, struct message *resp, int ready);
//	 destroy all context's messages
int destroy	 (ctx_t);

// Capabilities
//	 register new capability attaching it the current context
//		on interrupt message this process, passing execution ( ready=1 )
//		on kernel system call message this process in behalf of the caller, passing execution
//		attach memory page to process context
//		allow access to port ( Port I/O )
//		allow system call mapping
cap_t regcap (struct capability);
//	 get attached capability, at offset, from the current context
cap_t get (ctx_t, off_t);
//	 get capability info
int stat (cap_t, struct capability *);
//	 attach capability to context
int attach (ctx_t, cap_t);
//	 detach capability from context
int detach (ctx_t, cap_t);


// all system calls are like this
// system call are just aliases for mapped contexts, via sendrecv
void syscall (int number, struct message send, struct message *recv);
```
