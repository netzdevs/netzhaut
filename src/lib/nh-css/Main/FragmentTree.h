#ifndef NH_CSS_FRAGMENT_TREE_H
#define NH_CSS_FRAGMENT_TREE_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "SourceTree.h"
#include "BoxTree.h"

#include "../Layout/BoxModel.h"
#include "../Common/Includes.h"

#endif

/** @addtogroup lib_nh-css_enums
 *  @{
 */

    typedef enum NH_CSS_FRAGMENT {
        NH_CSS_FRAGMENT_BOX,
        NH_CSS_FRAGMENT_TEXT,
    } NH_CSS_FRAGMENT;

/** @} */

/** @addtogroup lib_nh-css_structs
 *  @{
 */

    typedef struct nh_css_TextFragment {
        nh_css_TextValues Values;
        NH_ENCODING_UTF32 *text_p;
        unsigned int length;
    } nh_css_TextFragment;

    typedef struct nh_css_BoxFragment {
        nh_css_BoxValues Values;
    } nh_css_BoxFragment;

    typedef struct nh_css_Fragment {
        NH_CSS_FRAGMENT type;
        nh_css_BoxFragment Box;
        nh_css_TextFragment Text;
        nh_css_PixelBox Block;
        struct nh_css_Fragment *Parent_p;
        nh_css_BoxTreeNode *Node_p;
        nh_core_List Children;
        void *data_p;
    } nh_css_Fragment;

    typedef struct nh_css_FragmentTree {
        nh_css_Fragment *Root_p;
    } nh_css_FragmentTree;

/** @} */

/** @addtogroup lib_nh-css_functions
 *  @{
 */

    nh_css_Fragment nh_css_initFragment(
        nh_css_BoxTreeNode *Node_p, nh_css_Fragment *Parent_p, NH_CSS_FRAGMENT type, nh_api_CanvasType *Type_p
    );

    nh_css_FragmentTree nh_css_createFragmentTree(
        nh_css_BoxTreeNode *Node_p, nh_api_CanvasType *Type_p
    );
    
/** @} */

#endif
