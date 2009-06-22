#ifndef TYPES_H
#define TYPES_H

typedef short Short;
typedef unsigned short UShort;

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
   typedef bool Bool;         ///< Integer from 0 to 1. (Boolean or b)

   const ushort INT8_TYPE = 3;
   typedef int16_t Int8;      ///< Integer from -128 to 127. (Char or c)

   const ushort INT16_TYPE = 4;
   typedef int16_t Int16;     ///< Integer from -32.768 to 32.767. (Short or s)

   const ushort INT32_TYPE = 5;
   typedef int32_t Int32;     ///< Integer from -2.147.483.648 to 2.147.483.647. (Int or i)

   const ushort INT64_TYPE = 6;
   typedef int16_t Int64;     ///< Integer from -9.223.372.036.854.775.808 to 9.223.372.036.854.775.807. (Long or l)

   const ushort UINT8_TYPE = 7;
   typedef uint8_t UInt8;     ///< Unsigned integer from 0 to 255. (Unsigned char or C)

   const ushort UINT16_TYPE = 8;
   typedef uint16_t UInt16;   ///< Unsigned integer from 0 to 65.535. (Unsigned short or S)

   const ushort UINT32_TYPE = 9;
   typedef uint32_t UInt32;   ///< Unsigned integer from 0 to 4.294.967.295. (Unsigned int or I)

   const ushort UINT64_TYPE = 10;
   typedef uint64_t UInt64;   ///< Unsigned integer from 0 to 18.446.744.073.709.551.615. (Unsigned long or L)

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

   inline const char* cast_type_to_string(ushort type)
   {
      const char* pszCasted;

      switch (type)
      {
         case NULL_TYPE: pszCasted = "Null"; break;
         case UNDEFINED_TYPE: pszCasted = "Undefined"; break;
         case BOOL_TYPE: pszCasted = "Bool"; break;
         case INT8_TYPE: pszCasted = "Int8";
         case INT16_TYPE: pszCasted = "Int16";
         case INT32_TYPE: pszCasted = "Int32";
         case INT64_TYPE: pszCasted = "Int64";
         case UINT8_TYPE: pszCasted = "UInt8";
         case UINT16_TYPE: pszCasted = "UInt16";
         case UINT32_TYPE: pszCasted = "UInt32";
         case UINT64_TYPE: pszCasted = "UInt64";
         case ARRAY_TYPE: pszCasted = "Array";
         case LIST_TYPE: pszCasted = "List";
         case BLOCK_TYPE: pszCasted = "Block";
         case CLASS_TYPE: pszCasted = "Class";
         case EXCEPTION_TYPE: pszCasted = "Exception";
         case FUNCTION_TYPE: pszCasted = "Function";
         case MAP_TYPE: pszCasted = "Map";
         case STRING_TYPE: pszCasted = "String";
         case UNICODE_STRING_TYPE: pszCasted = "UnicodeString";
         case USER_OBJECT_TYPE: pszCasted = "UserObject";
         default: FATAL("Unknown type %d.\n", type); abort();
      }
      return pszCasted;
   }
}


#endif
