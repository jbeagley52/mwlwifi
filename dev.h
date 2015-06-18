/*
 * Copyright (C) 2006-2015, Marvell International Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/* Description:  This file defines device related information.
 */

#ifndef _mwl_dev_h_
#define _mwl_dev_h_

#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/firmware.h>
#include <linux/delay.h>
#include <linux/bitops.h>
#include <net/mac80211.h>

/* Map to 0x80000000 (Bus control) on BAR0 */
#define MACREG_REG_H2A_INTERRUPT_EVENTS      0x00000C18 /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_CAUSE       0x00000C1C /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_MASK        0x00000C20 /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_CLEAR_SEL   0x00000C24 /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_STATUS_MASK 0x00000C28 /* (From host to ARM) */

#define MACREG_REG_A2H_INTERRUPT_EVENTS      0x00000C2C /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_CAUSE       0x00000C30 /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_MASK        0x00000C34 /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_CLEAR_SEL   0x00000C38 /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_STATUS_MASK 0x00000C3C /* (From ARM to host) */

/* Map to 0x80000000 on BAR1 */
#define MACREG_REG_GEN_PTR                  0x00000C10
#define MACREG_REG_INT_CODE                 0x00000C14

/* Bit definitio for MACREG_REG_A2H_INTERRUPT_CAUSE (A2HRIC) */
#define MACREG_A2HRIC_BIT_TX_DONE           BIT(0)
#define MACREG_A2HRIC_BIT_RX_RDY            BIT(1)
#define MACREG_A2HRIC_BIT_OPC_DONE          BIT(2)
#define MACREG_A2HRIC_BIT_MAC_EVENT         BIT(3)
#define MACREG_A2HRIC_BIT_RX_PROBLEM        BIT(4)
#define MACREG_A2HRIC_BIT_RADIO_OFF         BIT(5)
#define MACREG_A2HRIC_BIT_RADIO_ON          BIT(6)
#define MACREG_A2HRIC_BIT_RADAR_DETECT      BIT(7)
#define MACREG_A2HRIC_BIT_ICV_ERROR         BIT(8)
#define MACREG_A2HRIC_BIT_WEAKIV_ERROR      BIT(9)
#define MACREG_A2HRIC_BIT_QUEUE_EMPTY       BIT(10)
#define MACREG_A2HRIC_BIT_QUEUE_FULL        BIT(11)
#define MACREG_A2HRIC_BIT_CHAN_SWITCH       BIT(12)
#define MACREG_A2HRIC_BIT_TX_WATCHDOG       BIT(13)
#define MACREG_A2HRIC_BA_WATCHDOG           BIT(14)
/* 15 taken by ISR_TXACK */
#define MACREG_A2HRIC_BIT_SSU_DONE          BIT(16)
#define MACREG_A2HRIC_CONSEC_TXFAIL         BIT(17)

#define ISR_SRC_BITS        (MACREG_A2HRIC_BIT_RX_RDY | \
			     MACREG_A2HRIC_BIT_TX_DONE | \
			     MACREG_A2HRIC_BIT_OPC_DONE | \
			     MACREG_A2HRIC_BIT_MAC_EVENT | \
			     MACREG_A2HRIC_BIT_WEAKIV_ERROR | \
			     MACREG_A2HRIC_BIT_ICV_ERROR | \
			     MACREG_A2HRIC_BIT_SSU_DONE | \
			     MACREG_A2HRIC_BIT_RADAR_DETECT | \
			     MACREG_A2HRIC_BIT_CHAN_SWITCH | \
			     MACREG_A2HRIC_BIT_TX_WATCHDOG | \
			     MACREG_A2HRIC_BIT_QUEUE_EMPTY | \
			     MACREG_A2HRIC_BA_WATCHDOG | \
			     MACREG_A2HRIC_CONSEC_TXFAIL)

#define MACREG_A2HRIC_BIT_MASK      ISR_SRC_BITS

/* Bit definitio for MACREG_REG_H2A_INTERRUPT_CAUSE (H2ARIC) */
#define MACREG_H2ARIC_BIT_PPA_READY         BIT(0)
#define MACREG_H2ARIC_BIT_DOOR_BELL         BIT(1)
#define MACREG_H2ARIC_BIT_PS                BIT(2)
#define MACREG_H2ARIC_BIT_PSPOLL            BIT(3)
#define ISR_RESET                           BIT(15)
#define ISR_RESET_AP33                      BIT(26)

/* Data descriptor related constants */
#define EAGLE_RXD_CTRL_DRIVER_OWN           0x00
#define EAGLE_RXD_CTRL_DMA_OWN              0x80

#define EAGLE_RXD_STATUS_OK                 0x01

#define EAGLE_TXD_STATUS_IDLE               0x00000000
#define EAGLE_TXD_STATUS_OK                 0x00000001
#define EAGLE_TXD_STATUS_FW_OWNED           0x80000000

/* Antenna control */
#define ANTENNA_TX_4_AUTO                   0
#define ANTENNA_TX_2                        3
#define ANTENNA_RX_4_AUTO                   0
#define ANTENNA_RX_2                        2

/* Band related constants */
#define BAND_24_CHANNEL_NUM                 14
#define BAND_24_RATE_NUM                    13
#define BAND_50_CHANNEL_NUM                 24
#define BAND_50_RATE_NUM                    8

/* vif and station */
#define NUM_WEP_KEYS                        4
#define MWL_MAX_TID                         8
#define MWL_AMSDU_SIZE_4K                   0
#define MWL_AMSDU_SIZE_8K                   1

/* power init */
#define MWL_POWER_INIT_1                    1
#define MWL_POWER_INIT_2                    2

enum {
	MWL8864 = 0,
	MWL8897,
	MWLUNKNOWN,
};

enum {
	AP_MODE_11AC = 0x10,         /* generic 11ac indication mode */
	AP_MODE_2_4GHZ_11AC_MIXED = 0x17,
};

enum {
	AMPDU_NO_STREAM,
	AMPDU_STREAM_NEW,
	AMPDU_STREAM_IN_PROGRESS,
	AMPDU_STREAM_ACTIVE,
};

struct mwl_chip_info {
	char *part_name;
	char *fw_image;
};

struct mwl_tx_pwr_tbl {
	u8 channel;
	u8 setcap;
	u16 tx_power[SYSADPT_TX_POWER_LEVEL_TOTAL];
	u8 cdd;                      /* 0: off, 1: on */
	u16 txantenna2;
};

struct mwl_hw_data {
	u32 fw_release_num;          /* MajNbr:MinNbr:SubMin:PatchLevel */
	u8 hw_version;               /* plain number indicating version */
	u8 host_interface;           /* plain number of interface       */
	u16 max_num_tx_desc;         /* max number of TX descriptors    */
	u16 max_num_mc_addr;         /* max number multicast addresses  */
	u16 num_antennas;            /* number antennas used            */
	u16 region_code;             /* region (eg. 0x10 for USA FCC)   */
	unsigned char mac_addr[ETH_ALEN]; /* well known -> AA:BB:CC:DD:EE:FF */
};

#define MWL_TX_RATE_FORMAT_MASK       0x00000003
#define MWL_TX_RATE_BANDWIDTH_MASK    0x00000030
#define MWL_TX_RATE_BANDWIDTH_SHIFT   4
#define MWL_TX_RATE_SHORTGI_MASK      0x00000040
#define MWL_TX_RATE_SHORTGI_SHIFT     6
#define MWL_TX_RATE_RATEIDMCS_MASK    0x00007F00
#define MWL_TX_RATE_RATEIDMCS_SHIFT   8

struct mwl_tx_desc {
	u8 data_rate;
	u8 tx_priority;
	__le16 qos_ctrl;
	__le32 pkt_ptr;
	__le16 pkt_len;
	u8 dest_addr[ETH_ALEN];
	__le32 pphys_next;
	__le32 sap_pkt_info;
	__le32 rate_info;
	u8 type;
	u8 xmit_control;     /* bit 0: use rateinfo, bit 1: disable ampdu */
	__le16 reserved;
	__le32 tcpack_sn;
	__le32 tcpack_src_dst;
	struct sk_buff *psk_buff;
	struct mwl_tx_desc *pnext;
	u8 reserved1[2];
	u8 packet_info;
	u8 packet_id;
	__le16 packet_len_and_retry;
	__le16 packet_rate_info;
	u8 *sta_info;
	__le32 status;
} __packed;

#define MWL_RX_RATE_FORMAT_MASK       0x0007
#define MWL_RX_RATE_NSS_MASK          0x0018
#define MWL_RX_RATE_NSS_SHIFT         3
#define MWL_RX_RATE_BW_MASK           0x0060
#define MWL_RX_RATE_BW_SHIFT          5
#define MWL_RX_RATE_GI_MASK           0x0080
#define MWL_RX_RATE_GI_SHIFT          7
#define MWL_RX_RATE_RT_MASK           0xFF00
#define MWL_RX_RATE_RT_SHIFT          8

struct mwl_rx_desc {
	__le16 pkt_len;              /* total length of received data      */
	__le16 rate;                 /* receive rate information           */
	__le32 pphys_buff_data;      /* physical address of payload data   */
	__le32 pphys_next;           /* physical address of next RX desc   */
	__le16 qos_ctrl;             /* received QosCtrl field variable    */
	__le16 ht_sig2;              /* like name states                   */
	__le32 hw_rssi_info;
	__le32 hw_noise_floor_info;
	u8 noise_floor;
	u8 reserved[3];
	u8 rssi;                     /* received signal strengt indication */
	u8 status;                   /* status field containing USED bit   */
	u8 channel;                  /* channel this pkt was received on   */
	u8 rx_control;               /* the control element of the desc    */
	/* above are 32bits aligned and is same as FW, RxControl put at end
	 * for sync
	 */
	struct sk_buff *psk_buff;    /* associated sk_buff for Linux       */
	void *pbuff_data;            /* virtual address of payload data    */
	struct mwl_rx_desc *pnext;   /* virtual address of next RX desc    */
} __packed;

struct mwl_desc_data {
	dma_addr_t pphys_tx_ring;          /* ptr to first TX desc (phys.)    */
	struct mwl_tx_desc *ptx_ring;      /* ptr to first TX desc (virt.)    */
	struct mwl_tx_desc *pnext_tx_desc; /* next TX desc that can be used   */
	struct mwl_tx_desc *pstale_tx_desc;/* the staled TX descriptor        */
	dma_addr_t pphys_rx_ring;          /* ptr to first RX desc (phys.)    */
	struct mwl_rx_desc *prx_ring;      /* ptr to first RX desc (virt.)    */
	struct mwl_rx_desc *pnext_rx_desc; /* next RX desc that can be used   */
	unsigned int wcb_base;             /* FW base offset for registers    */
	unsigned int rx_desc_write;        /* FW descriptor write position    */
	unsigned int rx_desc_read;         /* FW descriptor read position     */
	unsigned int rx_buf_size;          /* length of the RX buffers        */
} __packed;

struct mwl_ampdu_stream {
	struct ieee80211_sta *sta;
	u8 tid;
	u8 state;
	u8 idx;
};

struct mwl_priv {
	struct ieee80211_hw *hw;
	const struct firmware *fw_ucode;
	int chip_type;

	struct device_node *dt_node;
	struct device_node *pwr_node;
	bool disable_2g;
	bool disable_5g;
	int antenna_tx;
	int antenna_rx;

	struct mwl_tx_pwr_tbl tx_pwr_tbl[SYSADPT_MAX_NUM_CHANNELS];
	u32 cdd;                     /* 0: off, 1: on */
	u16 txantenna2;
	u8 powinited;
	u16 max_tx_pow[SYSADPT_TX_POWER_LEVEL_TOTAL]; /* max tx power (dBm) */
	u16 target_powers[SYSADPT_TX_POWER_LEVEL_TOTAL]; /* target powers   */
	u8 cal_tbl[200];

	struct pci_dev *pdev;
	void *iobase0;               /* MEM Base Address Register 0  */
	void *iobase1;               /* MEM Base Address Register 1  */
	u32 next_bar_num;

	spinlock_t fwcmd_lock;       /* for firmware command         */
	unsigned short *pcmd_buf;    /* pointer to CmdBuf (virtual)  */
	dma_addr_t pphys_cmd_buf;    /* pointer to CmdBuf (physical) */
	bool in_send_cmd;

	int irq;
	struct mwl_hw_data hw_data;  /* Adapter HW specific info     */

	/* various descriptor data */
	spinlock_t tx_desc_lock;     /* for tx descriptor data       */
	struct mwl_desc_data desc_data[SYSADPT_NUM_OF_DESC_DATA];
	struct sk_buff_head txq[SYSADPT_NUM_OF_DESC_DATA];
	struct sk_buff_head delay_q;
	/* number of descriptors owned by fw at any one time */
	int fw_desc_cnt[SYSADPT_NUM_OF_DESC_DATA];

	struct tasklet_struct tx_task;
	struct tasklet_struct rx_task;
	int txq_limit;
	bool is_tx_schedule;
	int recv_limit;
	bool is_rx_schedule;
	s8 noise;                    /* Most recently reported noise in dBm */
	struct ieee80211_supported_band band_24;
	struct ieee80211_channel channels_24[BAND_24_CHANNEL_NUM];
	struct ieee80211_rate rates_24[BAND_24_RATE_NUM];
	struct ieee80211_supported_band band_50;
	struct ieee80211_channel channels_50[BAND_50_CHANNEL_NUM];
	struct ieee80211_rate rates_50[BAND_50_RATE_NUM];

	u32 ap_macids_supported;
	u32 sta_macids_supported;
	u32 macids_used;
	spinlock_t vif_lock;         /* for private interface info   */
	struct list_head vif_list;   /* List of interfaces.          */
	u32 running_bsses;           /* bitmap of running BSSes      */

	spinlock_t sta_lock;         /* for private sta info         */
	struct list_head sta_list;   /* List of stations             */

	bool radio_on;
	bool radio_short_preamble;
	bool wmm_enabled;
	struct ieee80211_tx_queue_params wmm_params[SYSADPT_TX_WMM_QUEUES];

	/* Ampdu stream information */
	u8 num_ampdu_queues;
	spinlock_t stream_lock;      /* for ampdu stream             */
	struct mwl_ampdu_stream ampdu[SYSADPT_TX_AMPDU_QUEUES];
	struct work_struct watchdog_ba_handle;
};

struct beacon_info {
	bool valid;
	u16 cap_info;
	u8 b_rate_set[SYSADPT_MAX_DATA_RATES_G];
	u8 op_rate_set[SYSADPT_MAX_DATA_RATES_G];
	u16 ie_wmm_len;               /* Keep WMM IE */
	u8 *ie_wmm_ptr;
	u16 ie_rsn_len;               /* Keep WPA IE */
	u8 *ie_rsn_ptr;
	u16 ie_rsn48_len;             /* Keep WPA2 IE */
	u8 *ie_rsn48_ptr;
	u16 ie_ht_len;                /* Keep HT IE */
	u8 *ie_ht_ptr;
	u8 ie_list_ht[148];
	u16 ie_vht_len;               /* Keep VHT IE */
	u8 *ie_vht_ptr;
	u8 ie_list_vht[24];
};

struct mwl_vif {
	struct list_head list;
	struct ieee80211_vif *vif;
	int macid;       /* Firmware macid for this vif.  */
	u16 seqno;       /* Non AMPDU sequence number assigned by driver.  */
	struct {         /* Saved WEP keys */
		u8 enabled;
		u8 key[sizeof(struct ieee80211_key_conf) + WLAN_KEY_LEN_WEP104];
	} wep_key_conf[NUM_WEP_KEYS];
	u8 bssid[ETH_ALEN];          /* BSSID */
	u8 sta_mac[ETH_ALEN];        /* Station mac address */
	/* A flag to indicate is HW crypto is enabled for this bssid */
	bool is_hw_crypto_enabled;
	/* Indicate if this is station mode */
	bool is_sta;
	struct beacon_info beacon_info;
	u16 iv16;
	u32 iv32;
	s8 keyidx;
};

struct mwl_tx_info {
	u32 start_time;
	u32 pkts;
};

struct mwl_amsdu_frag {
	struct sk_buff *skb;
	u8 pad;
	u8 *cur_pos;
	u8 num;
	u32 jiffies;
};

struct mwl_amsdu_ctrl {
	struct mwl_amsdu_frag frag[SYSADPT_TX_WMM_QUEUES];
	u8 cap;
};

struct mwl_sta {
	struct list_head list;
	struct ieee80211_sta *sta;
	bool is_ampdu_allowed;
	struct mwl_tx_info tx_stats[MWL_MAX_TID];
	bool is_amsdu_allowed;
	struct mwl_amsdu_ctrl amsdu_ctrl;
	u16 iv16;
	u32 iv32;
};

/* DMA header used by firmware and hardware. */
struct mwl_dma_data {
	__le16 fwlen;
	struct ieee80211_hdr wh;
	char data[0];
} __packed;

/* Transmission information to transmit a socket buffer. */
struct mwl_tx_ctrl {
	u8 tx_priority;
	u16 qos_ctrl;
	u8 type;
	u8 xmit_control;
	void *sta;
	void *vif;
	void *k_conf;
} __packed;

static inline struct mwl_vif *mwl_dev_get_vif(const struct ieee80211_vif *vif)
{
	return (struct mwl_vif *)&vif->drv_priv;
}

static inline struct mwl_sta *mwl_dev_get_sta(const struct ieee80211_sta *sta)
{
	return (struct mwl_sta *)&sta->drv_priv;
}

#endif /* _mwl_dev_h_ */