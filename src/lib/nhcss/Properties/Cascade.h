#ifndef NH_CSS_CASCADE_H
#define NH_CSS_CASCADE_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "Filter.h"

#include "../Common/Includes.h"

#endif

/** @addtogroup lib_nhcss_functions
 *  @{
 */

    nh_css_DeclaredValue *nh_css_compare(
        nh_css_DeclaredValue *Value1_p, nh_css_DeclaredValue *Value2_p
    );

    void nh_css_cascade(
        nh_css_Filter *Filter_p
    );

/** @} */

#endif
