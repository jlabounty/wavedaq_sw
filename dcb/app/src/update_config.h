/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e
 *  Created :  19.09.2014 13:45:08
 *
 *  Description :  Updating external devices via serial protocols if corresponding
 *                 register bank settings have changed.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __UPDATE_CONFIG_H__
#define __UPDATE_CONFIG_H__

/***************************** Include Files *******************************/

/************************** Function Prototypes ****************************/

/* Update Configuration functions */
int auto_update_configurations();
int trigger_update_configurations();
int update_lmk_ch(unsigned int mod_reg);
int update_lmk();

#endif /** __UPDATE_CONFIG_H__ */
