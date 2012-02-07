
#ifndef FABLE_H
#define FABLE_H

#include <sys/select.h> // For fd_set
#include <sys/uio.h> // For struct iovec

struct fable_buf {

  struct iovec* bufs;
  int nbufs;
  int written;

} __attribute__((packed));

#ifndef FABLE_TYPE
#error "Must define FABLE_TYPE to use the Fable prototype. Available types: unixdomain"
#endif

#define CONC2(C, D) C ## D
#define CONC(A, B) CONC2(A, B)
// Necessary because sub-macros are expanded *after* expansion and *excluding* parameters to ##. Nice.
// Also, the unix transport must *not* be named 'unix' as unix, lowercase, is #defined to 1 somewhere in libc.

#define fable_init CONC(fable_init_, FABLE_TYPE)
#define fable_connect CONC(fable_connect_, FABLE_TYPE)
#define fable_listen CONC(fable_listen_, FABLE_TYPE)
#define fable_accept CONC(fable_accept_, FABLE_TYPE)
#define fable_set_nonblocking CONC(fable_set_nonblocking_, FABLE_TYPE)
#define fable_get_select_fds CONC(fable_get_select_fds_, FABLE_TYPE)
#define fable_ready CONC(fable_ready_, FABLE_TYPE)
#define fable_get_write_buf CONC(fable_get_write_buf_, FABLE_TYPE)
#define fable_lend_write_buf CONC(fable_lend_write_buf_, FABLE_TYPE)
#define fable_release_write_buf CONC(fable_release_write_buf_, FABLE_TYPE)
#define fable_get_read_buf CONC(fable_get_read_buf_, FABLE_TYPE)
#define fable_lend_read_buf CONC(fable_lend_read_buf_, FABLE_TYPE)
#define fable_release_read_buf CONC(fable_release_read_buf_, FABLE_TYPE)
#define fable_close CONC(fable_close_, FABLE_TYPE)

#define FABLE_SELECT_READ 1
#define FABLE_SELECT_WRITE 2
#define FABLE_SELECT_ACCEPT 3

void fable_init_unixdomain();
void* fable_connect_unixdomain(const char* name);
void* fable_listen_unixdomain(const char* name);
void* fable_accept_unixdomain(void* listen_handle);
void fable_set_nonblocking_unixdomain(void* handle);
void fable_get_select_fds_unixdomain(void* handle, int type, int* maxfd, fd_set* rfds, fd_set* wfds, fd_set* efds, struct timeval* timeout);
int fable_ready_unixdomain(void* handle, int type, fd_set* rfds, fd_set* wfds, fd_set* efds);
struct fable_buf* fable_get_write_buf_unixdomain(void* handle, int len);
struct fable_buf* fable_lend_write_buf_unixdomain(void* handle, const char* buf, int len);
int fable_release_write_buf_unixdomain(void* handle, struct fable_buf* buf);
int fable_lend_read_buf(void* handle, char* buf, int len);
struct fable_buf* fable_get_read_buf(void* handle, int len);
void fable_release_read_buf(void* handle, struct fable_buf* buf);
void fable_close_unixdomain(void* handle);

#endif
