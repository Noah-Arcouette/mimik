/*

All architectures must define these constructs

*/
#ifndef __INTERNAL_LIB_C_SYSTEM_H__
#define __INTERNAL_LIB_C_SYSTEM_H__

int __system_unlink (const char *);
int __system_link   (const char *src, const char *dst);

#endif
