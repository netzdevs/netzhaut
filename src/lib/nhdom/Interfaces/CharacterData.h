#ifndef NH_DOM_CHARACTER_DATA_H
#define NH_DOM_CHARACTER_DATA_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "../Common/Includes.h"

#endif

/** @addtogroup lib_nhdom_functions
 *  @{
 */

    NH_DOM_RESULT nh_dom_appendToCharacterData(
        nh_dom_CharacterData *CharacterData_p, nh_webidl_DOMString DOMString 
    );

    nh_webidl_DOMString *nh_dom_getCharacterDataString(
        nh_dom_CharacterData *CharacterData_p
    );

/** @} */

#endif
