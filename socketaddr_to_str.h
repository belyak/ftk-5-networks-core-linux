#ifndef SOCKETADDR_TO_STR_H_
#define SOCKETADDR_TO_STR_H_

#include <sys/socket.h>

/**
 * возвращает указатель на строку вида "a1.a2.a3.a4:port"
 * указатель актуален до следующего вызова, затем буфер заменяется новыми данными.
 */
char * sockaddr_str(const struct sockaddr & addr);


#endif /* SOCKETADDR_TO_STR_H_ */
