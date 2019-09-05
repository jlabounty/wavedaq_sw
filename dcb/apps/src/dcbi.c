#include "system.h"
#include "sc_io.h"
#include "xfs_printf.h"
#include "utilities.h"
#include "dbg.h"

int main()
{
  /* Set default debug level */
  set_dbg_level(DBG_LEVEL_SPAM);

  init_system();

  if (DBG_INIT)
  {
    xfs_printf("\r\n");
    xfs_printf("---------------------------------------------------------\r\n");
    xfs_printf("-- WDAQ DCB Firmware Initialization                    --\r\n");
    xfs_printf("---------------------------------------------------------\r\n\r\n");
    xfs_printf("---------------------------------------------------------\r\n");
    xfs_printf("-- Version Information:\r\n");
    print_sys_info();
    xfs_printf("---------------------------------------------------------\r\n\r\n");
  }

  /* Initialization done */
  /* Set SW state ready to signal normal operation on LED */
//  emio_set_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_PIN);
  emio_set_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_SW_READY_PIN);

  return 0;
}