#ifndef NH_CORE_CHANNEL_H
#define NH_CORE_CHANNEL_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "../Common/Includes.h"

#include <stddef.h>

#endif

/** @addtogroup lib_nhcore_structs
 *  @{
 */

    // TODO semaphore etc.
    typedef struct nh_Channel {
#ifdef __unix__
        int rw_p[2];
#endif
    } nh_Channel;

/** @} */

/** @addtogroup lib_nhcore_functions
 *  @{
 */

    NH_CORE_RESULT nh_core_initChannel(
        nh_Channel *Channel_p
    );
    
    NH_CORE_RESULT nh_openChannel(
        nh_Channel *Channel_p
    );
    
    void nh_closeChannelReadAccess(
        nh_Channel *Channel_p
    );
    
    void nh_closeChannelWriteAccess(
        nh_Channel *Channel_p
    );
    
    int nh_core_writeToChannel(
        nh_Channel *Channel_p, NH_BYTE *bytes_p, int byteCount
    );
    
    NH_BYTE *nh_readFromChannel(
        nh_Channel *Channel_p, size_t *size_p
    );

/** @} */

#endif 
