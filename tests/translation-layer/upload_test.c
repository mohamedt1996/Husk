/* SPDX-License-Identifier: GPL-2.0-or-later */
#include <assert.h>
#include "../../src/translation-layer-next/husk-tl-upload.h"

int main(void)
{
    uint8_t *p = NULL; size_t len = 0, cap = 0;
    assert(tl_append_upload(&p, &len, &cap, NULL, 0));
    for (int i = 0; i < 100000; i++) assert(tl_append_upload(&p, &len, &cap, "ab", 2));
    assert(len == 200000 && cap >= len && p[0] == 'a' && p[len - 1] == 'b');
    uint8_t *original = p; size_t old_len = len, old_cap = cap;
    assert(!tl_append_upload(&p, &len, &cap, "x", TL_MAX_UPLOAD));
    assert(p == original && len == old_len && cap == old_cap && p[len - 1] == 'b');
    free(p);
    return 0;
}
