/*
 * Copyright (c) 2008 Guijin Ding. All rights reserved.
 *
 * Guijin Ding
 * dingguijin@gmail.com
 *
 * Intel82566MM.h
 *
 */

#ifndef __INTEL82566MM_H__
#define __INTEL82566MM_H__

#define MBit 1000000

enum {
	eePowerStateOff = 0,
	eePowerStateOn,
	eePowerStateCount
};

enum {
	kFiveSeconds = 5000000
};


enum
{
	MEDIUM_INDEX_AUTO = 0,
	MEDIUM_INDEX_10HD,
	MEDIUM_INDEX_10FD,
	MEDIUM_INDEX_100HD,
	MEDIUM_INDEX_100FD,
	MEDIUM_INDEX_1000FD,
	MEDIUM_INDEX_COUNT
};

enum 
{
	kActivationLevelNone = 0,  /* adapter shut off */
	kActivationLevelKDP,       /* adapter partially up to support KDP */
	kActivationLevelBSD        /* adapter fully up to support KDP and BSD */
};


class Intel82566MM: public IOEthernetController
{
	
	OSDeclareDefaultStructors(Intel82566MM);
	
public:
	// --------------------------------------------------
	// IOService (or its superclass) methods.
	// --------------------------------------------------
	
	virtual bool start(IOService * provider);
	virtual void stop(IOService * provider);
	virtual bool init(OSDictionary *properties);
	virtual void free();

	// --------------------------------------------------
	// Power Management Support
	// --------------------------------------------------
	virtual IOReturn registerWithPolicyMaker(IOService* policyMaker);
                 
	// --------------------------------------------------
	// IONetworkController methods.
	// --------------------------------------------------
	
	virtual IOReturn enable(IONetworkInterface * netif);
	virtual IOReturn disable(IONetworkInterface * netif);
	
	virtual UInt32 outputPacket(mbuf_t m, void * param);
	
	virtual void getPacketBufferConstraints(IOPacketBufferConstraints * constraints) const;
	
	virtual IOOutputQueue * createOutputQueue();
	
	virtual const OSString * newVendorString() const;
	virtual const OSString * newModelString() const;
	
	virtual IOReturn selectMedium(const IONetworkMedium * medium);
	virtual bool configureInterface(IONetworkInterface * interface);
	
	virtual bool createWorkLoop();
	virtual IOWorkLoop * getWorkLoop() const;
	
	//-----------------------------------------------------------------------
	// Methods inherited from IOEthernetController.
	//-----------------------------------------------------------------------
	
	virtual IOReturn getHardwareAddress(IOEthernetAddress * addr);
	virtual IOReturn setHardwareAddress(const IOEthernetAddress * addr);
	virtual IOReturn setPromiscuousMode(bool active);
	virtual IOReturn setMulticastMode(bool active);
	virtual IOReturn setMulticastList(IOEthernetAddress * addrs, UInt32 count);
	virtual IOReturn getChecksumSupport(UInt32 *checksumMask, UInt32 checksumFamily, bool isOutput);
	
private:
	IOWorkLoop * workLoop;
	IOPCIDevice * pciDevice;
	OSDictionary * mediumDict;
	IONetworkMedium * mediumTable[MEDIUM_INDEX_COUNT];
	IOOutputQueue * transmitQueue;

	IOInterruptEventSource * interruptSource;
	IOTimerEventSource * watchdogSource;

	IOEthernetInterface * netif;
	IONetworkStats * netStats;
	IOEthernetStats * etherStats;
    
	IOMemoryMap * csrPCIAddress;
	IOMemoryMap * flashPCIAddress;
	IOVirtualAddress csrCPUAddress;
	IOVirtualAddress flashCPUAddress;
	
	IOMbufNaturalMemoryCursor * rxMbufCursor;
	IOMbufNaturalMemoryCursor * txMbufCursor;
	
	bool interruptEnabled;
	bool enabledForNetif;
	UInt32 preLinkStatus;
	
	struct e1000_adapter adapter;
	
	
private:
	void interruptOccurred(IOInterruptEventSource * src);
	void timeoutOccurred(IOTimerEventSource* src);
	bool addNetworkMedium(UInt32 type, UInt32 bps, UInt32 index);
	
	SInt32 e1000_read_pcie_cap_reg(struct e1000_hw *hw, UInt32 reg, UInt16 *value);
	
	void e1000_print_link_info();
	void e1000_free_rx_resources();
	void e1000_clean_rx_ring();
	void e1000_free_tx_resources();
	void e1000_clean_tx_ring();
	void e1000_reset();
	bool e1000_has_link();
	void e1000e_enable_receives();
	bool e1000_clean_tx_irq();
	bool e1000_clean_rx_irq();
	void e1000_alloc_rx_buffers();
	int  e1000_desc_unused(struct e1000_ring *ring);
	void e1000_configure_rx();
	void e1000_setup_rctl();
	void e1000_configure_tx();
	SInt32 e1000_setup_ring_resources(struct e1000_ring* ring);
	bool e1000_set_multi(IOEthernetAddress * addrs, UInt32 count);
	bool e1000_tx_csum(mbuf_t skb);
	
public:
	static void interruptHandler(OSObject * target,
				     IOInterruptEventSource * src,
				     int count );
	
	static bool interruptFilter(OSObject * target ,
				    IOFilterInterruptEventSource * src);
	
	static void timeoutHandler(OSObject * target, IOTimerEventSource * src);
	UInt32 interruptReason;

};


#endif //__INTEL82566MM_H__
