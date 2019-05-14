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

#include "e1000_hw.h"

SInt32 e1000_get_bus_info_pcie_generic(struct e1000_hw *hw)
{
	struct e1000_bus_info *bus = &hw->bus;
	UInt32 status;
	UInt16 pcie_link_status, pci_header_type;
	
	e_debug("e1000_get_bus_info_pcie_generic");
	
	bus->type = e1000_bus_type_pci_express;
	bus->speed = e1000_bus_speed_2500;

	/*
	ret_val = e1000_read_pcie_cap_reg(hw,
	                                  PCIE_LINK_STATUS,
	                                  &pcie_link_status);
	*/
	pcie_link_status = hw->pcie_link_status;

	if (pcie_link_status == 0)
		bus->width = e1000_bus_width_unknown;
	else
		bus->width = (e1000_bus_width)((pcie_link_status &
		                                PCIE_LINK_WIDTH_MASK) >>
		                               PCIE_LINK_WIDTH_SHIFT);
	
	pci_header_type = hw->pci_header_type;
	
	if (pci_header_type & PCI_HEADER_TYPE_MULTIFUNC) {
		status = E1000_READ_REG(hw, E1000_STATUS);
		bus->func = (status & E1000_STATUS_FUNC_MASK)
			>> E1000_STATUS_FUNC_SHIFT;
	} else {
		bus->func = 0;
	}
	
	return E1000_SUCCESS;
}
