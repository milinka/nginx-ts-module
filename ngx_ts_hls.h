
/*
 * Copyright (C) Roman Arutyunyan
 */


#include <ngx_config.h>
#include <ngx_core.h>

#include "ngx_ts_stream.h"


#ifndef _NGX_TS_HLS_H_INCLUDED_
#define _NGX_TS_HLS_H_INCLUDED_


typedef struct {
    ngx_path_t            *path;
    ngx_msec_t             min_seg;
    ngx_msec_t             max_seg;
    ngx_uint_t             nsegs;
} ngx_ts_hls_conf_t;


typedef struct {
    ngx_uint_t             id;
    uint64_t               duration;
} ngx_ts_hls_segment_t;


typedef struct {
    ngx_file_t             file;
    ngx_str_t              path;
    u_char                *m3u8_path;
    u_char                *m3u8_tmp_path;

    ngx_chain_t           *prologue;
    ngx_ts_stream_t       *ts;
    ngx_ts_hls_conf_t     *conf;

    ngx_ts_hls_segment_t  *segs;
    ngx_uint_t             nsegs;
    ngx_uint_t             seg;
    uint64_t               seg_pts;
} ngx_ts_hls_t;


ngx_ts_hls_t *ngx_ts_hls_create(ngx_ts_hls_conf_t *conf, ngx_ts_stream_t *ts,
    ngx_str_t *name);
ngx_int_t ngx_ts_hls_write_frame(ngx_ts_hls_t *hls, ngx_ts_program_t *prog,
    ngx_ts_es_t *es, ngx_chain_t *bufs);
ngx_msec_t ngx_ts_hls_file_manager(void *data);


#endif /* _NGX_TS_HLS_H_INCLUDED_ */
