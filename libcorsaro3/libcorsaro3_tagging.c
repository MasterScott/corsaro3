/*
 * corsaro
 *
 * Alistair King, CAIDA, UC San Diego
 * Shane Alcock, WAND, University of Waikato
 *
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

#include <stdlib.h>
#include <string.h>

#include <libipmeta.h>
#include "libcorsaro3_tagging.h"
#include "libcorsaro3_log.h"

corsaro_packet_tagger_t *corsaro_create_packet_tagger(corsaro_logger_t *logger)
{

    corsaro_packet_tagger_t *tagger = NULL;

    tagger = (corsaro_packet_tagger_t *)calloc(1,
            sizeof(corsaro_packet_tagger_t));
    if (!tagger) {
        return NULL;
    }

    tagger->logger = logger;
    tagger->ipmeta = ipmeta_init();
    tagger->providers = libtrace_list_init(sizeof(ipmeta_provider_t *));
    tagger->tagfreelist = libtrace_list_init(sizeof(corsaro_packet_tags_t *));

    return tagger;
}

#define MAXSPACE (4096)
#define FRAGSPACE (512)

#define COPY_STRING(space, maxspace, used, toadd, errname) \
    if (used + strlen(toadd) >= maxspace) { \
        corsaro_log(logger, "%s option string is too long?", errname); \
        return NULL; \
    } \
    memcpy(nxt, toadd, strlen(toadd)); \
    nxt += strlen(toadd); \
    used += strlen(toadd); \
    space[used] = '\0';

static inline char *create_maxmind_option_string(corsaro_logger_t *logger,
        maxmind_opts_t *maxopts) {

    char space[MAXSPACE];
    char fragment[FRAGSPACE];
    char *nxt = space;
    int used = 0;
    int towrite = 0;

    if (maxopts->directory) {
        snprintf(fragment, FRAGSPACE, "-d %s ", maxopts->directory);
        COPY_STRING(space, MAXSPACE, used, fragment, "maxmind");
    }

    if (maxopts->ds_name) {
        snprintf(fragment, FRAGSPACE, "-D %s ", maxopts->ds_name);
        COPY_STRING(space, MAXSPACE, used, fragment, "maxmind");
    }

    if (maxopts->blocks_file) {
        snprintf(fragment, FRAGSPACE, "-b %s ", maxopts->blocks_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "maxmind");
    }

    if (maxopts->locations_file) {
        snprintf(fragment, FRAGSPACE, "-l %s ", maxopts->locations_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "maxmind");
    }

    if (used > 0) {
        return strdup(space);
    }
    return NULL;
}

static inline char *create_prefix2asn_option_string(corsaro_logger_t *logger,
        pfx2asn_opts_t *pfxopts) {

    char space[MAXSPACE];
    char fragment[FRAGSPACE];
    char *nxt = space;
    int used = 0;
    int towrite = 0;

    snprintf(fragment, FRAGSPACE, "%s ", "prefix2asn");

    COPY_STRING(space, MAXSPACE, used, fragment, "prefix2asn");

    if (pfxopts->pfx2as_file) {
        snprintf(fragment, FRAGSPACE, "-f %s ", pfxopts->pfx2as_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "maxmind");
    }

    if (pfxopts->ds_name) {
        snprintf(fragment, FRAGSPACE, "-D %s ", pfxopts->ds_name);
        COPY_STRING(space, MAXSPACE, used, fragment, "prefix2asn");
    }

    if (used > 0) {
        return strdup(space);
    }
    return NULL;
}

static inline char *create_netacq_option_string(corsaro_logger_t *logger,
        netacq_opts_t *acqopts) {

    char space[MAXSPACE];
    char fragment[FRAGSPACE];
    char *nxt = space;
    int used = 0;
    int towrite = 0;
    libtrace_list_node_t *n;

    snprintf(fragment, FRAGSPACE, "%s ", "netacq-edge");

    COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");

    if (acqopts->blocks_file) {
        snprintf(fragment, FRAGSPACE, "-b %s ", acqopts->blocks_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
    }

    if (acqopts->ds_name) {
        snprintf(fragment, FRAGSPACE, "-D %s ", acqopts->ds_name);
        COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
    }

    if (acqopts->country_file) {
        snprintf(fragment, FRAGSPACE, "-c %s ", acqopts->country_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
    }

    if (acqopts->locations_file) {
        snprintf(fragment, FRAGSPACE, "-l %s ", acqopts->locations_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
    }

    if (acqopts->region_file) {
        snprintf(fragment, FRAGSPACE, "-r %s ", acqopts->region_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
    }

    if (acqopts->polygon_map_file) {
        snprintf(fragment, FRAGSPACE, "-p %s ", acqopts->polygon_map_file);
        COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
    }

    if (acqopts->polygon_table_files) {
        n = acqopts->polygon_table_files->head;
        while (n) {
            char *fname = *((char **)(n->data));
            snprintf(fragment, FRAGSPACE, "-t %s ", fname);
            COPY_STRING(space, MAXSPACE, used, fragment, "netacq-edge");
            n = n->next;
        }
    }

    if (used > 0) {
        return strdup(space);
    }
    return NULL;
}

static char *create_ipmeta_options(corsaro_logger_t *logger,
        ipmeta_provider_id_t provid, void *options) {

    char *opts = NULL;

    switch(provid) {
        case IPMETA_PROVIDER_MAXMIND:
            opts = create_maxmind_option_string(logger,
                    (maxmind_opts_t *)options);
            break;
        case IPMETA_PROVIDER_NETACQ_EDGE:
            opts = create_netacq_option_string(logger,
                    (netacq_opts_t *)options);
            break;
        case IPMETA_PROVIDER_PFX2AS:
            opts = create_prefix2asn_option_string(logger,
                    (pfx2asn_opts_t *)options);
            break;
    }

    return opts;

}

int corsaro_enable_ipmeta_provider(corsaro_packet_tagger_t *tagger,
        ipmeta_provider_id_t provid, void *options) {

    ipmeta_provider_t *prov;
    char *optstring = NULL;

    if (tagger == NULL) {
        return -1;
    }

    if (tagger->ipmeta == NULL) {
        corsaro_log(tagger->logger,
                "Cannot enable IPMeta provider: IPMeta instance is NULL.");
        return -1;
    }

    prov = ipmeta_get_provider_by_id(tagger->ipmeta, provid);
    if (prov == NULL) {
        corsaro_log(tagger->logger,
                "Cannot enable IPMeta provider: %u is an invalid provider ID.",
                provid);
        return -1;
    }

    optstring = create_ipmeta_options(tagger->logger, provid, options);
    if (!optstring) {
        corsaro_log(tagger->logger,
                "Cannot enable IPMeta provider %u: error parsing options.",
                provid);
        return -1;
    }

    if (ipmeta_enable_provider(tagger->ipmeta, prov, (const char *)optstring,
            IPMETA_PROVIDER_DEFAULT_NO) != 0) {
        corsaro_log(tagger->logger,
                "Cannot enable IPMeta provider %u: libipmeta internal error.",
                provid);
        free(optstring);
        return -1;
    }

    libtrace_list_push_back(tagger->providers, &prov);

    if (optstring) {
        free(optstring);
    }

    return 0;
}

void corsaro_destroy_packet_tagger(corsaro_packet_tagger_t *tagger) {

    libtrace_list_node_t *n;

    if (tagger) {
        if (tagger->ipmeta) {
            ipmeta_free(tagger->ipmeta);
        }

        if (tagger->providers) {
            libtrace_list_deinit(tagger->providers);
        }

        if (tagger->tagfreelist) {
            n = tagger->tagfreelist->head;
            while (n) {
                corsaro_packet_tags_t *tag = *(corsaro_packet_tags_t **)(n->data);
                free(tag);
                n = n->next;
            }
            libtrace_list_deinit(tagger->tagfreelist);
        }
        free(tagger);
    }
}

static int update_maxmind_tags(corsaro_logger_t *logger,
        ipmeta_provider_t *prov, uint32_t addr, corsaro_packet_tags_t *tags) {

    ipmeta_record_t *rec = NULL;

    rec = ipmeta_lookup_single(prov, addr);

    if (rec == NULL) {
        return 0;
    }

    tags->maxmind_continent = *((uint16_t *)(rec->continent_code));
    tags->maxmind_country = *((uint16_t *)(rec->country_code));

    tags->providers_used |= (1 << IPMETA_PROVIDER_MAXMIND);

    return 0;
}

static void update_basic_tags(corsaro_logger_t *logger,
        libtrace_packet_t *packet, corsaro_packet_tags_t *tags) {

    void *transport;
    uint8_t proto;
    libtrace_icmp_t *icmp;
    uint32_t rem;

    tags->protocol = 0;
    tags->src_port = 0;
    tags->dest_port = 0;

    transport = trace_get_transport(packet, &proto, &rem);

    if (transport == NULL) {
        return;
    }

    tags->protocol = proto;
    if (proto == TRACE_IPPROTO_ICMP && rem >= 2) {
        icmp = (libtrace_icmp_t *)transport;
        tags->src_port = icmp->type;
        tags->dest_port = icmp->code;
    } else if (proto == TRACE_IPPROTO_TCP || proto == TRACE_IPPROTO_UDP) {
        tags->src_port = trace_get_source_port(packet);
        tags->dest_port = trace_get_destination_port(packet);
    }
    tags->providers_used |= 1;
}

int corsaro_tag_packet(corsaro_packet_tagger_t *tagger,
        corsaro_packet_tags_t *tags, libtrace_packet_t *packet) {

    struct sockaddr_storage saddr;
    struct sockaddr_in *sin;
    libtrace_list_node_t *n;

    tags->providers_used = 0;

    if (tagger->providers == NULL) {
        return 0;
    }

    if (trace_get_source_address(packet, (struct sockaddr *)(&saddr)) == NULL)
    {
        return 0;
    }

    if (saddr.ss_family != AF_INET) {
        return 0;
    }

    sin = (struct sockaddr_in *)(&saddr);

    n = tagger->providers->head;
    while (n) {
        ipmeta_provider_t *prov = *((ipmeta_provider_t **)(n->data));
        n = n->next;

        switch(ipmeta_get_provider_id(prov)) {
            case IPMETA_PROVIDER_MAXMIND:
                if (update_maxmind_tags(tagger->logger, prov,
                            sin->sin_addr.s_addr, tags) != 0) {
                    return -1;
                }
                break;
            /* TODO other provider methods */
            default:
                printf("???: %u\n", ipmeta_get_provider_id(prov));
        }
    }

    update_basic_tags(tagger->logger, packet, tags);
    tags->src_port = trace_get_source_port(packet);

    return 0;
}


// vim: set sw=4 tabstop=4 softtabstop=4 expandtab :