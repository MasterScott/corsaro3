/*
 * corsaro
 *
 * Alistair King, CAIDA, UC San Diego
 * corsaro-info@caida.org
 *
 * Copyright (C) 2012 The Regents of the University of California.
 *
 * This file is part of corsaro.
 *
 * corsaro is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * corsaro is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with corsaro.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef __CORSARO_REPORT_CONFIG_H
#define __CORSARO_REPORT_CONFIG_H

/* ---------- GLOBAL METRIC SETTINGS ---------- */

/** The prefix to attach to all metrics */
/** @todo make the darknet name configurable */
#define METRIC_PREFIX "darknet.ucsd-nt"

enum leafmetric_id {
  LEAFMETRIC_ID_UNIQ_SRC_IP = 0,
  LEAFMETRIC_ID_UNIQ_DST_IP = 1,
  LEAFMETRIC_ID_PKT_CNT     = 2,
  LEAFMETRIC_ID_IP_LEN      = 3,

  LEAFMETRIC_ID_CNT         = 4
};

const char *leafmetric_names[] = {
  "uniq_src_ip",
  "uniq_dst_ip",
  "pkt_cnt",
  "ip_len"
};

enum leafmetric_flag {
  LEAFMETRIC_FLAG_UNIQ_SRC_IP   = 0x01,
  LEAFMETRIC_FLAG_UNIQ_DST_IP   = 0x02,
  LEAFMETRIC_FLAG_PKT_CNT       = 0x04,
  LEAFMETRIC_FLAG_IP_LEN        = 0x08,
};

enum submetric_id {
  SUBMETRIC_ID_MAXMIND_CONTINENT       = 0,
  SUBMETRIC_ID_MAXMIND_COUNTRY         = 1,

  SUBMETRIC_ID_NETACQ_EDGE_CONTINENT   = 2,
  SUBMETRIC_ID_NETACQ_EDGE_COUNTRY     = 3,
  SUBMETRIC_ID_NETACQ_EDGE_REGION      = 4,
  SUBMETRIC_ID_NETACQ_EDGE_POLYS = 5,

  SUBMETRIC_ID_PFX2AS                  = 6,

  SUBMETRIC_ID_PROTOCOL                = 7,

  SUBMETRIC_ID_PORT                    = 8,

  SUBMETRIC_ID_FILTER                  = 9,

  SUBMETRIC_ID_TREE                    = 10,

  SUBMETRIC_ID_CNT                     = 11,
};

enum tree_id {
  TREE_ID_UNFILTERED  = 0,
  TREE_ID_NONSPOOFED  = 1,
  TREE_ID_NONERRATIC  = 2,
  TREE_ID_RFCCLEAN    = 3,
  TREE_ID_CNT         = 4,
};

enum tree_flag {
  TREE_FLAG_UNFILTERED = 0x01,
  TREE_FLAG_NONSPOOFED = 0x02,
  TREE_FLAG_NONERRATIC = 0x04,
  TREE_FLAG_RFCCLEAN = 0x08,
};

const uint8_t tree_flags[] = {
  TREE_FLAG_UNFILTERED,
  TREE_FLAG_NONSPOOFED,
  TREE_FLAG_NONERRATIC,
  TREE_FLAG_RFCCLEAN,
};

const char *tree_names[] = {
  "unfiltered",
  "non-spoofed",
  "non-erratic",
  "rfc5735-non-spoofed",
};

#define UNFILTERED_TAG_NAME "all-pkts"

/* for each tree/submetric combo, list the leafmetrics */
const uint8_t tree_submetric_leafmetrics[TREE_ID_CNT][SUBMETRIC_ID_CNT] = {
  /* Unfiltered */
  {
    /* Maxmind continent */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Maxmind country */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Netacq continent */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Netacq country */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Netacq region */
    0,

    /* Netacq region poly */
    0,

    /* pfx2as */
    0,

    /* Protocol */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Port */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Filter */
    0,

    /* Tree */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,
  },

  /** Non-spoofed */
  {
   /* Maxmind continent */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

   /* Maxmind country */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Netacq continent */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Netacq country */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Netacq region */
    0,

    /* Netacq region poly */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

    /* pfx2as */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,

    /* Protocol */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT,

    /* Port */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,

    /* Filter */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,

    /* Tree */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,
  },

  /** Non-erratic */
  {
   /* Maxmind continent */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

   /* Maxmind country */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

    /* Netacq continent */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

    /* Netacq country */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

    /* Netacq region */
    0,

    /* Netacq region poly */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

    /* pfx2as */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP,

    /* Protocol */
    0,

    /* Port */
    0,

    /* Filter */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,

    /* Tree */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,
  },

  /* RFC 5735, Non-spoofed */
  {
    /* Maxmind continent */
    0,

    /* Maxmind country */
    0,

    /* Netacq continent */
    0,

    /* Netacq country */
    0,

    /* Netacq region */
    0,

    /* Netacq region poly */
    0,

    /* pfx2as */
    0,

    /* Protocol */
    0,

    /* Port */
    0,

    /* Filter */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,

    /* Tree */
    LEAFMETRIC_FLAG_UNIQ_SRC_IP |
    LEAFMETRIC_FLAG_UNIQ_DST_IP |
    LEAFMETRIC_FLAG_PKT_CNT |
    LEAFMETRIC_FLAG_IP_LEN,
  },
};

/* ---------- TREE METRIC SETTINGS ---------- */

#define METRIC_PATH_TREE ".overall"

/* ---------- FILTER CRITERIA METRIC SETTINGS ---------- */

#define METRIC_PATH_FILTER ".filter-criteria"

/* ---------- MAXMIND METRIC SETTINGS ---------- */
const char *continent_strings[] = {
  "??",
  "AF",
  "AN",
  "AS",
  "EU",
  "NA",
  "OC",
  "SA",
};

#define METRIC_PATH_MAXMIND_CONTINENT ".geo.maxmind"

#define METRIC_PATH_MAXMIND_COUNTRY    ".geo.maxmind"

/** The max number of values in a 16 bit number (two 8-bit ascii characters) */
#define METRIC_MAXMIND_ASCII_MAX UINT16_MAX


/* ---------- NETACQ EDGE METRIC SETTINGS ---------- */

/* mapping from netacuity continent code to our string array */
const int netacq_cont_map[] = {
  0, /* 0: '**' => '??' */
  1, /* 1: 'af' => 'AF' */
  2, /* 2: 'an' => 'AN' */
  6, /* 3: 'au' => 'OC' */
  3, /* 4: 'as' => 'AS' */
  4, /* 5: 'eu' => 'EU' */
  5, /* 6: 'na' => 'NA' */
  7, /* 7: 'sa' => 'SA' */
};

#define METRIC_PATH_NETACQ_EDGE_CONTINENT     \
  ".geo.netacuity"

#define METRIC_PATH_NETACQ_EDGE_COUNTRY     \
  ".geo.netacuity"

#define METRIC_PATH_NETACQ_EDGE_REGION     \
  ".geo.netacuity.native" /* deprecated netacuity regions */

#define METRIC_PATH_NETACQ_EDGE_POLYS     \
  ".geo.netacuity"

/** The max region code value (currently the actual max is 30,404, but this
 * could easily go higher. be careful) */
#define METRIC_NETACQ_EDGE_ASCII_MAX UINT16_MAX

/** The number of polygon tables that we are currently supporting */
#define METRIC_NETACQ_EDGE_POLYS_TBL_CNT 2

/* ---------- PFX2AS METRIC SETTINGS ---------- */
#define METRIC_PATH_PFX2AS             ".routing.asn"

uint32_t tree_pfx2as_max[] = {
  /** unfiltered */
  0,

  /** Non-spoofed */
  3000,

  /** Non-erratic */
  UINT32_MAX,
};

/** Sort PFX2AS ASN Records
 *
 * First, sort by ASN count ascending (to put ASN groups at the end)
 * Second, sort by 'size' of AS (number of IPs in it's prefixes)
 * Third, sort by the ASN
 */
#define pfx2as_ip_cnt_lt(alpha, bravo)					\
  (									\
   ((alpha)->asn_cnt < (bravo)->asn_cnt) ||				\
   (									\
    ((alpha)->asn_cnt == (bravo)->asn_cnt) &&				\
    (									\
     ((alpha)->asn_ip_cnt > (bravo)->asn_ip_cnt) ||			\
     (									\
     ((alpha)->asn_ip_cnt == (bravo)->asn_ip_cnt) &&			\
     (									\
     ((alpha)->asn[0] < (bravo)->asn[0])				\
									) \
									) \
									) \
									) \
									)


/* ---------- PROTOCOL METRIC SETTINGS ---------- */
#define METRIC_PATH_PROTOCOL            ".traffic.protocol"
#define METRIC_PROTOCOL_VAL_MAX         256


/* ---------- PORT METRIC SETTINGS ---------- */
/* these need to be METRIC_DIRECTION_MAX apart */
enum {
  METRIC_PORT_PROTOCOL_SKIP  = -1,
  METRIC_PORT_PROTOCOL_TCP   = 0,
  METRIC_PORT_PROTOCOL_UDP   = 1,
  /*  METRIC_PROTOCOL_OTHER = 4,*/

  METRIC_PORT_PROTOCOL_MAX = METRIC_PORT_PROTOCOL_UDP,
};

enum {
  METRIC_PORT_DIRECTION_SRC = 0,
  METRIC_PORT_DIRECTION_DST = 1,

  METRIC_PORT_DIRECTION_MAX = METRIC_PORT_DIRECTION_DST,
};

#define METRIC_PORT_VAL_CNT UINT16_MAX+1

uint16_t tree_port_max[] = {
  /** unfiltered */
  1024,

  /** Non-spoofed */
  /* ideally we want this to be UINT16_MAX, but until we get DBATS... */
  6000,

  /** Non-erratic */
  0, /* no port info */
};

#define PORT_PREFIX ".traffic.port"

static char *port_metric_paths[] = {
  PORT_PREFIX".tcp.src_port",
  PORT_PREFIX".tcp.dst_port",
  PORT_PREFIX".udp.src_port",
  PORT_PREFIX".udp.dst_port",
  /*
  PORT_PREFIX".other.src_port",
  PORT_PREFIX".other.dst_port",
  */
};

/* ---------- FILTER SETTINGS ---------- */

/* need to define a list of tags. easy. */
struct tag_def {
  char *name;
  int tree_flags;
  char *bpf;
};
const struct tag_def tag_defs[] = {
  /* unfiltered tag */
  {
    "all-pkts",
    TREE_FLAG_UNFILTERED,
    NULL,
  },

  /* non-spoofed and non-erratic tags */
  {
    "abnormal-protocol",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "(icmp or udp or proto 41 or (tcp and ((tcp[tcpflags] & 0x2f )= tcp-syn or (tcp[tcpflags] & 0x2f) = tcp-ack or (tcp[tcpflags] & 0x2f) = tcp-rst or (tcp[tcpflags] & 0x2f) = tcp-fin or (tcp[tcpflags] & 0x2f) = (tcp-syn|tcp-fin) or (tcp[tcpflags] & 0x2f) = (tcp-syn|tcp-ack) or (tcp[tcpflags] & 0x2f) = (tcp-fin|tcp-ack) or (tcp[tcpflags] & 0x2f) = (tcp-ack|tcp-push) or (tcp[tcpflags] & 0x2f) = (tcp-ack|tcp-push|tcp-fin))))"
  },
  {
    "ttl-200",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "((ip[8] < 200) or icmp)",
  },
  {
    "fragmented",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "((ip[6:2] & 0x9f)=0)",
  },
  {
    "last-byte-src-0",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "(ip[15:1] != 0)",
  },
  {
    "last-byte-src-255",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "(ip[15:1] != 255)",
  },
  {
    "same-src-dst",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "ip[12:4] != ip[16:4]",
  },
  {
    "udp-port-0",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "not (udp port 0)",
  },
  {
    "tcp-port-0",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC | TREE_FLAG_RFCCLEAN,
    "not (tcp port 0)",
  },
  {
    "rfc5735",
    TREE_FLAG_NONSPOOFED | TREE_FLAG_NONERRATIC,
    "not (src net 0.0.0.0/8 or src net 10.0.0.0/8 or src net 127.0.0.0/8 or src net 169.254.0.0/16 or src net 172.16.0.0/12 or src net 192.0.0.0/24 or src net 192.0.2.0/24 or src net 192.88.99.0/24 or src net 192.168.0.0/16 or src net 198.18.0.0/15 or src net 198.51.100.0/24 or src net 203.0.113.0/24 or src net 224.0.0.0/4 or src net 240.0.0.0/4)",
  },

  /* non-erratic only tags */
  {
    "backscatter",
    TREE_FLAG_NONERRATIC,
    "not (tcp and ((tcp[tcpflags] & tcp-ack != 0) and (tcp[tcpflags] & tcp-syn != 0) or (tcp[tcpflags] & tcp-rst !=0))) and not (icmp and (icmp[0]=0 || icmp[0]=3 || icmp[0]=4 || icmp[0]=5 || icmp[0]=11 || icmp[0]=12 || icmp[0]=14 || icmp[0]=16 || icmp[0]=18)) and not (udp src port 53)",
  },
  {
    "bittorrent",
    TREE_FLAG_NONERRATIC,
    "not (udp and udp [4:2] >= 20  and ((udp[8:4]=0x64313a61 or udp[8:4]=0x64313a72) and udp[12:4]=0x64323a69 and udp[16:4]=0x6432303a)) and not (udp[4:2]>= 44 and udp and udp[28:4]=0x13426974 and udp[32:4]=0x546f7272  and udp[36:4]=0x656e7420 and udp[40:4]=0x70726f74 and udp[44:4]=0x6f636f6c) and not (ip[2:2]>=0x3a and (udp[8:2]=0x4102 or udp[8:2]=0x2102 or udp[8:2]=0x3102 or udp[8:2]=0x1102) and udp[udp[4:2]-4:4]=0 and udp[udp[4:2]-8:4]=0 and udp[udp[4:2]-10:2]=0x0008) and not (ip[2:2]=0x30 and (udp[8:2]=0x4100 or udp[8:2]=0x2100 or udp[8:2]=0x3102 or udp[8:2]=0x1100)) and not (udp and ip[2:2]=61 and udp[20:4]=0x7fffffff and udp[24:4]=0xab020400 and udp[28:4]=0x01000000 and udp[32:4]=0x08000000 and udp[36:4]=0)",
  },
  {
    "udp-0x31",
    TREE_FLAG_NONERRATIC,
    "not (udp and ip[2:2]=58 and udp[8:4]=0x0 and udp[12:4]=0x00 and udp[16:2]=0x3100)"
  },
  {
    "udp-ip-len-96",
    TREE_FLAG_NONERRATIC,
    "not (udp and ip[2:2]=96)"
  },
  {
    "port-53",
    TREE_FLAG_NONERRATIC,
    "not port 53",
  },
  {
    "tcp-port-23",
    TREE_FLAG_NONERRATIC,
    "not tcp port 23",
  },
  {
    "tcp-port-80",
    TREE_FLAG_NONERRATIC,
    "not tcp port 80",
  },
  {
    "tcp-port-5000",
    TREE_FLAG_NONERRATIC,
    "not tcp port 5000",
  },
  {
    "dns-resp-non-standard",
    TREE_FLAG_NONERRATIC,
    "not (udp and ip[2:2]> 0x2a and udp[10:2] & 0xfff0=0x8180 and udp[12:2]=0001 and udp[14:4]=0x00000000 and udp[18:2]=0x0000)",
  },
  {
    "netbios-query-name"
    TREE_FLAG_NONERRATIC,
    "not (udp and src port 137 and dst port 137 and ip[2:2]> 0x30 and udp[20:2]=0x2043 and udp[22:2]=0x4b41 and udp[24:4]=0x41414141)",
  },

  /* rfcclean only tags */
  {
    "not-rfc5735",
    TREE_FLAG_RFCCLEAN,
    "(src net 0.0.0.0/8 or src net 10.0.0.0/8 or src net 127.0.0.0/8 or src net 169.254.0.0/16 or src net 172.16.0.0/12 or src net 192.0.0.0/24 or src net 192.0.2.0/24 or src net 192.88.99.0/24 or src net 192.168.0.0/16 or src net 198.18.0.0/15 or src net 198.51.100.0/24 or src net 203.0.113.0/24 or src net 224.0.0.0/4 or src net 240.0.0.0/4)",
  },

};

#endif /* __CORSARO_REPORT_CONFIG_H */