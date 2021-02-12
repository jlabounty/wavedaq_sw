/*
 * Definitions for board vendor, type, revision and variant which is
 * given by the first status register at 0x0000 of each WDAQ board
 */

#ifndef __WDAQ_BOARD_ID__
#define __WDAQ_BOARD_ID__

/* Limits */
#define BRD_VENDOR_ID_MAX     2
#define BRD_TYPE_ID_MAX       4
#define BRD_REV_ID_MAX        7

/* Board Type IDs */
#define BRD_VENDOR_ID_UNKNOWN 0
#define BRD_VENDOR_ID_PSI     1
#define BRD_VENDOR_ID_PISA    2

/* Board Type IDs */
#define BRD_TYPE_ID_NONE0     0
#define BRD_TYPE_ID_NONE1     1
#define BRD_TYPE_ID_WDB       2
#define BRD_TYPE_ID_DCB       3
#define BRD_TYPE_ID_TCB       4
#define BRD_TYPE_ID_BLANK   254
#define BRD_TYPE_ID_EMPTY   255


/* DCB Board Revision IDs */
#define DCB_BRD_REV_ID_A      0
#define DCB_BRD_REV_ID_B      1

/* WDB Board Revision IDs */
#define WDB_BRD_REV_ID_C      2
#define WDB_BRD_REV_ID_D      3
#define WDB_BRD_REV_ID_E      4
#define WDB_BRD_REV_ID_F      5
#define WDB_BRD_REV_ID_G      6
#define WDB_BRD_REV_ID_H      7

/* TCB Board Revision IDs */
#define TCB_BRD_REV_ID_1      1
#define TCB_BRD_REV_ID_2      2
#define TCB_BRD_REV_ID_3      3

typedef struct {
   unsigned int vendor_id;
   unsigned int type_id;
   unsigned int rev_id;
   unsigned int variant_id;
} WDAQ_BRD;

#define WDAQ_BRD_VENDOR_NAME const char *wdaq_brd_vendor_name[] = { \
  "UNKNOWN", \
  "PSI", \
  "INFN PISA", \
}

#define WDAQ_BRD_TYPE_NAME const char *wdaq_brd_type_name[] = { \
  "NONE0", \
  "NONE1", \
  "WDB",   \
  "DCB",   \
  "TCB"    \
}

#endif /* __WDAQ_BOARD_ID__ */
