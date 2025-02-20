/*
 * Copyright (c) 2019-2021 Apple Inc. All rights reserved.
 * Copyright Epic Games, Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

/* This isn't really a header. It's a preprocessor for-each loop.
   
   To generate code for each page config kind, just do:
   
       #define PAS_DEFINE_HEAP_CONFIG_KIND(name, page_config_value) \
           ... the code you want for pas_heap_config_kind_##name \
               and (page_config_value) ...
       #include "pas_heap_config_kind.def"
       #undef PAS_DEFINE_HEAP_CONFIG_KIND
   
   For example, this can be used to create switch statements as an alternative to adding virtual
   functions or fields to heap_config. Generally, we only use this when we have no
   other alternative (like the unified deallocation log). */

PAS_DEFINE_HEAP_CONFIG_KIND(
    null,
    ((pas_heap_config){
        .config_ptr = NULL,
        .kind = pas_heap_config_kind_null,
    }))

PAS_DEFINE_HEAP_CONFIG_KIND(pas_utility, PAS_UTILITY_HEAP_CONFIG)

#if PAS_ENABLE_THINGY
PAS_DEFINE_HEAP_CONFIG_KIND(thingy, THINGY_HEAP_CONFIG)
#endif

#if PAS_ENABLE_ISO
PAS_DEFINE_HEAP_CONFIG_KIND(iso, ISO_HEAP_CONFIG)
#endif

#if PAS_ENABLE_ISO_TEST
PAS_DEFINE_HEAP_CONFIG_KIND(iso_test, ISO_TEST_HEAP_CONFIG)
#endif

#if PAS_ENABLE_MINALIGN32
PAS_DEFINE_HEAP_CONFIG_KIND(minalign32, MINALIGN32_HEAP_CONFIG)
#endif

#if PAS_ENABLE_PAGESIZE64K
PAS_DEFINE_HEAP_CONFIG_KIND(pagesize64k, PAGESIZE64K_HEAP_CONFIG)
#endif

#if PAS_ENABLE_BMALLOC
PAS_DEFINE_HEAP_CONFIG_KIND(bmalloc, BMALLOC_HEAP_CONFIG)
#endif

#if PAS_ENABLE_HOTBIT
PAS_DEFINE_HEAP_CONFIG_KIND(hotbit, HOTBIT_HEAP_CONFIG)
#endif

#if PAS_ENABLE_JIT
PAS_DEFINE_HEAP_CONFIG_KIND(jit, JIT_HEAP_CONFIG)
#endif

#if PAS_ENABLE_INLINE_MEDIUM_PAGE_HEADER
PAS_DEFINE_HEAP_CONFIG_KIND(inline_medium_page_header, INLINE_MEDIUM_PAGE_HEADER_CONFIG)
#endif

#if PAS_ENABLE_OUTLINE_MEDIUM_PAGE_HEADER
PAS_DEFINE_HEAP_CONFIG_KIND(outline_medium_page_header, OUTLINE_MEDIUM_PAGE_HEADER_CONFIG)
#endif

#if PAS_ENABLE_INLINE_NON_COMMITTABLE_GRANULES
PAS_DEFINE_HEAP_CONFIG_KIND(inline_non_committable_granules, INLINE_NON_COMMITTABLE_GRANULES_CONFIG)
#endif

#if PAS_ENABLE_OUTLINE_NON_COMMITTABLE_GRANULES
PAS_DEFINE_HEAP_CONFIG_KIND(outline_non_committable_granules, OUTLINE_NON_COMMITTABLE_GRANULES_CONFIG)
#endif

#if PAS_ENABLE_FILC
PAS_DEFINE_HEAP_CONFIG_KIND(filc, FILC_HEAP_CONFIG)
PAS_DEFINE_HEAP_CONFIG_KIND(filc_hard, FILC_HARD_HEAP_CONFIG)
#endif

