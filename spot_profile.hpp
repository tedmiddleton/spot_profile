#ifndef INCLUDED_spot_profile_hpp
#define INCLUDED_spot_profile_hpp

#include <stdint.h>

#include <immintrin.h>
#include <x86intrin.h>

extern uint64_t g_spot_profile_tsc;
extern uint64_t g_spot_profile_ema_tsc;
extern uint64_t g_spot_profile_current_tsc;

#if __APPLE__

    #define _rdtscp __rdtscp

#endif

#define SP_BEGIN()              \
    uint64_t tsc1, tsc2, tsca;  \
    unsigned dummy;             \
    tsca = 0;                   \
    tsc1 = _rdtscp(&dummy);

#define SP_END()                        \
    tsc2 = _rdtscp(&dummy);             \
    tsca = tsc2-tsc1;                   \
    if (tsca < g_spot_profile_tsc) {    \
        g_spot_profile_tsc = tsca;      \
    }                                   \
    g_spot_profile_current_tsc = tsca;  \
    g_spot_profile_ema_tsc =            \
        (uint64_t)(tsca * 0.2 + g_spot_profile_ema_tsc * 0.8);

#define SP_CLEAR()                          \
    g_spot_profile_tsc = UINT64_MAX;        \
    g_spot_profile_ema_tsc = UINT64_MAX;    \
    g_spot_profile_current_tsc = UINT64_MAX;

#endif // INCLUDED_spot_profile_hpp

