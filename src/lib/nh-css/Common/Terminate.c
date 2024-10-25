// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "Terminate.h"
#include "IndexMap.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// DEBUG ===========================================================================================

NH_API_RESULT nh_css_terminate()
{
    nh_css_freeIndexMap();
    return NH_API_SUCCESS;
}

