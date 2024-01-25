System of Daemons:
Kernel:
    Capabilities
    Messaging
    Context Switching
User:
    Initiate System
    Processes
    Scheduling
    Memory
    Swap
    VFS
    Scheduling
    Drives


Kernel:
    Contexts:
        System Context ( registers )
        Messages
        Capabilities
            Interrupts
            System Calls
            Memory Paging ( also part of the system context )
            Port I/O
            System Functionality

```C
// Context
//   current
ctx_t current (void);
// next / previous
ctx_t next     (ctx_t);
ctx_t previous (ctx_t);
//   switch
int cswitch (ctx_t);
//   fork
ctx_t fork (ctx_t, void *);
//   kill
int kill (ctx_t);

// Messages
//   pop
int pop (ctx_t, struct message *);
//   push
int push (ctx_t, struct message);
//   peek
int peek (ctx_t, off_t, struct message *);
//   update
int update (ctx_t, off_t, struct message);
//   remove
int remove (ctx_t, off_t);

// Capabilities
//   register
//      on interrupt message this process
//      on system call message this process
//      attach memory page to process context
//      allow access to port
//      allow system functionality
cap_t regcap (struct capability);
//   get
cap_t get (ctx_t, off_t);
//   stat
int stat (cap_t, struct capability *);
//   attach
int attach (ctx_t, cap_t);
//   detach
int detach (ctx_t, cap_t);
```
