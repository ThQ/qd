#ifndef T_MAP
#define T_MAP t::Map

#include "t/Object.h"
#include "t/String.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_MAP(m) \
   DEPRECATED(); \
   SVM_ASSERT_NOT_NULL(m); \
   if (m->cls != NS_TYPE::tMAP) \
   { \
      FATAL("Should be of type <system.Map>.\n"); \
      abort();\
   }
#else
   #define SVM_ASSERT_MAP(m) DEPRECATED();
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_MAP(m) \
   DEPRECATED(); \
   SVM_CHECK_NOT_NULL(m); \
   if (m->cls != t::tMAP) \
   { \
      WARNING("Bad type given, expected <system.Map>.\n"); \
   }
#else
   #define SVM_CHECK_MAP(m) DEPRECATED();
#endif

namespace t
{
   extern T_OBJECT* tMAP;

   class Map : public Object
   {
      public: int length;
      public: T_OBJECT** keys;
      public: T_OBJECT** items;

      public: Map();

      /**
       * Asserts that an object is of type t::Map.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         ASSERT_NOT_NULL(NS_TYPE::tMAP);
         T_OBJECT::assert_type(obj, NS_TYPE::tMAP);
      }

      public: static T_OBJECT* build();

      /*
       * Checks if an object is of type t::Map.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tMAP);
      }

      public: static T_OBJECT* clear(T_OBJECT* map);
      public: static int find_key(Map* map, T_OBJECT* key);
      public: static T_OBJECT* set_item(T_OBJECT* map, T_OBJECT* key, T_OBJECT* value);
      public: static T_OBJECT* set_item(T_OBJECT* map, std::string key, std::string value);
      public: static T_OBJECT* slice(T_OBJECT* map, T_OBJECT* key1, T_OBJECT* key2);
   };
}

#endif
