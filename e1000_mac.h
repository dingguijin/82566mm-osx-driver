/*******************************************************************************

  Intel PRO/1000 Linux driver
  Copyright(c) 1999 - 2008 Intel Corporation.

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Contact Information:
  Linux NICS <linux.nics@intel.com>
  e1000-devel Mailing List <e1000-devel@lists.sourceforge.net>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

*******************************************************************************/

#ifndef _E1000_MAC_H_
#define _E1000_MAC_H_

/*
 * Functions that should not be called directly from drivers but can be used
 * by other files in this 'shared code'
 */
void    e1000_init_mac_ops_generic(struct e1000_hw *hw);
SInt32  e1000_blink_led_generic(struct e1000_hw *hw);
SInt32  e1000_check_for_copper_link_generic(struct e1000_hw *hw);
SInt32  e1000_check_for_fiber_link_generic(struct e1000_hw *hw);
SInt32  e1000_check_for_serdes_link_generic(struct e1000_hw *hw);
SInt32  e1000_cleanup_led_generic(struct e1000_hw *hw);
SInt32  e1000_commit_fc_settings_generic(struct e1000_hw *hw);
SInt32  e1000_config_fc_after_link_up_generic(struct e1000_hw *hw);
SInt32  e1000_disable_pcie_master_generic(struct e1000_hw *hw);
SInt32  e1000_force_mac_fc_generic(struct e1000_hw *hw);
SInt32  e1000_get_auto_rd_done_generic(struct e1000_hw *hw);
SInt32  e1000_get_hw_semaphore_generic(struct e1000_hw *hw);
SInt32  e1000_get_speed_and_duplex_copper_generic(struct e1000_hw *hw, UInt16 *speed, UInt16 *duplex);
SInt32  e1000_get_speed_and_duplex_fiber_serdes_generic(struct e1000_hw *hw, UInt16 *speed, UInt16 *duplex);
SInt32  e1000_id_led_init_generic(struct e1000_hw *hw);
SInt32  e1000_led_on_generic(struct e1000_hw *hw);
SInt32  e1000_led_off_generic(struct e1000_hw *hw);
void    e1000_update_mc_addr_list_generic(struct e1000_hw *hw,
	                               UInt8 *mc_addr_list, UInt32 mc_addr_count,
	                               UInt32 rar_used_count, UInt32 rar_count);
SInt32  e1000_poll_fiber_serdes_link_generic(struct e1000_hw *hw);
SInt32  e1000_set_default_fc_generic(struct e1000_hw *hw);
SInt32  e1000_set_fc_watermarks_generic(struct e1000_hw *hw);
SInt32  e1000_setup_fiber_serdes_link_generic(struct e1000_hw *hw);
SInt32  e1000_setup_led_generic(struct e1000_hw *hw);
SInt32  e1000_setup_link_generic(struct e1000_hw *hw);
SInt32  e1000_validate_mdi_setting_generic(struct e1000_hw *hw);
SInt32  e1000_write_8bit_ctrl_reg_generic(struct e1000_hw *hw, UInt32 reg, UInt32 offset, UInt8 data);

UInt32  e1000_hash_mc_addr_generic(struct e1000_hw *hw, UInt8 *mc_addr);

void e1000_clear_hw_cntrs_base_generic(struct e1000_hw *hw);
void e1000_clear_vfta_generic(struct e1000_hw *hw);
void e1000_config_collision_dist_generic(struct e1000_hw *hw);
void e1000_init_rx_addrs_generic(struct e1000_hw *hw, UInt16 rar_count);
void e1000_mta_set_generic(struct e1000_hw *hw, UInt32 hash_value);
void e1000_pcix_mmrbc_workaround_generic(struct e1000_hw *hw);
void e1000_put_hw_semaphore_generic(struct e1000_hw *hw);
void e1000_rar_set_generic(struct e1000_hw *hw, UInt8 *addr, UInt32 index);
SInt32  e1000_check_alt_mac_addr_generic(struct e1000_hw *hw);
void e1000_remove_device_generic(struct e1000_hw *hw);
void e1000_reset_adaptive_generic(struct e1000_hw *hw);
void e1000_set_pcie_no_snoop_generic(struct e1000_hw *hw, UInt32 no_snoop);
void e1000_update_adaptive_generic(struct e1000_hw *hw);
void e1000_write_vfta_generic(struct e1000_hw *hw, UInt32 offset, UInt32 value);

#endif
