#define DMA_PSCHED_EN_IOCTL         _IO('D', 'e')
#define DMA_PSCHED_DIS_IOCTL        _IO('D', 'd')
#define DMA_PSCHED_EN_SLOT_IOCTL   _IOW('D', 's', int32_t*)

struct dma_buf{
        char *data;         /* pointer to data */
        unsigned int len;   /* #bytes of data */
        unsigned char slot;
        unsigned char win;
};
