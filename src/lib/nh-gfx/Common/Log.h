#ifndef NH_GFX_COMMON_LOG_H
#define NH_GFX_COMMON_LOG_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "Includes.h"
#include "Result.h"

#include "../Fonts/FontManager.h"

#endif

/** @addtogroup lib_nh-gfx_functions
 *  @{
 */

    void nh_gfx_logFont(
        nh_gfx_Font *Font_p 
    );

    void nh_gfx_logVulkanValidation(
        char *message_p
    );

    void nh_gfx_logOpenGLCommand(
        char *format_p, ...
    );

/** @} */

#endif // NH_GFX_COMMON_LOG_H 
