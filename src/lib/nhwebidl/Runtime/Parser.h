#ifndef NH_WEBIDL_PARSER_H
#define NH_WEBIDL_PARSER_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "Tokenizer.h"

#include "../Common/Includes.h"

#include "../../nhcore/Util/List.h"
#include "../../nhcore/Util/String.h"

#endif

/** @addtogroup lib_nhwebidl_enums
 *  @{
 */

    typedef enum NH_WEBIDL_PARSE_NODE {
        NH_WEBIDL_PARSE_NODE_DEFINITIONS,
        NH_WEBIDL_PARSE_NODE_DEFINITION,
        NH_WEBIDL_PARSE_NODE_ARGUMENT_NAME_KEYWORD,
        NH_WEBIDL_PARSE_NODE_CALLBACK_OR_CLASS_OR_MIXIN,
        NH_WEBIDL_PARSE_NODE_CLASS_OR_MIXIN,
        NH_WEBIDL_PARSE_NODE_CLASS_REST,
        NH_WEBIDL_PARSE_NODE_PARTIAL,
        NH_WEBIDL_PARSE_NODE_PARTIAL_DEFINITION,
        NH_WEBIDL_PARSE_NODE_PARTIAL_CLASS_OR_PARTIAL_MIXIN,
        NH_WEBIDL_PARSE_NODE_PARTIAL_CLASS_REST,
        NH_WEBIDL_PARSE_NODE_CLASS_MEMBERS,
        NH_WEBIDL_PARSE_NODE_CLASS_MEMBER,
        NH_WEBIDL_PARSE_NODE_PARTIAL_CLASS_MEMBERS,
        NH_WEBIDL_PARSE_NODE_PARTIAL_CLASS_MEMBER,
        NH_WEBIDL_PARSE_NODE_INHERITANCE,
        NH_WEBIDL_PARSE_NODE_MIXIN_REST,
        NH_WEBIDL_PARSE_NODE_MIXIN_MEMBERS,
        NH_WEBIDL_PARSE_NODE_MIXIN_MEMBER,
        NH_WEBIDL_PARSE_NODE_INCLUDES_STATEMENT,
        NH_WEBIDL_PARSE_NODE_CALLBACK_REST_OR_CLASS,
        NH_WEBIDL_PARSE_NODE_CALLBACK_CLASS_MEMBERS,
        NH_WEBIDL_PARSE_NODE_CALLBACK_CLASS_MEMBER,
        NH_WEBIDL_PARSE_NODE_CONST,
        NH_WEBIDL_PARSE_NODE_CONST_VALUE,
        NH_WEBIDL_PARSE_NODE_BOOLEAN_LITERAL,
        NH_WEBIDL_PARSE_NODE_FLOAT_LITERAL,
        NH_WEBIDL_PARSE_NODE_CONST_TYPE,
        NH_WEBIDL_PARSE_NODE_READ_ONLY_MEMBER,
        NH_WEBIDL_PARSE_NODE_READ_ONLY_MEMBER_REST,
        NH_WEBIDL_PARSE_NODE_READ_WRITE_ATTRIBUTE,
        NH_WEBIDL_PARSE_NODE_INHERIT_ATTRIBUTE,
        NH_WEBIDL_PARSE_NODE_ATTRIBUTE_REST,
        NH_WEBIDL_PARSE_NODE_ATTRIBUTE_NAME,
        NH_WEBIDL_PARSE_NODE_ATTRIBUTE_NAME_KEYWORD,
        NH_WEBIDL_PARSE_NODE_OPTIONAL_READ_ONLY,
        NH_WEBIDL_PARSE_NODE_DEFAULT_VALUE,
        NH_WEBIDL_PARSE_NODE_OPERATION,
        NH_WEBIDL_PARSE_NODE_REGULAR_OPERATION,
        NH_WEBIDL_PARSE_NODE_SPECIAL_OPERATION,
        NH_WEBIDL_PARSE_NODE_SPECIAL,
        NH_WEBIDL_PARSE_NODE_OPERATION_REST,
        NH_WEBIDL_PARSE_NODE_OPTIONAL_OPERATION_NAME,
        NH_WEBIDL_PARSE_NODE_OPERATION_NAME,
        NH_WEBIDL_PARSE_NODE_OPERATION_NAME_KEYWORD,
        NH_WEBIDL_PARSE_NODE_ARGUMENT_LIST,
        NH_WEBIDL_PARSE_NODE_ARGUMENTS,
        NH_WEBIDL_PARSE_NODE_ARGUMENT,
        NH_WEBIDL_PARSE_NODE_ARGUMENT_REST,
        NH_WEBIDL_PARSE_NODE_ARGUMENT_NAME,
        NH_WEBIDL_PARSE_NODE_ELLIPSIS,
        NH_WEBIDL_PARSE_NODE_CONSTRUCTOR,
        NH_WEBIDL_PARSE_NODE_STRINGIFIER,
        NH_WEBIDL_PARSE_NODE_STRINGIFIER_REST,
        NH_WEBIDL_PARSE_NODE_STATIC_MEMBER,
        NH_WEBIDL_PARSE_NODE_STATIC_MEMBER_REST,
        NH_WEBIDL_PARSE_NODE_ITERABLE,
        NH_WEBIDL_PARSE_NODE_OPTIONAL_TYPE,
        NH_WEBIDL_PARSE_NODE_ASYNC_ITERABLE,
        NH_WEBIDL_PARSE_NODE_OPTIONAL_ARGUMENT_LIST,
        NH_WEBIDL_PARSE_NODE_READ_WRITE_MAPLIKE,
        NH_WEBIDL_PARSE_NODE_MAPLIKE_REST,
        NH_WEBIDL_PARSE_NODE_READ_WRITE_SETLIKE,
        NH_WEBIDL_PARSE_NODE_SETLIKE_REST,
        NH_WEBIDL_PARSE_NODE_NAMESPACE,
        NH_WEBIDL_PARSE_NODE_NAMESPACE_MEMBERS,
        NH_WEBIDL_PARSE_NODE_NAMESPACE_MEMBER,
        NH_WEBIDL_PARSE_NODE_DICTIONARY,
        NH_WEBIDL_PARSE_NODE_DICTIONARY_MEMBERS,
        NH_WEBIDL_PARSE_NODE_DICTIONARY_MEMBER,
        NH_WEBIDL_PARSE_NODE_DICTIONARY_MEMBERREST,
        NH_WEBIDL_PARSE_NODE_PARTIAL_DICTIONARY,
        NH_WEBIDL_PARSE_NODE_DEFAULT,
        NH_WEBIDL_PARSE_NODE_ENUM,
        NH_WEBIDL_PARSE_NODE_ENUM_VALUE_LIST,
        NH_WEBIDL_PARSE_NODE_ENUM_VALUE_LIST_COMMA,
        NH_WEBIDL_PARSE_NODE_ENUM_VALUE_LIST_STRING,
        NH_WEBIDL_PARSE_NODE_CALLBACK_REST,
        NH_WEBIDL_PARSE_NODE_TYPEDEF,
        NH_WEBIDL_PARSE_NODE_TYPE,
        NH_WEBIDL_PARSE_NODE_TYPE_WITH_EXTENDED_ATTRIBUTES,
        NH_WEBIDL_PARSE_NODE_SINGLE_TYPE,
        NH_WEBIDL_PARSE_NODE_UNION_TYPE,
        NH_WEBIDL_PARSE_NODE_UNION_MEMBER_TYPE,
        NH_WEBIDL_PARSE_NODE_UNION_MEMBER_TYPES,
        NH_WEBIDL_PARSE_NODE_DISTINGUISHABLE_TYPE,
        NH_WEBIDL_PARSE_NODE_PRIMITIVE_TYPE,
        NH_WEBIDL_PARSE_NODE_UNRESTRICTED_FLOAT_TYPE,
        NH_WEBIDL_PARSE_NODE_FLOAT_TYPE,
        NH_WEBIDL_PARSE_NODE_UNSIGNED_INTEGER_TYPE,
        NH_WEBIDL_PARSE_NODE_INTEGER_TYPE,
        NH_WEBIDL_PARSE_NODE_OPTIONAL_LONG,
        NH_WEBIDL_PARSE_NODE_STRING_TYPE,
        NH_WEBIDL_PARSE_NODE_PROMISE_TYPE,
        NH_WEBIDL_PARSE_NODE_RECORD_TYPE,
        NH_WEBIDL_PARSE_NODE_NULL,
        NH_WEBIDL_PARSE_NODE_BUFFER_RELATED_TYPE,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_LIST,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTES,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_REST,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_INNER,
        NH_WEBIDL_PARSE_NODE_OTHER,
        NH_WEBIDL_PARSE_NODE_OTHER_OR_COMMA,
        NH_WEBIDL_PARSE_NODE_IDENTIFIER_LIST,
        NH_WEBIDL_PARSE_NODE_IDENTIFIERS,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_NO_ARGS,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_ARG_LIST,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_IDENT,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_IDENT_LIST,
        NH_WEBIDL_PARSE_NODE_EXTENDED_ATTRIBUTE_NAMED_ARG_LIST,
        NH_WEBIDL_PARSE_NODE_NON_STANDARD_SPECIFIER,
    } NH_WEBIDL_PARSE_NODE;

/** @} */

/** @addtogroup lib_nhwebidl_structs
 *  @{
 */

    typedef struct nh_webidl_ParseNode {
        NH_WEBIDL_PARSE_NODE type;
        nh_webidl_Token *Token_p;
        nh_List Children;
    } nh_webidl_ParseNode;

    typedef struct nh_webidl_FragmentParseResult {
        nh_webidl_ParseNode *Root_p;
        nh_Array Tokens;
        nh_List SyntaxErrors;
    } nh_webidl_FragmentParseResult;

/** @} */

/** @addtogroup lib_nhwebidl_typedefs
 *  @{
 */

    typedef nh_webidl_FragmentParseResult (*nh_webidl_parse_f)(
        NH_BYTE *logName_p, NH_BYTE *fragment_p
    );

    typedef void (*nh_webidl_unparse_f)(
        nh_webidl_FragmentParseResult ParseResult
    );

/** @} */

/** @addtogroup lib_nhwebidl_vars
 *  @{
 */

    extern const NH_BYTE *NH_WEBIDL_PARSE_NODE_NAMES_PP[];
    extern size_t NH_WEBIDL_PARSE_NODE_NAMES_PP_COUNT;

/** @} */

/** @addtogroup lib_nhwebidl_functions
 *  @{
 */

    nh_webidl_FragmentParseResult nh_webidl_initFragmentParseResult(
    );

    nh_webidl_FragmentParseResult nh_webidl_parse(
        NH_BYTE *logName_p, NH_BYTE *fragment_p
    );

    void nh_webidl_unparse(
        nh_webidl_FragmentParseResult ParseResult
    );

    NH_WEBIDL_RESULT nh_webidl_getParseNodes(
        nh_webidl_ParseNode *Node_p, NH_WEBIDL_PARSE_NODE type, nh_List *Nodes_p
    );

/** @} */

#endif
