/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef HUSK_TL_UPLOAD_H
#define HUSK_TL_UPLOAD_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Uploads are buffered by the host HTTP bridge. Keep memory bounded until the
 * bridge supports streaming, and leave the old buffer intact on failure. */
enum { TL_MAX_UPLOAD = 64 * 1024 * 1024 };
static bool tl_append_upload(uint8_t **body, size_t *len, size_t *cap, const void *src, size_t n)
{
    if (*len > TL_MAX_UPLOAD || n > TL_MAX_UPLOAD - *len) return false;
    if (!n) return true;
    size_t need = *len + n;
    if (need > *cap) {
        size_t next = *cap ? *cap : 65536;
        while (next < need) next *= 2;
        uint8_t *p = realloc(*body, next);
        if (!p) return false;
        *body = p; *cap = next;
    }
    memcpy(*body + *len, src, n); *len = need;
    return true;
}
#endif
