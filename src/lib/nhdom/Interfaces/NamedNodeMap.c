// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "NamedNodeMap.h"

#include "../Common/Macros.h"

#include "../../nhcore/Util/List.h"
#include "../../nhcore/System/Memory.h"

#include "../../nhwebidl/Runtime/Object.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// DECLARE =========================================================================================

typedef struct nh_dom_NamedNodeMapInternal {
    nh_dom_Element *Element_p;
    nh_List AttributeList;
} nh_dom_NamedNodeMapInternal;

// INITIALIZE ======================================================================================

NH_DOM_RESULT nh_dom_initializeNamedNodeMap(
    nh_webidl_Object *NamedNodeMap_p)
{
NH_DOM_BEGIN()

    NamedNodeMap_p->internal_p = nh_core_allocate(sizeof(nh_dom_NamedNodeMapInternal));
    NH_DOM_CHECK_MEM(NamedNodeMap_p->internal_p)

    ((nh_dom_NamedNodeMapInternal*)NamedNodeMap_p->internal_p)->AttributeList = nh_core_initList(8);
    NamedNodeMap_p->Attributes.pp[0] = &((nh_dom_NamedNodeMapInternal*)NamedNodeMap_p->internal_p)->AttributeList.size;

NH_DOM_DIAGNOSTIC_END(NH_DOM_SUCCESS)
}

// INTERNAL ========================================================================================

nh_dom_NamedNodeMap *nh_dom_createNamedNodeMap(
    nh_dom_Element *Element_p)
{
NH_DOM_BEGIN()

    nh_webidl_Object *NamedNodeMap_p = nh_webidl_createObject("DOM", "NamedNodeMap");
    NH_DOM_CHECK_MEM_2(NULL, NamedNodeMap_p)

    ((nh_dom_NamedNodeMapInternal*)NamedNodeMap_p->internal_p)->Element_p = Element_p;

NH_DOM_END((nh_dom_NamedNodeMap*)NamedNodeMap_p)
}

nh_dom_Attr* nh_dom_getAttr(
    nh_dom_NamedNodeMap *NamedNodeMap_p, NH_WEBIDL_UNSIGNED_LONG index)
{
NH_DOM_BEGIN()

    nh_List *AttributeList_p = 
        &((nh_dom_NamedNodeMapInternal*)((nh_webidl_Object*)NamedNodeMap_p)->internal_p)->AttributeList;

    if (index >= AttributeList_p->size) {
        NH_DOM_END(NULL)
    }
 
NH_DOM_END(AttributeList_p->pp[index])
}

nh_List *nh_dom_getAttrList(
    nh_dom_NamedNodeMap *NamedNodeMap_p)
{
NH_DOM_BEGIN()
NH_DOM_END(&((nh_dom_NamedNodeMapInternal*)((nh_webidl_Object*)NamedNodeMap_p)->internal_p)->AttributeList)
}

