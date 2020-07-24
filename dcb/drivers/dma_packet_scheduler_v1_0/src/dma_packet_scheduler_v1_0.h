/* Magic number is 'D' */
#define DPS_IOC_MAGIC   'k'

#define DPS_IP_DISABLE   0
#define DPS_IP_ENABLE    1

/*
 * S means "Set" through a ptr,
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": switch G and S atomically
 * H means "sHift": switch T and Q atomically
 */
#define DPS_IOCT_EN          _IOW(DPS_IOC_MAGIC, 0, u_int32_t)
#define DPS_IOCT_SLOT_EN     _IOW(DPS_IOC_MAGIC, 1, u_int32_t)
#define DPS_IOCT_FREE_BUF     _IO(DPS_IOC_MAGIC, 2)
#define DPS_IOCQ_WINSIZE     _IOR(DPS_IOC_MAGIC, 3, u_int32_t)
#define DPS_IOCQ_NOWINDOWS   _IOR(DPS_IOC_MAGIC, 4, u_int32_t)
#define DPS_IOCQ_BUFSIZE     _IOR(DPS_IOC_MAGIC, 5, u_int32_t)

#define DPS_IOC_MAXNR   7

/*
struct dma_buf{
        char *data;
        unsigned int len;
        unsigned char slot;
        unsigned char win;
};
*/
