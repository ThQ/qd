#ifndef TYPES__H
#define TYPES__H 1

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "log.h"

#define PRTF_i1 "d"
#define PRTF_i2 "d"
#define PRTF_i3 "d"
#define PRTF_i4 "ld"

#define PRTF_u1 "u"
#define PRTF_u2 "u"
#define PRTF_u3 "u"
#define PRTF_u4 "lu"

#define T__IS_LITERAL_TYPE(type)       ((type) >= 10 && (type) <= 30)
#define T__IS_NOT_LITERAL_TYPE(type)   (type < 10 || type > 30)
#define T__IS_NOT_VALUE_TYPE(type)     (type < 10 || type > 30)
#define T__IS_OBJECT_TYPE(type)        ((type) >= 49 && (type) <=62)
#define T__IS_VALUE_TYPE(type)         ((type) >= 10 && (type) <= 30)
#define T__IS_TYPE(type)               (((uchar)t::TYPE_SLOTS[type]) != 0)
#define T__SLOTS(type)                 ((uchar)t::TYPE_SLOTS[type])

#define T__INT2VALUE(val)              ((t::Value)((int)(val)))
#define T__OBJECT2VALUE(val)           ((t::Value)((t::Object)(val)))
#define T__UINT2VALUE(val)             ((t::Value)((uint)(val)))
#define T__VALUE2OBJECT(val)           ((t::Object)((t::Value)(val)))
#define ASSERT_TYPE(type)              ASSERT(T__IS_TYPE(type), "UNKNOWN_TYPE (.type %u)", (uint)type)

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

typedef unsigned char   u1;
typedef unsigned short  u2;
typedef unsigned int    u3;
typedef unsigned long   u4;

typedef char            i1;
typedef short           i2;
typedef int             i3;
typedef long            i4;

namespace t
{
   extern const uchar TYPE_SLOTS[256];
   extern const char* TYPE_NAMES[256];

   const uchar NULL_TYPE           = 0;
   const uchar NULL_SLOTS          = 1;

   const uchar UNDEFINED_TYPE      = 1;
   const uchar UNDEFINED_SLOTS      = 1;

   const uchar BOOL_TYPE           = 10;
   const uchar BOOL_SLOTS          = 1;
   typedef bool Bool;                        ///< Integer from 0 to 1. (Boolean or b)

   const uchar CHAR_TYPE           = 11;
   const uchar CHAR_SLOTS          = 1;
   typedef char Char;

   const uchar SHORT_TYPE          = 12;
   const uchar SHORT_SLOTS         = 1;
   typedef char Short;

   const uchar INT_TYPE            = 13;
   const uchar INT_SLOTS           = 1;
   typedef int Int;

   const uchar LONG_TYPE           = 14;
   const uchar LONG_SLOTS          = 2;
   typedef long Long;

   const uchar LONG_LONG_TYPE      = 15;
   const uchar LONG_LONG_SLOTS     = 4;
   typedef long long LongLong;

   const uchar INT8_TYPE           = 16;
   const uchar INT8_SLOTS          = 1;
   typedef int8_t Int8;       ///< Integer from -128 to 127. (Char or c)

   const uchar INT16_TYPE          = 17;
   const uchar INT16_SLOTS         = 1;
   typedef int16_t Int16;     ///< Integer from -32.768 to 32.767. (Short or h)

   const uchar INT32_TYPE          = 18;
   const uchar INT32_SLOTS         = 1;
   typedef int32_t Int32;     ///< Integer from -2.147.483.648 to 2.147.483.647. (Int or i)

   const uchar INT64_TYPE          = 19;
   const uchar INT64_SLOTS         = 2;
   typedef int64_t Int64;     ///< Integer from -9.223.372.036.854.775.808 to 9.223.372.036.854.775.807. (Long or l)

   const uchar U_CHAR_TYPE         = 20;
   const uchar U_CHAR_SLOTS        = 1;
   typedef char UChar;

   const uchar U_SHORT_TYPE        = 21;
   const uchar U_SHORT_SLOTS       = 1;
   typedef char UShort;

   const uchar U_INT_TYPE          = 22;
   const uchar U_INT_SLOTS         = 1;
   typedef int UInt;

   const uchar U_LONG_TYPE         = 23;
   const uchar U_LONG_SLOTS        = 2;
   typedef long ULong;

   const uchar U_LONG_LONG_TYPE    = 24;
   const uchar U_LONG_LONG_SLOTS   = 4;
   typedef long long ULongLong;

   const uchar U_INT8_TYPE         = 25;
   const uchar U_INT8_SLOTS        = 1;
   typedef uint8_t UInt8;     ///< Unsigned integer from 0 to 255. (Unsigned char or C)

   const uchar U_INT16_TYPE        = 26;
   const uchar U_INT16_SLOTS       = 1;
   typedef uint16_t UInt16;   ///< Unsigned integer from 0 to 65.535. (Unsigned short or H)

   const uchar U_INT32_TYPE        = 27;
   const uchar U_INT32_SLOTS       = 1;
   typedef uint32_t UInt32;   ///< Unsigned integer from 0 to 4.294.967.295. (Unsigned int or I)

   const uchar U_INT64_TYPE        = 28;
   const uchar U_INT64_SLOTS       = 2;
   typedef uint64_t UInt64;   ///< Unsigned integer from 0 to 18.446.744.073.709.551.615. (Unsigned long or L)

   const uchar OBJECT_TYPE         = 49;
   const uchar OBJECT_SLOTS        = 1;

   const uchar ARRAY_TYPE          = 50;
   const uchar ARRAY_SLOTS         = 1;

   const uchar LIST_TYPE           = 51;
   const uchar LIST_SLOTS          = 1;

   const uchar BLOCK_TYPE          = 52;
   const uchar BLOCK_SLOTS         = 1;

   const uchar CLASS_TYPE          = 53;
   const uchar CLASS_SLOTS         = 1;

   const uchar EXCEPTION_TYPE      = 54;
   const uchar EXCEPTION_SLOTS     = 1;

   const uchar FUNCTION_TYPE       = 55;
   const uchar FUNCTION_SLOTS      = 1;

   const uchar MAP_TYPE            = 56;
   const uchar MAP_SLOTS           = 1;

   const uchar STRING_TYPE         = 57;
   const uchar STRING_SLOTS        = 1;

   const uchar UNICODE_STRING_TYPE = 58;
   const uchar UNICODE_STRING_SLOTS= 1;

   const uchar USER_OBJECT_TYPE    = 59;
   const uchar USER_OBJECT_SLOTS   = 1;

   const uchar HEAP_OBJECT_TYPE    = 60;
   const uchar HEAP_OBJECT_SLOTS   = 1;

   const uchar REGISTER_VALUE_TYPE = 61;
   const uchar REGISTER_VALUE_SLOTS = 1;

   const uchar DESTINATION_REGISTER_VALUE_TYPE = 62;
   const uchar DESTINATION_REGISTER_VALUE_SLOTS = 1;
   typedef void* Value;

   typedef Value (*CastToStringFunction)(Value);
   typedef Value (*InitializeFunction)();
   typedef void (*DestroyFunction)(Value);
   typedef void (*PrintFunction)(Value);
   typedef void (*PrintLineFunction)(Value);

   inline const char* get_type_name(ushort type)
   {
      return t::TYPE_NAMES[type];
   }

   inline uchar get_type_slots(ushort nType)
   {
      ASSERT(t::TYPE_SLOTS[nType] != 0, "You requested slots from an invalid type.");
      return t::TYPE_SLOTS[nType];
   }

   void print_line_value(ushort nType, Value pValue);
}


#endif
