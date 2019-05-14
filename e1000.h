#ifndef _E1000_H_
#define _E1000_H_

#include <sys/kpi_mbuf.h>
#include "e1000_hw.h"

#define E1000_MAX_INTR 10

/* Tx/Rx descriptor defines */
#define E1000_DEFAULT_TXD		256
#define E1000_MAX_TXD			4096
#define E1000_MIN_TXD			80

#define E1000_DEFAULT_RXD		256
#define E1000_MAX_RXD			4096
#define E1000_MIN_RXD			80

#define E1000_MIN_ITR_USECS		10 /* 100000 irq/sec */
#define E1000_MAX_ITR_USECS		10000 /* 100    irq/sec */

/* Early Receive defines */
#define E1000_ERT_2048			0x100

#define E1000_FC_PAUSE_TIME		0x0680 /* 858 usec */

/* How many Tx Descriptors do we need to call netif_wake_queue ? */
/* How many Rx Buffers do we bundle into one write to the hardware ? */
#define E1000_RX_BUFFER_WRITE		16 /* Must be power of 2 */

#define AUTO_ALL_MODES			0
#define E1000_EEPROM_APME		0x0400

#define E1000_MNG_VLAN_NONE		(-1)


/* hardware capability, feature, and workaround flags */
#define FLAG_HAS_AMT                      (1 << 0)
#define FLAG_HAS_FLASH                    (1 << 1)
#define FLAG_HAS_HW_VLAN_FILTER           (1 << 2)
#define FLAG_HAS_WOL                      (1 << 3)
#define FLAG_HAS_ERT                      (1 << 4)
#define FLAG_HAS_CTRLEXT_ON_LOAD          (1 << 5)
#define FLAG_HAS_SWSM_ON_LOAD             (1 << 6)
#define FLAG_HAS_JUMBO_FRAMES             (1 << 7)
#define FLAG_HAS_ASPM                     (1 << 8)
#define FLAG_IS_ICH                       (1 << 9)
#define FLAG_HAS_MSIX                     (1 << 10)
#define FLAG_HAS_SMART_POWER_DOWN         (1 << 11)
#define FLAG_IS_QUAD_PORT_A               (1 << 12)
#define FLAG_IS_QUAD_PORT                 (1 << 13)
#define FLAG_TIPG_MEDIUM_FOR_80003ESLAN   (1 << 14)
#define FLAG_APME_IN_WUC                  (1 << 15)
#define FLAG_APME_IN_CTRL3                (1 << 16)
#define FLAG_APME_CHECK_PORT_B            (1 << 17)
#define FLAG_DISABLE_FC_PAUSE_TIME        (1 << 18)
#define FLAG_NO_WAKE_UCAST                (1 << 19)
#define FLAG_MNG_PT_ENABLED               (1 << 20)
#define FLAG_RESET_OVERWRITES_LAA         (1 << 21)
#define FLAG_TARC_SPEED_MODE_BIT          (1 << 22)
#define FLAG_TARC_SET_BIT_ZERO            (1 << 23)
#define FLAG_RX_NEEDS_RESTART             (1 << 24)
#define FLAG_LSC_GIG_SPEED_DROP           (1 << 25)
#define FLAG_SMART_POWER_DOWN             (1 << 26)
#define FLAG_MSI_ENABLED                  (1 << 27)
#define FLAG_RX_CSUM_ENABLED              (1 << 28)
#define FLAG_TSO_FORCE                    (1 << 29)
#define FLAG_MSI_TEST_FAILED              (1 << 30)
#define FLAG_RX_RESTART_NOW               (1 << 31)


#define NUM_RING_FRAME                    256
#define SIZE_RING_DESC                    PAGE_SIZE
#define MAX_TX_SIZE                       (1 << 14)
#define MAX_RX_SIZE                       1524

/*
 * wrappers around a pointer to a socket buffer,
 * so a DMA handle can be stored along with the buffer
 */
struct e1000_buffer {
	mbuf_t skb;
	UInt32 next_to_watch;
};

struct e1000_ring {
	void* desc;			/* pointer to ring memory  */
	IOPhysicalAddress dma;		/* phys address of ring    */
	
	UInt16 next_to_use;
	UInt16 next_to_clean;
	
	UInt16 head;                   /* register offset */
	UInt16 tail;                   /* register offset */
	
	/* array of buffer information structs */
	struct e1000_buffer buffer_info[NUM_RING_FRAME];
};


/* board specific private data structure */
struct e1000_adapter {
	
	const struct e1000_info *ei;

	UInt32 bd_number;
	UInt32 rx_buffer_len;
	UInt16 mng_vlan_id;
	UInt16 link_speed;
	UInt16 link_duplex;

	/* track device up/down/testing state */
	unsigned long state;
	
	/*
	 * Tx
	 */
	struct e1000_ring tx_ring;
	
	unsigned long tx_queue_len;
	unsigned int restart_queue;
	UInt32 txd_cmd;

	
	/* Tx stats */
	UInt64 tpt_old;
	UInt64 colc_old;
	UInt32 gotc;
	UInt64 gotc_old;
	UInt32 tx_timeout_count;
	UInt32 tx_fifo_head;
	UInt32 tx_head_addr;
	UInt32 tx_fifo_size;
	UInt32 tx_dma_failed;

	/*
	 * Rx
	 */
	struct e1000_ring rx_ring;
	
	UInt32 rx_int_delay;
	UInt32 rx_abs_int_delay;

	/* Rx stats */
	UInt64 hw_csum_err;
	UInt64 hw_csum_good;
	UInt64 rx_hdr_split;
	UInt32 gorc;
	UInt64 gorc_old;
	UInt32 alloc_rx_buff_failed;
	UInt32 rx_dma_failed;

	UInt16 rx_ps_bsize0;
	UInt32 max_frame_size;
	UInt32 min_frame_size;

	/* structs defined in e1000_hw.h */
	struct e1000_hw hw;
	struct e1000_hw_stats stats;
	struct e1000_phy_info phy_info;
	struct e1000_phy_stats phy_stats;

	UInt32 msg_enable;
	UInt32 eeprom_wol;
	UInt32 wol;
	UInt32 pba;

	bool fc_autoneg;

	unsigned long led_status;

	unsigned int flags;
	UInt32 *config_space;
	
};

struct e1000_info {
        e1000_mac_type          mac;
        unsigned int            flags;
        UInt32                  pba;
        void                    (*init_ops)(struct e1000_hw *);
};

void e1000_init_function_pointers_ich8lan(struct e1000_hw *hw);
void e1000_init_function_pointers_82571(struct e1000_hw *hw);
void e1000_init_function_pointers_80003es2lan(struct e1000_hw *hw);
SInt32 e1000_get_bus_info_pcie_generic(struct e1000_hw *hw);

#endif /* __E1000_H__ */
