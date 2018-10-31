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

#ifndef LIBCORSARO_TRACE_H_
#define LIBCORSARO_TRACE_H_

#include <aio.h>

#include <libtrace.h>
#include <wandio.h>

#include "libcorsaro3_log.h"

typedef struct corsaro_fast_trace_writer {
    int io_fd;
    int whichbuf;
    int waiting;
    uint64_t written;

    struct aiocb aio[2];
    char *localbuf[2];
    int offset[2];
    int bufsize[2];

} corsaro_fast_trace_writer_t;

libtrace_t *corsaro_create_trace_reader(corsaro_logger_t *logger,
        char *tracename);
libtrace_out_t *corsaro_create_trace_writer(corsaro_logger_t *logger,
        char *tracename, int level, trace_option_compresstype_t method);
corsaro_fast_trace_writer_t *corsaro_create_fast_trace_writer();
void corsaro_destroy_trace_reader(libtrace_t *trace);
void corsaro_destroy_trace_writer(libtrace_out_t *trace);
void corsaro_destroy_fast_trace_writer(corsaro_fast_trace_writer_t *writer,
        corsaro_logger_t *logger);
int corsaro_read_next_packet(corsaro_logger_t *logger,
        libtrace_t *trace, libtrace_packet_t *packet);
int corsaro_write_packet(corsaro_logger_t *logger,
        libtrace_out_t *trace, libtrace_packet_t *packet);

int corsaro_start_fast_trace_writer(corsaro_logger_t *logger,
        corsaro_fast_trace_writer_t *writer, char *filename);
void corsaro_reset_fast_trace_writer(corsaro_fast_trace_writer_t *writer,
        corsaro_logger_t *logger);
int corsaro_fast_write_erf_packet(corsaro_logger_t *logger,
        corsaro_fast_trace_writer_t *writer, libtrace_packet_t *packet);

#endif

// vim: set sw=4 tabstop=4 softtabstop=4 expandtab :
