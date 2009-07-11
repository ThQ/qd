#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#define T__IS_LITERAL_TYPE(type) ((type) >= 2 && (type) <= 10)
#define T__IS_NOT_LITERAL_TYPE(type) (type < 2 || type > 10)

typedef short Short;
typedef unsigned short UShort;
typedef unsigned short ushort;

//typedef int Int;
typedef unsigned int UInt;
typedef unsigned int uint;

typedef long Long;
typedef unsigned long ULong;
typedef unsigned long ulong;

typedef long long longlong;
typedef unsigned long long ulonglong;

namespace t
{
   const ushort NULL_TYPE = 0;
   const ushort UNDEFINED_TYPE = 1;
   const ushort BOOL_TYPE = 2;
   const ushort INT8_TYPE = 3;
   const ushort INT16_TYPE = 4;
   const ushort INT32_TYPE = 5;
   const ushort INT64_TYPE = 6;
   const ushort UINT8_TYPE = 7;
   const ushort UINT16_TYPE = 8;
   const ushort UINT32_TYPE = 9;
   const ushort UINT64_TYPE = 10;

   const ushort ARRAY_TYPE = 11;
   const ushort LIST_TYPE = 12;
   const ushort BLOCK_TYPE = 13;
   const ushort CLASS_TYPE = 14;
   const ushort EXCEPTION_TYPE = 15;
   const ushort FUNCTION_TYPE = 16;
   const ushort MAP_TYPE = 17;
   const ushort STRING_TYPE = 18;
   const ushort UNICODE_STRING_TYPE = 19;
   const ushort USER_OBJECT_TYPE = 20;

   typedef void* Value;       ///< A pointer.
   typedef bool Bool;         ///< Integer from 0 to 1. (Boolean or b)
   typedef int8_t Int8;       ///< Integer from -128 to 127. (Char or c)
   typedef int16_t Int16;     ///< Integer from -32.768 to 32.767. (Short or s)
   typedef int32_t Int32;     ///< Integer from -2.147.483.648 to 2.147.483.647. (Int or i)
   typedef int64_t Int64;     ///< Integer from -9.223.372.036.854.775.808 to 9.223.372.036.854.775.807. (Long or l)
   typedef uint8_t UInt8;     ///< Unsigned integer from 0 to 255. (Unsigned char or C)
   typedef uint16_t UInt16;   ///< Unsigned integer from 0 to 65.535. (Unsigned short or S)
   typedef uint32_t UInt32;   ///< Unsigned integer from 0 to 4.294.967.295. (Unsigned int or I)
   typedef uint64_t UInt64;   ///< Unsigned integer from 0 to 18.446.744.073.709.551.615. (Unsigned long or L)

   typedef Value (*CastToStringFunction)(Value);
   typedef bool (*DestroyFunction)(Value);
   typedef void (*PrintFunction)(Value);
   typedef void (*PrintLineFunction)(Value);

   inline const char* cast_type_to_string(ushort type)
   {
      const char* pszCasted;

      switch (type)
      {
         case NULL_TYPE: pszCasted = "Null"; break;
         case UNDEFINED_TYPE: pszCasted = "Undefined"; break;
         case BOOL_TYPE: pszCasted = "Bool"; break;
         case INT8_TYPE: pszCasted = "Int8"; break;
         case INT16_TYPE: pszCasted = "Int16"; break;
         case INT32_TYPE: pszCasted = "Int32"; break;
         case INT64_TYPE: pszCasted = "Int64"; break;
         case UINT8_TYPE: pszCasted = "UInt8"; break;
         case UINT16_TYPE: pszCasted = "UInt16"; break;
         case UINT32_TYPE: pszCasted = "UInt32"; break;
         case UINT64_TYPE: pszCasted = "UInt64"; break;
         case ARRAY_TYPE: pszCasted = "Array"; break;
         case LIST_TYPE: pszCasted = "List"; break;
         case BLOCK_TYPE: pszCasted = "Block"; break;
         case CLASS_TYPE: pszCasted = "Class"; break;
         case EXCEPTION_TYPE: pszCasted = "Exception"; break;
         case FUNCTION_TYPE: pszCasted = "Function"; break;
         case MAP_TYPE: pszCasted = "Map"; break;
         case STRING_TYPE: pszCasted = "String"; break;
         case UNICODE_STRING_TYPE: pszCasted = "UnicodeString"; break;
         case USER_OBJECT_TYPE: pszCasted = "UserObject"; break;
         default: FATAL("Unknown type %d.\n", type); abort();
      }
      return pszCasted;
   }
}


#endif
