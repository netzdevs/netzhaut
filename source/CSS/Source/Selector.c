// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2020  Dajo Frey
 * Published under LGPLv3
 */

// INCLUDE ========================================================================================

#include "../Header/Associate.h"
#include "../Header/Properties.h"
#include "../Header/Macros.h"

#include "../../Core/Header/List.h"
#include "../../Core/Header/HashMap.h"
#include "../../Core/Header/Memory.h"
#include "../../Core/Header/String.h"

#include "../../HTML/Header/Attribute.h"
#include "../../HTML/Header/Document.h"

#include NH_UTILS
#include NH_DEBUG
#include NH_DEFAULT_CHECK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// DECLARE ========================================================================================

static void Nh_CSS_getSelectorParts(
    char *selectorString_p, NH_CSS_SELECTOR type, char **parts_pp
);
static NH_BOOL Nh_CSS_isAttributeSelector(
    const char *selector_p
);

/**
 * Checks if the attribute selector matches a specific node attribute. The implementation currently 
 * also checks for matching node properties.
 */
static NH_BOOL Nh_CSS_attributeSelectorHit(
    const char *selector_p, Nh_HTML_Node *Node_p
);

// INIT ============================================================================================

static void Nh_CSS_initSelector(
    Nh_CSS_Selector *Selector_p, char *selectorString_p)
{
NH_BEGIN()

    Selector_p->type = NH_CSS_SELECTOR_UNDEFINED;
    Selector_p->string_p = selectorString_p;
    Selector_p->Pseudo._class = -1;
    Selector_p->Pseudo.element = -1;
    NH_INIT_LIST(Selector_p->Parts)

NH_SILENT_END()
}

// PART ============================================================================================

static NH_RESULT Nh_CSS_addSelectorPart(
    Nh_CSS_Selector *Selector_p, Nh_CSS_Selector *Part_p)
{
NH_BEGIN()

    Nh_CSS_Selector *Alloc_p = Nh_allocate(sizeof(Nh_CSS_Selector));
    NH_CHECK_MEM(Alloc_p)
    memcpy(Alloc_p, Part_p, sizeof(Nh_CSS_Selector));
    Alloc_p->string_p = Nh_allocateChars(Part_p->string_p);
    NH_CHECK_MEM(Alloc_p->string_p)
    NH_CHECK(Nh_addListItem(&Selector_p->Parts, Alloc_p))

NH_END(NH_SUCCESS)
}

// HIT =============================================================================================

NH_BOOL Nh_CSS_createGenericProperty(
    Nh_HTML_Node *Node_p, char *selectorString_p, Nh_CSS_Selector *Selector_p)
{
NH_BEGIN()

#include NH_CUSTOM_CHECK

    Nh_CSS_initSelector(Selector_p, selectorString_p);

         if (strstr(selectorString_p, ">"))                           {Selector_p->type = NH_CSS_SELECTOR_CHILD_COMBINATOR;}
    else if (strstr(selectorString_p, ":"))                           {Selector_p->type = NH_CSS_SELECTOR_PSEUDO_CLASS;} 
    else if (strstr(selectorString_p, "::"))                          {Selector_p->type = NH_CSS_SELECTOR_PSEUDO_ELEMENT;}
    else if (strstr(selectorString_p, "*"))                           {Selector_p->type = NH_CSS_SELECTOR_UNIVERSAL;}
    else if (selectorString_p[0] == '#')                              {Selector_p->type = NH_CSS_SELECTOR_ID;}
    else if (selectorString_p[0] == '.')                              {Selector_p->type = NH_CSS_SELECTOR_CLASS;}
    else if (!strcmp(selectorString_p, NH_HTML_TAGS_PP[Node_p->tag])) {Selector_p->type = NH_CSS_SELECTOR_TYPE;}
    else if (Nh_CSS_isAttributeSelector(selectorString_p))            {Selector_p->type = NH_CSS_SELECTOR_ATTRIBUTE;}

    switch (Selector_p->type)
    {
        case NH_CSS_SELECTOR_UNIVERSAL :
        case NH_CSS_SELECTOR_TYPE : 
        {
            NH_END(NH_TRUE)
            break;
        }
        case NH_CSS_SELECTOR_ID :
        {    
            for (int i = 0; i < Node_p->Attributes.count; ++i) {
                if (Nh_HTML_getAttribute(&Node_p->Attributes, i)->type == NH_HTML_ATTRIBUTE_ID) {
                    if (!strcmp(selectorString_p + 1, Nh_HTML_getAttribute(&Node_p->Attributes, i)->value_p)) {
                        NH_END(NH_TRUE)
                    }
                }
            }
            break;
        }
        case NH_CSS_SELECTOR_CLASS :
        {    
            for (int i = 0; i < Node_p->Attributes.count; ++i) {
                if (Nh_HTML_getAttribute(&Node_p->Attributes, i)->type == NH_HTML_ATTRIBUTE_CLASS) {
                    if (!strcmp(selectorString_p + 1, Nh_HTML_getAttribute(&Node_p->Attributes, i)->value_p)) {
                        NH_END(NH_TRUE)
                    }
                }
            }
            break;
        }
        case NH_CSS_SELECTOR_ATTRIBUTE :
        {
            char tag_p[256] = {'\0'};
            int count = 0;
            for (int i = 0; i < strlen(selectorString_p); ++i) {if (selectorString_p[i] == '[') {break;}++count;}
            memcpy((void*)tag_p, (void*)selectorString_p, sizeof(char) * count);
            if (!strcmp(tag_p, NH_HTML_TAGS_PP[Node_p->tag])) {NH_END(NH_TRUE)}
            break;
        }
        case NH_CSS_SELECTOR_CHILD_COMBINATOR :
        {
            if (Node_p->Parent_p != NULL) 
            {
                char *parts_pp[2], part1_p[256] = {'\0'}, part2_p[256] = {'\0'};
                parts_pp[0] = part1_p, parts_pp[1] = part2_p;
                Nh_CSS_getSelectorParts(selectorString_p, NH_CSS_SELECTOR_CHILD_COMBINATOR, (char**)parts_pp);

                Nh_CSS_Selector Left, Right;

                if (Nh_CSS_createGenericProperty(Node_p->Parent_p, parts_pp[0], &Left) 
                &&  Nh_CSS_createGenericProperty(Node_p, parts_pp[1], &Right)) {
                    NH_CHECK(NH_FALSE, Nh_CSS_addSelectorPart(Selector_p, &Left))
                    NH_CHECK(NH_FALSE, Nh_CSS_addSelectorPart(Selector_p, &Right))
                    NH_END(NH_TRUE)
                }
            }
            break;
        }
        case NH_CSS_SELECTOR_PSEUDO_CLASS :
        {
            char pseudoClassString_p[255] = {'\0'};
            strcpy(pseudoClassString_p, strstr(selectorString_p, ":") + 1);

            Nh_HashValue *HashValue_p;
            if (hashmap_get(NH_HASHMAPS.CSS.PseudoClasses, pseudoClassString_p, (void**)(&HashValue_p)) != MAP_OK) {NH_END(NH_FALSE)}
            Selector_p->Pseudo._class = HashValue_p->number;

            char leftSelect_p[255] = {'\0'};
            strcpy(leftSelect_p, selectorString_p);
            leftSelect_p[strlen(selectorString_p) - (strlen(pseudoClassString_p) + 1)] = '\0';

            Nh_CSS_Selector Selector;

            if (Nh_CSS_createGenericProperty(Node_p, leftSelect_p, &Selector)) {
                NH_CHECK(NH_FALSE, Nh_CSS_addSelectorPart(Selector_p, &Selector))
                NH_END(NH_TRUE)
            }
        }
        case NH_CSS_SELECTOR_PSEUDO_ELEMENT :
        {
            int offset = 0;
            char pseudoElementString_p[255] = {'\0'};
            strcpy(pseudoElementString_p, strstr(selectorString_p, ":") + 1);

            if (pseudoElementString_p[0] == ':') {offset = 1;}

            Nh_HashValue *HashValue_p;
            if (hashmap_get(NH_HASHMAPS.CSS.PseudoElements, pseudoElementString_p + offset, (void**)(&HashValue_p)) != MAP_OK) {NH_END(NH_FALSE)}
            Selector_p->Pseudo.element = HashValue_p->number;

            char leftSelect_p[255] = {'\0'};
            strcpy(leftSelect_p, selectorString_p);
            leftSelect_p[strlen(selectorString_p) - (strlen(pseudoElementString_p) + 1 + offset)] = '\0';

            Nh_CSS_Selector Selector;

            if (Nh_CSS_createGenericProperty(Node_p, leftSelect_p, &Selector)) {
                NH_CHECK(NH_FALSE, Nh_CSS_addSelectorPart(Selector_p, &Selector))
                NH_END(NH_TRUE)
            }
            break;
        }
    }

#include NH_DEFAULT_CHECK

NH_END(NH_FALSE)
}

NH_BOOL Nh_CSS_selectorHit(
    Nh_HTML_Node *Node_p, Nh_CSS_Selector *Selector_p)
{
NH_BEGIN()

#include NH_CUSTOM_CHECK

    switch (Selector_p->type)
    {
        case NH_CSS_SELECTOR_UNIVERSAL :
        case NH_CSS_SELECTOR_TYPE      : 
        case NH_CSS_SELECTOR_ID        :
        case NH_CSS_SELECTOR_CLASS     :
        {
            NH_END(NH_TRUE)
        }
        case NH_CSS_SELECTOR_ATTRIBUTE :
        {
            if (Nh_CSS_attributeSelectorHit(Selector_p->string_p, Node_p)) {
                NH_END(NH_TRUE)
            }
            break;
        }
        case NH_CSS_SELECTOR_CHILD_COMBINATOR :
        {
            if (Node_p->Parent_p != NULL) 
            {
                if (Nh_CSS_selectorHit(Node_p->Parent_p, Nh_getListItem(&Selector_p->Parts, 0)) 
                &&  Nh_CSS_selectorHit(Node_p, Nh_getListItem(&Selector_p->Parts, 1))) {
                    NH_END(NH_TRUE)
                }
            }
            break;
        }
        case NH_CSS_SELECTOR_PSEUDO_CLASS :
        {
            if (Node_p->Pseudo.classes_p[Selector_p->Pseudo._class] 
            &&  Nh_CSS_selectorHit(Node_p, Nh_getListItem(&Selector_p->Parts, 0))) {
                NH_END(NH_TRUE)
            }
            break;
        }
        case NH_CSS_SELECTOR_PSEUDO_ELEMENT :
        {
            if (Node_p->Pseudo.elements_p[Selector_p->Pseudo.element] 
            &&  Nh_CSS_selectorHit(Node_p, Nh_getListItem(&Selector_p->Parts, 0))) {
                NH_END(NH_TRUE)
            }
            break;
        }
    }

#include NH_DEFAULT_CHECK

NH_END(NH_FALSE)
}

// HELPER ==========================================================================================

static NH_BOOL Nh_CSS_isAttributeSelector(
    const char *selector_p)
{
NH_BEGIN()

    int c = 0;
    for (int i = 0; i < strlen(selector_p); ++i) {
        if (selector_p[i] == '[') {c = 1;}
        if (c == 1 && selector_p[i] == ']') {c = 2;}
    }

NH_END(c == 2)
}

static NH_BOOL Nh_CSS_attributeHit(
    Nh_HTML_Node *Node_p, NH_HTML_ATTRIBUTE type, char *value_p)
{
NH_BEGIN()

    for (int i = 0; i < Node_p->Attributes.count; ++i) {
        if (Nh_HTML_getAttribute(&Node_p->Attributes, i)->type == type) {
            if (value_p != NULL) {NH_END(!strcmp(value_p, Nh_HTML_getAttribute(&Node_p->Attributes, i)->value_p))}
            else {NH_END(NH_TRUE)}
        }
    }

NH_END(NH_FALSE)
}

static NH_BOOL Nh_CSS_propertyHit(
    Nh_HTML_Node *Node_p, NH_CSS_PROPERTY type, char *value_p)
{
NH_BEGIN()

    for (int i = 0; i < Node_p->Properties.count; ++i) {
        if (Nh_CSS_getProperty(&Node_p->Properties, i)->type == type) {
            if (value_p == NULL) {NH_END(NH_TRUE)}
            for (int j = 0; j < Nh_CSS_getProperty(&Node_p->Properties, i)->valueCount; ++j) {
                if (!strcmp(value_p, Nh_CSS_getProperty(&Node_p->Properties, i)->values_pp[j])) {NH_END(NH_TRUE)}
            }
        }
    }

NH_END(NH_FALSE)
}

static NH_BOOL Nh_CSS_attributeSelectorHit(
    const char *selector_p, Nh_HTML_Node *Node_p)
{
NH_BEGIN()

    char element_p[256] = {'\0'};
    int count = 0;
    
    for (int i = 0; i < strlen(selector_p); ++i) {if (selector_p[i] == '[') {break;}++count;}
    memcpy((void*)element_p, (void*)selector_p, sizeof(char) * count);
    
    if (!strcmp(element_p, NH_HTML_TAGS_PP[Node_p->tag]))
    {
        char attr_p[256] = {'\0'}, val_p[256] = {'\0'};
        NH_BOOL attr = NH_FALSE, val = NH_FALSE;
        
        count = 0;
        for (int i = 0; i < strlen(selector_p); ++i) 
        {
            if (selector_p[i] == ']')        {break;}
            if (val && selector_p[i] != '"') {val_p[count++] = selector_p[i];}
            if (selector_p[i] == '=')        {attr = NH_FALSE; val = NH_TRUE; count = 0;}
            if (attr)                        {attr_p[count++] = selector_p[i];}
            if (selector_p[i] == '[')        {attr = NH_TRUE;}
        }

        Nh_HashValue *HashValue_p;
        NH_BOOL validAttribute = NH_FALSE, validProperty = NH_FALSE;

        if (hashmap_get(NH_HASHMAPS.HTML.Attributes, attr_p, (void**)(&HashValue_p)) != MAP_OK) {
            if (hashmap_get(NH_HASHMAPS.CSS.Properties, attr_p, (void**)(&HashValue_p)) != MAP_OK) {NH_END(NH_FALSE)}
            else {validProperty = NH_TRUE;}
        } 
        else {validAttribute = NH_TRUE;}

        if (validAttribute) {NH_END(Nh_CSS_attributeHit(Node_p, HashValue_p->number, val_p[0] != '\0' ? val_p : NULL))}
        if (validProperty)  {NH_END(Nh_CSS_propertyHit(Node_p, HashValue_p->number, val_p[0] != '\0' ? val_p : NULL))}
    }

NH_END(NH_FALSE)
}

static void Nh_CSS_getSelectorParts(
    char *selectorString_p, NH_CSS_SELECTOR type, char **parts_pp)
{
NH_BEGIN()

    switch (type)
    {
        case NH_CSS_SELECTOR_CHILD_COMBINATOR :
        {
            strcpy(parts_pp[1], strstr(selectorString_p, ">") + 1);
            strcpy(parts_pp[0], selectorString_p);
            parts_pp[0][strlen(selectorString_p) - (strlen(parts_pp[1]) + 1)] = '\0';
            break;
        }
     }

NH_SILENT_END()
}

