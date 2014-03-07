# 1 "Breakout.c"
# 1 "/Users/eroberts/source/jbe//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Breakout.c"






# 1 "/usr/include/stdio.h" 1 3 4
# 64 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/_types.h" 1 3 4
# 27 "/usr/include/_types.h" 3 4
# 1 "/usr/include/sys/_types.h" 1 3 4
# 32 "/usr/include/sys/_types.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 33 "/usr/include/sys/_types.h" 2 3 4
# 1 "/usr/include/machine/_types.h" 1 3 4
# 34 "/usr/include/machine/_types.h" 3 4
# 1 "/usr/include/i386/_types.h" 1 3 4
# 37 "/usr/include/i386/_types.h" 3 4
typedef signed char __int8_t;



typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
# 70 "/usr/include/i386/_types.h" 3 4
typedef int __darwin_ct_rune_t;





typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;


typedef long int __darwin_ptrdiff_t;





typedef long unsigned int __darwin_size_t;





typedef __builtin_va_list __darwin_va_list;





typedef int __darwin_wchar_t;




typedef __darwin_wchar_t __darwin_rune_t;


typedef int __darwin_wint_t;




typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
# 35 "/usr/include/machine/_types.h" 2 3 4
# 34 "/usr/include/sys/_types.h" 2 3 4
# 58 "/usr/include/sys/_types.h" 3 4
struct __darwin_pthread_handler_rec
{
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};
struct _opaque_pthread_attr_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_cond_t { long __sig; char __opaque[40]; };
struct _opaque_pthread_condattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_mutex_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_mutexattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_once_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_rwlock_t { long __sig; char __opaque[192]; };
struct _opaque_pthread_rwlockattr_t { long __sig; char __opaque[16]; };
struct _opaque_pthread_t { long __sig; struct __darwin_pthread_handler_rec *__cleanup_stack; char __opaque[1168]; };
# 94 "/usr/include/sys/_types.h" 3 4
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;

typedef __darwin_ino64_t __darwin_ino_t;



typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef struct _opaque_pthread_attr_t
   __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t
   __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t
   __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t
   __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t
   __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t
   __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t
   __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t
   __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t
   *__darwin_pthread_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];
# 28 "/usr/include/_types.h" 2 3 4
# 39 "/usr/include/_types.h" 3 4
typedef int __darwin_nl_item;
typedef int __darwin_wctrans_t;

typedef __uint32_t __darwin_wctype_t;
# 65 "/usr/include/stdio.h" 2 3 4





typedef __darwin_va_list va_list;




typedef __darwin_off_t off_t;




typedef __darwin_size_t size_t;






typedef __darwin_off_t fpos_t;
# 98 "/usr/include/stdio.h" 3 4
struct __sbuf {
 unsigned char *_base;
 int _size;
};


struct __sFILEX;
# 132 "/usr/include/stdio.h" 3 4
typedef struct __sFILE {
 unsigned char *_p;
 int _r;
 int _w;
 short _flags;
 short _file;
 struct __sbuf _bf;
 int _lbfsize;


 void *_cookie;
 int (*_close)(void *);
 int (*_read) (void *, char *, int);
 fpos_t (*_seek) (void *, fpos_t, int);
 int (*_write)(void *, const char *, int);


 struct __sbuf _ub;
 struct __sFILEX *_extra;
 int _ur;


 unsigned char _ubuf[3];
 unsigned char _nbuf[1];


 struct __sbuf _lb;


 int _blksize;
 fpos_t _offset;
} FILE;



extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;




# 248 "/usr/include/stdio.h" 3 4

void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE * , fpos_t *);
char *fgets(char * , int, FILE *);



FILE *fopen(const char * , const char * ) __asm("_" "fopen" );

int fprintf(FILE * , const char * , ...) ;
int fputc(int, FILE *);
int fputs(const char * , FILE * ) __asm("_" "fputs" );
size_t fread(void * , size_t, size_t, FILE * );
FILE *freopen(const char * , const char * ,
     FILE * ) __asm("_" "freopen" );
int fscanf(FILE * , const char * , ...) ;
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void * , size_t, size_t, FILE * ) __asm("_" "fwrite" );
int getc(FILE *);
int getchar(void);
char *gets(char *);

extern const int sys_nerr;
extern const char *const sys_errlist[];

void perror(const char *);
int printf(const char * , ...) ;
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename (const char *, const char *);
void rewind(FILE *);
int scanf(const char * , ...) ;
void setbuf(FILE * , char * );
int setvbuf(FILE * , char * , int, size_t);
int sprintf(char * , const char * , ...) ;
int sscanf(const char * , const char * , ...) ;
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE * , const char * , va_list) ;
int vprintf(const char * , va_list) ;
int vsprintf(char * , const char * , va_list) ;

int asprintf(char **, const char *, ...) ;
int vasprintf(char **, const char *, va_list) ;










char *ctermid(char *);

char *ctermid_r(char *);




FILE *fdopen(int, const char *) __asm("_" "fdopen" );


char *fgetln(FILE *, size_t *);

int fileno(FILE *);
void flockfile(FILE *);

const char
 *fmtcheck(const char *, const char *);
int fpurge(FILE *);

int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);

int getw(FILE *);

int pclose(FILE *);



FILE *popen(const char *, const char *) __asm("_" "popen" );

int putc_unlocked(int, FILE *);
int putchar_unlocked(int);

int putw(int, FILE *);
void setbuffer(FILE *, char *, int);
int setlinebuf(FILE *);

int snprintf(char * , size_t, const char * , ...) ;
char *tempnam(const char *, const char *) __asm("_" "tempnam" );
int vfscanf(FILE * , const char * , va_list) ;
int vscanf(const char * , va_list) ;
int vsnprintf(char * , size_t, const char * , va_list) ;
int vsscanf(const char * , const char * , va_list) ;

FILE *zopen(const char *, const char *, int);








FILE *funopen(const void *,
  int (*)(void *, char *, int),
  int (*)(void *, const char *, int),
  fpos_t (*)(void *, fpos_t, int),
  int (*)(void *));

# 383 "/usr/include/stdio.h" 3 4

int __srget(FILE *);
int __svfscanf(FILE *, const char *, va_list) ;
int __swbuf(int, FILE *);








static __inline int __sputc(int _c, FILE *_p) {
 if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
  return (*_p->_p++ = _c);
 else
  return (__swbuf(_c, _p));
}
# 443 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/secure/_stdio.h" 1 3 4
# 31 "/usr/include/secure/_stdio.h" 3 4
# 1 "/usr/include/secure/_common.h" 1 3 4
# 32 "/usr/include/secure/_stdio.h" 2 3 4
# 42 "/usr/include/secure/_stdio.h" 3 4
extern int __sprintf_chk (char * , int, size_t,
     const char * , ...)
  ;




extern int __snprintf_chk (char * , size_t, int, size_t,
      const char * , ...)
  ;




extern int __vsprintf_chk (char * , int, size_t,
      const char * , va_list)
  ;




extern int __vsnprintf_chk (char * , size_t, int, size_t,
       const char * , va_list)
  ;
# 444 "/usr/include/stdio.h" 2 3 4
# 8 "Breakout.c" 2
# 1 "/Users/eroberts/include/cslib.h" 1
# 21 "/Users/eroberts/include/cslib.h"
# 1 "/usr/include/stdlib.h" 1 3 4
# 61 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/Availability.h" 1 3 4
# 126 "/usr/include/Availability.h" 3 4
# 1 "/usr/include/AvailabilityInternal.h" 1 3 4
# 127 "/usr/include/Availability.h" 2 3 4
# 62 "/usr/include/stdlib.h" 2 3 4



# 1 "/usr/include/sys/wait.h" 1 3 4
# 79 "/usr/include/sys/wait.h" 3 4
typedef enum {
 P_ALL,
 P_PID,
 P_PGID
} idtype_t;






typedef __darwin_pid_t pid_t;




typedef __darwin_id_t id_t;
# 116 "/usr/include/sys/wait.h" 3 4
# 1 "/usr/include/sys/signal.h" 1 3 4
# 73 "/usr/include/sys/signal.h" 3 4
# 1 "/usr/include/sys/appleapiopts.h" 1 3 4
# 74 "/usr/include/sys/signal.h" 2 3 4







# 1 "/usr/include/machine/signal.h" 1 3 4
# 34 "/usr/include/machine/signal.h" 3 4
# 1 "/usr/include/i386/signal.h" 1 3 4
# 39 "/usr/include/i386/signal.h" 3 4
typedef int sig_atomic_t;
# 55 "/usr/include/i386/signal.h" 3 4
# 1 "/usr/include/i386/_structs.h" 1 3 4
# 56 "/usr/include/i386/signal.h" 2 3 4
# 35 "/usr/include/machine/signal.h" 2 3 4
# 82 "/usr/include/sys/signal.h" 2 3 4
# 154 "/usr/include/sys/signal.h" 3 4
# 1 "/usr/include/sys/_structs.h" 1 3 4
# 57 "/usr/include/sys/_structs.h" 3 4
# 1 "/usr/include/machine/_structs.h" 1 3 4
# 31 "/usr/include/machine/_structs.h" 3 4
# 1 "/usr/include/i386/_structs.h" 1 3 4
# 38 "/usr/include/i386/_structs.h" 3 4
# 1 "/usr/include/mach/i386/_structs.h" 1 3 4
# 43 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_i386_thread_state
{
    unsigned int __eax;
    unsigned int __ebx;
    unsigned int __ecx;
    unsigned int __edx;
    unsigned int __edi;
    unsigned int __esi;
    unsigned int __ebp;
    unsigned int __esp;
    unsigned int __ss;
    unsigned int __eflags;
    unsigned int __eip;
    unsigned int __cs;
    unsigned int __ds;
    unsigned int __es;
    unsigned int __fs;
    unsigned int __gs;
};
# 89 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_fp_control
{
    unsigned short __invalid :1,
        __denorm :1,
    __zdiv :1,
    __ovrfl :1,
    __undfl :1,
    __precis :1,
      :2,
    __pc :2,





    __rc :2,






             :1,
      :3;
};
typedef struct __darwin_fp_control __darwin_fp_control_t;
# 147 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_fp_status
{
    unsigned short __invalid :1,
        __denorm :1,
    __zdiv :1,
    __ovrfl :1,
    __undfl :1,
    __precis :1,
    __stkflt :1,
    __errsumm :1,
    __c0 :1,
    __c1 :1,
    __c2 :1,
    __tos :3,
    __c3 :1,
    __busy :1;
};
typedef struct __darwin_fp_status __darwin_fp_status_t;
# 191 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_mmst_reg
{
 char __mmst_reg[10];
 char __mmst_rsrv[6];
};
# 210 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_xmm_reg
{
 char __xmm_reg[16];
};
# 232 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_i386_float_state
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;
 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;
 __uint16_t __fpu_rsrv2;
 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;
 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 char __fpu_rsrv4[14*16];
 int __fpu_reserved1;
};
# 308 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_i386_exception_state
{
    unsigned int __trapno;
    unsigned int __err;
    unsigned int __faultvaddr;
};
# 326 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_debug_state32
{
 unsigned int __dr0;
 unsigned int __dr1;
 unsigned int __dr2;
 unsigned int __dr3;
 unsigned int __dr4;
 unsigned int __dr5;
 unsigned int __dr6;
 unsigned int __dr7;
};
# 358 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_thread_state64
{
 __uint64_t __rax;
 __uint64_t __rbx;
 __uint64_t __rcx;
 __uint64_t __rdx;
 __uint64_t __rdi;
 __uint64_t __rsi;
 __uint64_t __rbp;
 __uint64_t __rsp;
 __uint64_t __r8;
 __uint64_t __r9;
 __uint64_t __r10;
 __uint64_t __r11;
 __uint64_t __r12;
 __uint64_t __r13;
 __uint64_t __r14;
 __uint64_t __r15;
 __uint64_t __rip;
 __uint64_t __rflags;
 __uint64_t __cs;
 __uint64_t __fs;
 __uint64_t __gs;
};
# 413 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_float_state64
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;


 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;

 __uint16_t __fpu_rsrv2;


 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;

 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 struct __darwin_xmm_reg __fpu_xmm8;
 struct __darwin_xmm_reg __fpu_xmm9;
 struct __darwin_xmm_reg __fpu_xmm10;
 struct __darwin_xmm_reg __fpu_xmm11;
 struct __darwin_xmm_reg __fpu_xmm12;
 struct __darwin_xmm_reg __fpu_xmm13;
 struct __darwin_xmm_reg __fpu_xmm14;
 struct __darwin_xmm_reg __fpu_xmm15;
 char __fpu_rsrv4[6*16];
 int __fpu_reserved1;
};
# 517 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_exception_state64
{
    unsigned int __trapno;
    unsigned int __err;
    __uint64_t __faultvaddr;
};
# 535 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_debug_state64
{
 __uint64_t __dr0;
 __uint64_t __dr1;
 __uint64_t __dr2;
 __uint64_t __dr3;
 __uint64_t __dr4;
 __uint64_t __dr5;
 __uint64_t __dr6;
 __uint64_t __dr7;
};
# 39 "/usr/include/i386/_structs.h" 2 3 4
# 48 "/usr/include/i386/_structs.h" 3 4
struct __darwin_mcontext32
{
 struct __darwin_i386_exception_state __es;
 struct __darwin_i386_thread_state __ss;
 struct __darwin_i386_float_state __fs;
};
# 68 "/usr/include/i386/_structs.h" 3 4
struct __darwin_mcontext64
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_state64 __ss;
 struct __darwin_x86_float_state64 __fs;
};
# 91 "/usr/include/i386/_structs.h" 3 4
typedef struct __darwin_mcontext64 *mcontext_t;
# 32 "/usr/include/machine/_structs.h" 2 3 4
# 58 "/usr/include/sys/_structs.h" 2 3 4
# 75 "/usr/include/sys/_structs.h" 3 4
struct __darwin_sigaltstack
{
 void *ss_sp;
 __darwin_size_t ss_size;
 int ss_flags;
};
# 128 "/usr/include/sys/_structs.h" 3 4
struct __darwin_ucontext
{
 int uc_onstack;
 __darwin_sigset_t uc_sigmask;
 struct __darwin_sigaltstack uc_stack;
 struct __darwin_ucontext *uc_link;
 __darwin_size_t uc_mcsize;
 struct __darwin_mcontext64 *uc_mcontext;



};
# 218 "/usr/include/sys/_structs.h" 3 4
typedef struct __darwin_sigaltstack stack_t;
# 227 "/usr/include/sys/_structs.h" 3 4
typedef struct __darwin_ucontext ucontext_t;
# 155 "/usr/include/sys/signal.h" 2 3 4
# 163 "/usr/include/sys/signal.h" 3 4
typedef __darwin_pthread_attr_t pthread_attr_t;




typedef __darwin_sigset_t sigset_t;
# 178 "/usr/include/sys/signal.h" 3 4
typedef __darwin_uid_t uid_t;


union sigval {

 int sival_int;
 void *sival_ptr;
};





struct sigevent {
 int sigev_notify;
 int sigev_signo;
 union sigval sigev_value;
 void (*sigev_notify_function)(union sigval);
 pthread_attr_t *sigev_notify_attributes;
};


typedef struct __siginfo {
 int si_signo;
 int si_errno;
 int si_code;
 pid_t si_pid;
 uid_t si_uid;
 int si_status;
 void *si_addr;
 union sigval si_value;
 long si_band;
 unsigned long __pad[7];
} siginfo_t;
# 292 "/usr/include/sys/signal.h" 3 4
union __sigaction_u {
 void (*__sa_handler)(int);
 void (*__sa_sigaction)(int, struct __siginfo *,
         void *);
};


struct __sigaction {
 union __sigaction_u __sigaction_u;
 void (*sa_tramp)(void *, int, int, siginfo_t *, void *);
 sigset_t sa_mask;
 int sa_flags;
};




struct sigaction {
 union __sigaction_u __sigaction_u;
 sigset_t sa_mask;
 int sa_flags;
};
# 354 "/usr/include/sys/signal.h" 3 4
typedef void (*sig_t)(int);
# 371 "/usr/include/sys/signal.h" 3 4
struct sigvec {
 void (*sv_handler)(int);
 int sv_mask;
 int sv_flags;
};
# 390 "/usr/include/sys/signal.h" 3 4
struct sigstack {
 char *ss_sp;
 int ss_onstack;
};
# 412 "/usr/include/sys/signal.h" 3 4

void (*signal(int, void (*)(int)))(int);

# 117 "/usr/include/sys/wait.h" 2 3 4
# 1 "/usr/include/sys/resource.h" 1 3 4
# 76 "/usr/include/sys/resource.h" 3 4
# 1 "/usr/include/sys/_structs.h" 1 3 4
# 100 "/usr/include/sys/_structs.h" 3 4
struct timeval
{
 __darwin_time_t tv_sec;
 __darwin_suseconds_t tv_usec;
};
# 77 "/usr/include/sys/resource.h" 2 3 4
# 88 "/usr/include/sys/resource.h" 3 4
typedef __uint64_t rlim_t;
# 144 "/usr/include/sys/resource.h" 3 4
struct rusage {
 struct timeval ru_utime;
 struct timeval ru_stime;
# 155 "/usr/include/sys/resource.h" 3 4
 long ru_maxrss;

 long ru_ixrss;
 long ru_idrss;
 long ru_isrss;
 long ru_minflt;
 long ru_majflt;
 long ru_nswap;
 long ru_inblock;
 long ru_oublock;
 long ru_msgsnd;
 long ru_msgrcv;
 long ru_nsignals;
 long ru_nvcsw;
 long ru_nivcsw;


};
# 215 "/usr/include/sys/resource.h" 3 4
struct rlimit {
 rlim_t rlim_cur;
 rlim_t rlim_max;
};
# 237 "/usr/include/sys/resource.h" 3 4

int getpriority(int, id_t);

int getiopolicy_np(int, int);

int getrlimit(int, struct rlimit *) __asm("_" "getrlimit" );
int getrusage(int, struct rusage *);
int setpriority(int, id_t, int);

int setiopolicy_np(int, int, int);

int setrlimit(int, const struct rlimit *) __asm("_" "setrlimit" );

# 118 "/usr/include/sys/wait.h" 2 3 4
# 193 "/usr/include/sys/wait.h" 3 4
# 1 "/usr/include/machine/endian.h" 1 3 4
# 37 "/usr/include/machine/endian.h" 3 4
# 1 "/usr/include/i386/endian.h" 1 3 4
# 99 "/usr/include/i386/endian.h" 3 4
# 1 "/usr/include/sys/_endian.h" 1 3 4
# 124 "/usr/include/sys/_endian.h" 3 4
# 1 "/usr/include/libkern/_OSByteOrder.h" 1 3 4
# 66 "/usr/include/libkern/_OSByteOrder.h" 3 4
# 1 "/usr/include/libkern/i386/_OSByteOrder.h" 1 3 4
# 44 "/usr/include/libkern/i386/_OSByteOrder.h" 3 4
static __inline__
__uint16_t
_OSSwapInt16(
    __uint16_t _data
)
{
    return ((_data << 8) | (_data >> 8));
}

static __inline__
__uint32_t
_OSSwapInt32(
    __uint32_t _data
)
{



    __asm__ ("bswap   %0" : "+r" (_data));
    return _data;

}
# 91 "/usr/include/libkern/i386/_OSByteOrder.h" 3 4
static __inline__
__uint64_t
_OSSwapInt64(
    __uint64_t _data
)
{
    __asm__ ("bswap   %0" : "+r" (_data));
    return _data;
}
# 67 "/usr/include/libkern/_OSByteOrder.h" 2 3 4
# 125 "/usr/include/sys/_endian.h" 2 3 4
# 100 "/usr/include/i386/endian.h" 2 3 4
# 38 "/usr/include/machine/endian.h" 2 3 4
# 194 "/usr/include/sys/wait.h" 2 3 4







union wait {
 int w_status;



 struct {

  unsigned int w_Termsig:7,
    w_Coredump:1,
    w_Retcode:8,
    w_Filler:16;







 } w_T;





 struct {

  unsigned int w_Stopval:8,
    w_Stopsig:8,
    w_Filler:16;






 } w_S;
};
# 254 "/usr/include/sys/wait.h" 3 4

pid_t wait(int *) __asm("_" "wait" );
pid_t waitpid(pid_t, int *, int) __asm("_" "waitpid" );

int waitid(idtype_t, id_t, siginfo_t *, int) __asm("_" "waitid" );


pid_t wait3(int *, int, struct rusage *);
pid_t wait4(pid_t, int *, int, struct rusage *);


# 66 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/alloca.h" 1 3 4
# 35 "/usr/include/alloca.h" 3 4

void *alloca(size_t);

# 68 "/usr/include/stdlib.h" 2 3 4
# 81 "/usr/include/stdlib.h" 3 4
typedef __darwin_ct_rune_t ct_rune_t;




typedef __darwin_rune_t rune_t;






typedef __darwin_wchar_t wchar_t;



typedef struct {
 int quot;
 int rem;
} div_t;

typedef struct {
 long quot;
 long rem;
} ldiv_t;


typedef struct {
 long long quot;
 long long rem;
} lldiv_t;
# 134 "/usr/include/stdlib.h" 3 4
extern int __mb_cur_max;
# 144 "/usr/include/stdlib.h" 3 4

void abort(void) __attribute__((__noreturn__));
int abs(int) __attribute__((__const__));
int atexit(void (*)(void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);

long long
  atoll(const char *);

void *bsearch(const void *, const void *, size_t,
     size_t, int (*)(const void *, const void *));
void *calloc(size_t, size_t);
div_t div(int, int) __attribute__((__const__));
void exit(int) __attribute__((__noreturn__));
void free(void *);
char *getenv(const char *);
long labs(long) __attribute__((__const__));
ldiv_t ldiv(long, long) __attribute__((__const__));

long long
  llabs(long long);
lldiv_t lldiv(long long, long long);

void *malloc(size_t);
int mblen(const char *, size_t);
size_t mbstowcs(wchar_t * , const char * , size_t);
int mbtowc(wchar_t * , const char * , size_t);
int posix_memalign(void **, size_t, size_t);
void qsort(void *, size_t, size_t,
     int (*)(const void *, const void *));
int rand(void);
void *realloc(void *, size_t);
void srand(unsigned);
double strtod(const char *, char **) __asm("_" "strtod" );
float strtof(const char *, char **) __asm("_" "strtof" );
long strtol(const char *, char **, int);
long double
  strtold(const char *, char **) ;

long long
  strtoll(const char *, char **, int);

unsigned long
  strtoul(const char *, char **, int);

unsigned long long
  strtoull(const char *, char **, int);

int system(const char *) __asm("_" "system" );
size_t wcstombs(char * , const wchar_t * , size_t);
int wctomb(char *, wchar_t);


void _Exit(int) __attribute__((__noreturn__));
long a64l(const char *);
double drand48(void);
char *ecvt(double, int, int *, int *);
double erand48(unsigned short[3]);
char *fcvt(double, int, int *, int *);
char *gcvt(double, int, char *);
int getsubopt(char **, char * const *, char **);
int grantpt(int);

char *initstate(unsigned, char *, size_t);



long jrand48(unsigned short[3]);
char *l64a(long);
void lcong48(unsigned short[7]);
long lrand48(void);
char *mktemp(char *);
int mkstemp(char *);
long mrand48(void);
long nrand48(unsigned short[3]);
int posix_openpt(int);
char *ptsname(int);
int putenv(char *) __asm("_" "putenv" );
long random(void);
int rand_r(unsigned *);

char *realpath(const char * , char * ) __asm("_" "realpath" "$DARWIN_EXTSN");



unsigned short
 *seed48(unsigned short[3]);
int setenv(const char *, const char *, int) __asm("_" "setenv" );

void setkey(const char *) __asm("_" "setkey" );



char *setstate(const char *);
void srand48(long);

void srandom(unsigned);



int unlockpt(int);

int unsetenv(const char *) __asm("_" "unsetenv" );






# 1 "/usr/include/machine/types.h" 1 3 4
# 37 "/usr/include/machine/types.h" 3 4
# 1 "/usr/include/i386/types.h" 1 3 4
# 70 "/usr/include/i386/types.h" 3 4
# 1 "/usr/include/i386/_types.h" 1 3 4
# 71 "/usr/include/i386/types.h" 2 3 4







typedef signed char int8_t;

typedef unsigned char u_int8_t;


typedef short int16_t;

typedef unsigned short u_int16_t;


typedef int int32_t;

typedef unsigned int u_int32_t;


typedef long long int64_t;

typedef unsigned long long u_int64_t;


typedef int64_t register_t;






typedef __darwin_intptr_t intptr_t;



typedef unsigned long uintptr_t;




typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;







typedef u_int64_t syscall_arg_t;
# 38 "/usr/include/machine/types.h" 2 3 4
# 256 "/usr/include/stdlib.h" 2 3 4


typedef __darwin_dev_t dev_t;




typedef __darwin_mode_t mode_t;



u_int32_t
  arc4random(void);
void arc4random_addrandom(unsigned char *dat, int datlen);
void arc4random_stir(void);

int atexit_b(void (^)(void));
void *bsearch_b(const void *, const void *, size_t,
     size_t, int (^)(const void *, const void *));



char *cgetcap(char *, const char *, int);
int cgetclose(void);
int cgetent(char **, char **, const char *);
int cgetfirst(char **, char **);
int cgetmatch(const char *, const char *);
int cgetnext(char **, char **);
int cgetnum(char *, const char *, long *);
int cgetset(const char *);
int cgetstr(char *, const char *, char **);
int cgetustr(char *, const char *, char **);

int daemon(int, int) __asm("_" "daemon" "$1050") __attribute__((deprecated,visibility("default")));
char *devname(dev_t, mode_t);
char *devname_r(dev_t, mode_t, char *buf, int len);
char *getbsize(int *, long *);
int getloadavg(double [], int);
const char
 *getprogname(void);

int heapsort(void *, size_t, size_t,
     int (*)(const void *, const void *));

int heapsort_b(void *, size_t, size_t,
     int (^)(const void *, const void *));

int mergesort(void *, size_t, size_t,
     int (*)(const void *, const void *));

int mergesort_b(void *, size_t, size_t,
     int (^)(const void *, const void *));

void psort(void *, size_t, size_t,
     int (*)(const void *, const void *));

void psort_b(void *, size_t, size_t,
     int (^)(const void *, const void *));

void psort_r(void *, size_t, size_t, void *,
     int (*)(void *, const void *, const void *));

void qsort_b(void *, size_t, size_t,
     int (^)(const void *, const void *));

void qsort_r(void *, size_t, size_t, void *,
     int (*)(void *, const void *, const void *));
int radixsort(const unsigned char **, int, const unsigned char *,
     unsigned);
void setprogname(const char *);
int sradixsort(const unsigned char **, int, const unsigned char *,
     unsigned);
void sranddev(void);
void srandomdev(void);
void *reallocf(void *, size_t);

long long
  strtoq(const char *, char **, int);
unsigned long long
  strtouq(const char *, char **, int);

extern char *suboptarg;
void *valloc(size_t);







# 22 "/Users/eroberts/include/cslib.h" 2
# 1 "/usr/lib/gcc/i686-apple-darwin10/4.2.1/include/stddef.h" 1 3 4
# 152 "/usr/lib/gcc/i686-apple-darwin10/4.2.1/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 23 "/Users/eroberts/include/cslib.h" 2
# 45 "/Users/eroberts/include/cslib.h"
typedef enum {false, true} bool;







typedef char *string;
# 62 "/Users/eroberts/include/cslib.h"
typedef void (*proc)();
# 87 "/Users/eroberts/include/cslib.h"
void *getBlock(size_t nbytes);
# 97 "/Users/eroberts/include/cslib.h"
void *getTypedBlock(size_t nbytes, string type);
# 110 "/Users/eroberts/include/cslib.h"
void freeBlock(void *ptr);
# 124 "/Users/eroberts/include/cslib.h"
string getBlockType(void *ptr);
# 133 "/Users/eroberts/include/cslib.h"
void setBlockData(void *ptr, void *value);
# 142 "/Users/eroberts/include/cslib.h"
void *getBlockData(void *ptr);
# 191 "/Users/eroberts/include/cslib.h"
   void error(string msg, ...);
# 9 "Breakout.c" 2
# 1 "/Users/eroberts/include/gevents.h" 1
# 12 "/Users/eroberts/include/gevents.h"
# 1 "/Users/eroberts/include/cslib.h" 1
# 13 "/Users/eroberts/include/gevents.h" 2
# 1 "/Users/eroberts/include/generic.h" 1
# 10 "/Users/eroberts/include/generic.h"
# 1 "/Users/eroberts/include/cmpfn.h" 1
# 23 "/Users/eroberts/include/cmpfn.h"
typedef int (*CompareFn)(const void *p1, const void *p2);
# 32 "/Users/eroberts/include/cmpfn.h"
int intCmpFn(const void *p1, const void *p2);
# 41 "/Users/eroberts/include/cmpfn.h"
int shortCmpFn(const void *p1, const void *p2);
# 50 "/Users/eroberts/include/cmpfn.h"
int longCmpFn(const void *p1, const void *p2);
# 59 "/Users/eroberts/include/cmpfn.h"
int charCmpFn(const void *p1, const void *p2);
# 68 "/Users/eroberts/include/cmpfn.h"
int floatCmpFn(const void *p1, const void *p2);
# 77 "/Users/eroberts/include/cmpfn.h"
int doubleCmpFn(const void *p1, const void *p2);
# 86 "/Users/eroberts/include/cmpfn.h"
int unsignedCmpFn(const void *p1, const void *p2);
# 95 "/Users/eroberts/include/cmpfn.h"
int unsignedShortCmpFn(const void *p1, const void *p2);
# 104 "/Users/eroberts/include/cmpfn.h"
int unsignedLongCmpFn(const void *p1, const void *p2);
# 113 "/Users/eroberts/include/cmpfn.h"
int unsignedCharCmpFn(const void *p1, const void *p2);
# 122 "/Users/eroberts/include/cmpfn.h"
int stringCmpFn(const void *p1, const void *p2);
# 132 "/Users/eroberts/include/cmpfn.h"
int pointerCmpFn(const void *p1, const void *p2);
# 11 "/Users/eroberts/include/generic.h" 2
# 36 "/Users/eroberts/include/generic.h"
typedef union {
    int intRep;
    short shortRep;
    long longRep;
    float floatRep;
    double doubleRep;
    char charRep;
    bool boolRep;
    unsigned unsignedRep;
    unsigned short unsignedShortRep;
    unsigned long unsignedLongRep;
    unsigned char unsignedCharRep;
    void *pointerRep;
} GenericType;
# 58 "/Users/eroberts/include/generic.h"
typedef void (*FetchFn)(va_list args, GenericType *dst);
# 67 "/Users/eroberts/include/generic.h"
typedef void (*StoreFn)(GenericType src, void *dst);







typedef string (*ToStringFn)(GenericType dst);
# 84 "/Users/eroberts/include/generic.h"
int size(void *arg);
# 93 "/Users/eroberts/include/generic.h"
bool isEmptyGeneric(int size, ...);
# 102 "/Users/eroberts/include/generic.h"
void clear(void *arg);
# 111 "/Users/eroberts/include/generic.h"
void *clone(void *arg);
# 122 "/Users/eroberts/include/generic.h"
void *get(void *arg, ...);
# 133 "/Users/eroberts/include/generic.h"
void set(void *arg, ...);
# 145 "/Users/eroberts/include/generic.h"
void put(void *arg, ...);
# 154 "/Users/eroberts/include/generic.h"
bool containsKey(void *arg, void *key);
# 164 "/Users/eroberts/include/generic.h"
bool containsGeneric(int size, ...);
# 175 "/Users/eroberts/include/generic.h"
void add(void *arg, ...);
# 186 "/Users/eroberts/include/generic.h"
void xremove(void *arg, ...);
# 197 "/Users/eroberts/include/generic.h"
void _enqueue(void *arg, ...);
# 206 "/Users/eroberts/include/generic.h"
void *_dequeue(void *arg);
# 215 "/Users/eroberts/include/generic.h"
void *peek(void *arg);
# 224 "/Users/eroberts/include/generic.h"
bool equals(void *s1, void *s2);
# 234 "/Users/eroberts/include/generic.h"
bool isSubset(void *s1, void *s2);
# 243 "/Users/eroberts/include/generic.h"
void *xunion(void *s1, void *s2);
# 252 "/Users/eroberts/include/generic.h"
void *intersection(void *s1, void *s2);
# 261 "/Users/eroberts/include/generic.h"
void *setDifference(void *s1, void *s2);
# 270 "/Users/eroberts/include/generic.h"
double getXGeneric(int size, ...);
# 279 "/Users/eroberts/include/generic.h"
double getYGeneric(int size, ...);
# 288 "/Users/eroberts/include/generic.h"
double getWidthGeneric(int size, ...);
# 297 "/Users/eroberts/include/generic.h"
double getHeightGeneric(int size, ...);
# 306 "/Users/eroberts/include/generic.h"
void setVisible(void *arg, bool flag);
# 315 "/Users/eroberts/include/generic.h"
bool isVisible(void *arg);
# 324 "/Users/eroberts/include/generic.h"
void setColor(void *arg, string color);
# 333 "/Users/eroberts/include/generic.h"
int getTypeSizeForType(string type);
# 342 "/Users/eroberts/include/generic.h"
CompareFn getCompareFnForType(string type);
# 359 "/Users/eroberts/include/generic.h"
FetchFn getFetchFnForType(string type);
# 376 "/Users/eroberts/include/generic.h"
StoreFn getStoreFnForType(string type);
# 386 "/Users/eroberts/include/generic.h"
ToStringFn getToStringFn(string type);
# 14 "/Users/eroberts/include/gevents.h" 2
# 1 "/Users/eroberts/include/gtimer.h" 1
# 19 "/Users/eroberts/include/gtimer.h"
typedef struct GTimerCDT *GTimer;
# 30 "/Users/eroberts/include/gtimer.h"
GTimer newGTimer(double milliseconds);
# 39 "/Users/eroberts/include/gtimer.h"
void freeGTimer(GTimer timer);
# 51 "/Users/eroberts/include/gtimer.h"
void startTimer(GTimer timer);
# 60 "/Users/eroberts/include/gtimer.h"
void stopTimer(GTimer timer);
# 15 "/Users/eroberts/include/gevents.h" 2
# 1 "/Users/eroberts/include/gwindow.h" 1
# 11 "/Users/eroberts/include/gwindow.h"
# 1 "/Users/eroberts/include/gtypes.h" 1
# 20 "/Users/eroberts/include/gtypes.h"
typedef struct {
   double x;
   double y;
} GPoint;
# 32 "/Users/eroberts/include/gtypes.h"
typedef struct {
   double width;
   double height;
} GDimension;
# 44 "/Users/eroberts/include/gtypes.h"
typedef struct {
   double x;
   double y;
   double width;
   double height;
} GRectangle;
# 59 "/Users/eroberts/include/gtypes.h"
GPoint createGPoint(double x, double y);
# 68 "/Users/eroberts/include/gtypes.h"
double getXGPoint(GPoint pt);
# 77 "/Users/eroberts/include/gtypes.h"
double getYGPoint(GPoint pt);
# 87 "/Users/eroberts/include/gtypes.h"
GDimension createGDimension(double width, double height);
# 96 "/Users/eroberts/include/gtypes.h"
double getWidthGDimension(GDimension dim);
# 105 "/Users/eroberts/include/gtypes.h"
double getHeightGDimension(GDimension dim);
# 114 "/Users/eroberts/include/gtypes.h"
GRectangle createGRectangle(double x, double y, double width, double height);
# 123 "/Users/eroberts/include/gtypes.h"
double getXGRectangle(GRectangle r);
# 132 "/Users/eroberts/include/gtypes.h"
double getYGRectangle(GRectangle r);
# 141 "/Users/eroberts/include/gtypes.h"
double getWidthGRectangle(GRectangle r);
# 150 "/Users/eroberts/include/gtypes.h"
double getHeightGRectangle(GRectangle r);
# 159 "/Users/eroberts/include/gtypes.h"
bool isEmptyGRectangle(GRectangle r);
# 168 "/Users/eroberts/include/gtypes.h"
bool containsGRectangle(GRectangle r, GPoint pt);
# 12 "/Users/eroberts/include/gwindow.h" 2



typedef void *GObject;
# 53 "/Users/eroberts/include/gwindow.h"
typedef struct GWindowCDT *GWindow;
# 64 "/Users/eroberts/include/gwindow.h"
GWindow newGWindow(double width, double height);
# 73 "/Users/eroberts/include/gwindow.h"
void closeGWindow(GWindow gw);
# 84 "/Users/eroberts/include/gwindow.h"
void requestFocus(GWindow gw);
# 93 "/Users/eroberts/include/gwindow.h"
void clearGWindow(GWindow gw);
# 102 "/Users/eroberts/include/gwindow.h"
void setVisibleGWindow(GWindow gw, bool flag);
# 111 "/Users/eroberts/include/gwindow.h"
bool isVisibleGWindow(GWindow gw);
# 120 "/Users/eroberts/include/gwindow.h"
void drawLine(GWindow gw, double x0, double y0, double x1, double y1);
# 132 "/Users/eroberts/include/gwindow.h"
GPoint drawPolarLine(GWindow gw, double x, double y, double r, double theta);
# 141 "/Users/eroberts/include/gwindow.h"
void drawOval(GWindow gw, double x, double y, double width, double height);
# 150 "/Users/eroberts/include/gwindow.h"
void fillOval(GWindow gw, double x, double y, double width, double height);
# 159 "/Users/eroberts/include/gwindow.h"
void drawRect(GWindow gw, double x, double y, double width, double height);
# 168 "/Users/eroberts/include/gwindow.h"
void fillRect(GWindow gw, double x, double y, double width, double height);
# 185 "/Users/eroberts/include/gwindow.h"
void setColorGWindow(GWindow gw, string color);
# 197 "/Users/eroberts/include/gwindow.h"
string getColorGWindow(GWindow gw);
# 206 "/Users/eroberts/include/gwindow.h"
double getWidthGWindow(GWindow gw);
# 215 "/Users/eroberts/include/gwindow.h"
double getHeightGWindow(GWindow gw);
# 224 "/Users/eroberts/include/gwindow.h"
void repaint(GWindow gw);
# 233 "/Users/eroberts/include/gwindow.h"
void setWindowTitle(GWindow gw, string title);
# 242 "/Users/eroberts/include/gwindow.h"
string getWindowTitle(GWindow gw);
# 251 "/Users/eroberts/include/gwindow.h"
void draw(GWindow gw, GObject gobj);
# 261 "/Users/eroberts/include/gwindow.h"
void drawAt(GWindow gw, GObject gobj, double x, double y);
# 274 "/Users/eroberts/include/gwindow.h"
void addGWindow(GWindow gw, GObject gobj);
# 284 "/Users/eroberts/include/gwindow.h"
void addAt(GWindow gw, GObject gobj, double x, double y);
# 297 "/Users/eroberts/include/gwindow.h"
void addToRegion(GWindow gw, GObject gobj, string region);
# 306 "/Users/eroberts/include/gwindow.h"
void removeGWindow(GWindow gw, GObject gobj);
# 317 "/Users/eroberts/include/gwindow.h"
GObject getGObjectAt(GWindow gw, double x, double y);
# 332 "/Users/eroberts/include/gwindow.h"
void setRegionAlignment(GWindow gw, string region, string align);
# 342 "/Users/eroberts/include/gwindow.h"
void pause(double milliseconds);
# 16 "/Users/eroberts/include/gevents.h" 2
# 27 "/Users/eroberts/include/gevents.h"
typedef enum {
   ACTION_EVENT = 0x010,
   KEY_EVENT = 0x020,
   TIMER_EVENT = 0x040,
   WINDOW_EVENT = 0x080,
   MOUSE_EVENT = 0x100,
   CLICK_EVENT = 0x200,
   ANY_EVENT = 0x3F0
} EventClassType;







typedef enum {
   WINDOW_CLOSED = WINDOW_EVENT + 1,
   WINDOW_RESIZED = WINDOW_EVENT + 2,
   ACTION_PERFORMED = ACTION_EVENT + 1,
   MOUSE_CLICKED = MOUSE_EVENT + 1,
   MOUSE_PRESSED = MOUSE_EVENT + 2,
   MOUSE_RELEASED = MOUSE_EVENT + 3,
   MOUSE_MOVED = MOUSE_EVENT + 4,
   MOUSE_DRAGGED = MOUSE_EVENT + 5,
   KEY_PRESSED = KEY_EVENT + 1,
   KEY_RELEASED = KEY_EVENT + 2,
   KEY_TYPED = KEY_EVENT + 3,
   TIMER_TICKED = TIMER_EVENT + 1,
} EventType;
# 65 "/Users/eroberts/include/gevents.h"
typedef enum {
   SHIFT_DOWN = 1 << 0,
   CTRL_DOWN = 1 << 1,
   META_DOWN = 1 << 2,
   ALT_DOWN = 1 << 3,
   ALT_GRAPH_DOWN = 1 << 4,
   BUTTON1_DOWN = 1 << 5,
   BUTTON2_DOWN = 1 << 6,
   BUTTON3_DOWN = 1 << 7
} ModifierCodes;







typedef enum {
   BACKSPACE_KEY = 8,
   TAB_KEY = 9,
   ENTER_KEY = 10,
   CLEAR_KEY = 12,
   ESCAPE_KEY = 27,
   PAGE_UP_KEY = 33,
   PAGE_DOWN_KEY = 34,
   END_KEY = 35,
   HOME_KEY = 36,
   LEFT_ARROW_KEY = 37,
   UP_ARROW_KEY = 38,
   RIGHT_ARROW_KEY = 39,
   DOWN_ARROW_KEY = 40,
   F1_KEY = 112,
   F2_KEY = 113,
   F3_KEY = 114,
   F4_KEY = 115,
   F5_KEY = 116,
   F6_KEY = 117,
   F7_KEY = 118,
   F8_KEY = 119,
   F9_KEY = 120,
   F10_KEY = 121,
   F11_KEY = 122,
   F12_KEY = 123,
   DELETE_KEY = 127,
   HELP_KEY = 156
} KeyCodes;
# 142 "/Users/eroberts/include/gevents.h"
typedef struct GEventCDT *GEvent;
# 151 "/Users/eroberts/include/gevents.h"
EventClassType getEventClass(GEvent e);
# 160 "/Users/eroberts/include/gevents.h"
EventType getEventType(GEvent e);
# 174 "/Users/eroberts/include/gevents.h"
double getEventTime(GEvent e);
# 183 "/Users/eroberts/include/gevents.h"
void setEventTime(GEvent e, double time);
# 198 "/Users/eroberts/include/gevents.h"
int getModifiers(GEvent e);
# 207 "/Users/eroberts/include/gevents.h"
void setModifiers(GEvent e, int modifiers);
# 217 "/Users/eroberts/include/gevents.h"
void waitForClick();
# 260 "/Users/eroberts/include/gevents.h"
GEvent waitForEvent(int mask);
# 272 "/Users/eroberts/include/gevents.h"
GEvent getNextEvent(int mask);
# 283 "/Users/eroberts/include/gevents.h"
GEvent newGWindowEvent(EventType type, GWindow gw);
# 292 "/Users/eroberts/include/gevents.h"
GEvent newGActionEvent(EventType type, GObject source, string actionCommand);
# 303 "/Users/eroberts/include/gevents.h"
GEvent newGMouseEvent(EventType type, GWindow gw, double x, double y);
# 314 "/Users/eroberts/include/gevents.h"
GEvent newGMouseEvent(EventType type, GWindow gw, double x, double y);
# 323 "/Users/eroberts/include/gevents.h"
GEvent newGKeyEvent(EventType type, GWindow gw, int keyChar, int keyCode);
# 332 "/Users/eroberts/include/gevents.h"
GEvent newGTimerEvent(EventType type, GTimer timer);
# 341 "/Users/eroberts/include/gevents.h"
void freeEvent(GEvent e);
# 350 "/Users/eroberts/include/gevents.h"
GWindow getGWindow(GEvent e);
# 359 "/Users/eroberts/include/gevents.h"
GObject getSource(GEvent e);
# 368 "/Users/eroberts/include/gevents.h"
string getActionCommand(GEvent e);
# 377 "/Users/eroberts/include/gevents.h"
double getXGEvent(GEvent e);
# 386 "/Users/eroberts/include/gevents.h"
double getYGEvent(GEvent e);
# 399 "/Users/eroberts/include/gevents.h"
char getKeyChar(GEvent e);
# 408 "/Users/eroberts/include/gevents.h"
int getKeyCode(GEvent e);
# 417 "/Users/eroberts/include/gevents.h"
GTimer getGTimer(GEvent e);
# 10 "Breakout.c" 2
# 1 "/Users/eroberts/include/gobjects.h" 1
# 76 "/Users/eroberts/include/gobjects.h"
void freeGObject(GObject gobj);
# 85 "/Users/eroberts/include/gobjects.h"
double getXGObject(GObject gobj);
# 94 "/Users/eroberts/include/gobjects.h"
double getYGObject(GObject gobj);
# 103 "/Users/eroberts/include/gobjects.h"
GPoint getLocation(GObject gobj);
# 112 "/Users/eroberts/include/gobjects.h"
void setLocation(GObject gobj, double x, double y);
# 122 "/Users/eroberts/include/gobjects.h"
void move(GObject gobj, double dx, double dy);
# 132 "/Users/eroberts/include/gobjects.h"
double getWidthGObject(GObject gobj);
# 142 "/Users/eroberts/include/gobjects.h"
double getHeightGObject(GObject gobj);
# 151 "/Users/eroberts/include/gobjects.h"
GDimension getSize(GObject gobj);
# 167 "/Users/eroberts/include/gobjects.h"
GRectangle getBounds(GObject gobj);
# 195 "/Users/eroberts/include/gobjects.h"
void setColorGObject(GObject gobj, string color);
# 208 "/Users/eroberts/include/gobjects.h"
string getColorGObject(GObject gobj);
# 217 "/Users/eroberts/include/gobjects.h"
void setVisibleGObject(GObject gobj, bool flag);
# 226 "/Users/eroberts/include/gobjects.h"
bool isVisibleGObject(GObject gobj);
# 236 "/Users/eroberts/include/gobjects.h"
void sendForward(GObject gobj);
# 248 "/Users/eroberts/include/gobjects.h"
void sendToFront(GObject gobj);
# 258 "/Users/eroberts/include/gobjects.h"
void sendBackward(GObject gobj);
# 270 "/Users/eroberts/include/gobjects.h"
void sendToBack(GObject gobj);
# 279 "/Users/eroberts/include/gobjects.h"
bool containsGObject(GObject gobj, double x, double y);
# 289 "/Users/eroberts/include/gobjects.h"
string getType(GObject gobj);
# 304 "/Users/eroberts/include/gobjects.h"
GObject getParent(GObject gobj);
# 314 "/Users/eroberts/include/gobjects.h"
void setFilled(GObject gobj, bool flag);
# 323 "/Users/eroberts/include/gobjects.h"
bool isFilled(GObject gobj);
# 332 "/Users/eroberts/include/gobjects.h"
void setFillColor(GObject gobj, string color);
# 343 "/Users/eroberts/include/gobjects.h"
string getFillColor(GObject gobj);
# 365 "/Users/eroberts/include/gobjects.h"
typedef GObject GRect;
# 375 "/Users/eroberts/include/gobjects.h"
GRect newGRect(double x, double y, double width, double height);
# 396 "/Users/eroberts/include/gobjects.h"
typedef GObject GOval;
# 406 "/Users/eroberts/include/gobjects.h"
GObject newGOval(double x, double y, double width, double height);
# 424 "/Users/eroberts/include/gobjects.h"
typedef GObject GLine;
# 435 "/Users/eroberts/include/gobjects.h"
GObject newGLine(double x0, double y0, double x1, double y1);
# 447 "/Users/eroberts/include/gobjects.h"
void setStartPoint(GLine line, double x, double y);
# 457 "/Users/eroberts/include/gobjects.h"
void setEndPoint(GLine line, double x, double y);
# 466 "/Users/eroberts/include/gobjects.h"
GPoint getStartPoint(GObject gobj);
# 475 "/Users/eroberts/include/gobjects.h"
GPoint getEndPoint(GObject gobj);
# 497 "/Users/eroberts/include/gobjects.h"
typedef GObject GArc;
# 507 "/Users/eroberts/include/gobjects.h"
GArc newGArc(double x, double y, double width, double height,
                                 double start, double sweep);
# 517 "/Users/eroberts/include/gobjects.h"
void setStartAngle(GArc arc, double start);
# 526 "/Users/eroberts/include/gobjects.h"
double getStartAngle(GArc arc);
# 535 "/Users/eroberts/include/gobjects.h"
void setSweepAngle(GArc arc, double start);
# 544 "/Users/eroberts/include/gobjects.h"
double getSweepAngle(GArc arc);
# 555 "/Users/eroberts/include/gobjects.h"
typedef GObject GCompound;
# 564 "/Users/eroberts/include/gobjects.h"
GObject newGCompound(void);
# 574 "/Users/eroberts/include/gobjects.h"
void addGCompound(GCompound compound, GObject gobj);
# 583 "/Users/eroberts/include/gobjects.h"
typedef enum {
   GARC = 1<<0,
   GCOMPOUND = 1<<1,
   GIMAGE = 1<<2,
   GLABEL = 1<<3,
   GLINE = 1<<4,
   GOVAL = 1<<5,
   GPOLYGON = 1<<6,
   GRECT = 1<<7,
   G3DRECT = 1<<8,
   GROUNDRECT = 1<<9,
   GBUTTON = 1<<10,
   GCHECKBOX = 1<<11,
   GCHOOSER = 1<<12,
   GSLIDER = 1<<13,
   GTEXTFIELD = 1<<14,
} GObjectTypeBits;
# 11 "Breakout.c" 2
# 1 "/Users/eroberts/include/gwindow.h" 1
# 12 "Breakout.c" 2
# 1 "/Users/eroberts/include/random.h" 1
# 21 "/Users/eroberts/include/random.h"
int randomInteger(int low, int high);
# 34 "/Users/eroberts/include/random.h"
double randomReal(double low, double high);
# 47 "/Users/eroberts/include/random.h"
bool randomChance(double p);
# 59 "/Users/eroberts/include/random.h"
void setRandomSeed(int seed);
# 13 "Breakout.c" 2
# 62 "Breakout.c"
void setupBricks(GWindow gw);
string getBrickColor(int row);
void playGame(GWindow gw);
GObject getCollidingObject(GWindow gw, GObject ball);
void playBounceSound();



int main_() {
   GWindow gw;

   gw = newGWindow(400, 600);
   playGame(gw);
   return 0;
}

void setupBricks(GWindow gw) {
   GRect brick;
   int row, col;
   double x, y;

   for (row = 0; row < 10; row++) {
      y = 70 + row * (8 + 4);
      for (col = 0; col < 10; col++) {
         x = 2 + col * ((400 - (10 - 1) * 4) / 10 + 4);
         brick = newGRect(x, y, (400 - (10 - 1) * 4) / 10, 8);
         setFilled(brick, true);
         setColor(brick, getBrickColor(row));
         add(gw, brick);
      }
   }
}

string getBrickColor(int row) {
   switch (row) {
    case 0: case 1: return "RED";
    case 2: case 3: return "ORANGE";
    case 4: case 5: return "YELLOW";
    case 6: case 7: return "GREEN";
    case 8: case 9: return "CYAN";
    default: return "GRAY";
   }
};

void playGame(GWindow gw) {
   double width, height, r, bx, by, px, py, vx, vy;
   int nBricksRemaining, nBallsLeft;
   GObject collider = ((void *)0);
   GOval ball;
   GRect paddle;
   GEvent e;

   setupBricks(gw);
   width = getWidthGeneric(sizeof gw, gw);
   height = getHeightGeneric(sizeof gw, gw);
   r = 10;
   bx = width / 2 - r;
   by = height / 2 - r;
   ball = newGOval(bx, by, 2 * r, 2 * r);
   setFilled(ball, true);
   add(gw, ball);
   px = (width - 60) / 2;
   py = height - 10 - 30;
   paddle = newGRect(px, py, 60, 10);
   setFilled(paddle, true);
   add(gw, paddle);
   nBricksRemaining = 10 * 10;
   nBallsLeft = 3;
   while (nBallsLeft > 0 && nBricksRemaining > 0) {
      waitForClick();
      nBallsLeft--;
      vx = randomReal(1, 2);
      if (randomChance(0.5)) vx = -vx;
      vy = 3.0;
      while (getYGeneric(sizeof ball, ball) < height - r && nBricksRemaining > 0) {
         e = getNextEvent(MOUSE_EVENT);
         if (e != ((void *)0)) {
            if (getEventType(e) == MOUSE_MOVED) {
               px = getXGeneric(sizeof e, e) - 60;
               if (px < 0) px = 0;
               if (px > width - 60) px = width - 60;
               setLocation(paddle, px, py);
            }
         } else {
            move(ball, vx, vy);
fprintf(__stderrp, "ball@(%g,%g) vx = %g\n", getXGeneric(4, ball), getYGeneric(4, ball), vx);
            if (getXGeneric(sizeof ball, ball) < 0 || getXGeneric(sizeof ball, ball) > width - 2 * r) vx = -vx;
            if (getYGeneric(sizeof ball, ball) < 0) vy = -vy;

            if (collider != ((void *)0)) {
               if (false) playBounceSound();
               if (collider == paddle) {
                  vy = -vy;
                  setLocation(ball, getXGeneric(sizeof ball, ball), getYGeneric(sizeof paddle, paddle) - 2 * r);
               } else {
                  xremove(gw, collider);
                  nBricksRemaining--;
                  vy = -vy;
               }
            }
            pause(300.0);
         }
      }
      pause(500.0);
      setLocation(ball, bx, by);
   }
   waitForClick();
}

GObject getCollidingObject(GWindow gw, GObject ball) {
   double x, y, d;
   GObject obj;

   x = getXGeneric(sizeof ball, ball);
   y = getYGeneric(sizeof ball, ball);
   d = 2 * 10;
   obj = getGObjectAt(gw, x, y);
   if (obj == ((void *)0)) obj = getGObjectAt(gw, x + d, y);
   if (obj == ((void *)0)) obj = getGObjectAt(gw, x, y + d);
   if (obj == ((void *)0)) obj = getGObjectAt(gw, x + d, y + d);
   return obj;
}

void playBounceSound() {


}
