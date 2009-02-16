#ifndef SVM_MAP_H
#define SVM_MAP_H

#include "svm/Object.h"
#include "svm/String.h"

void svm_print(svm::Object* o);

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_MAP(m) SVM_ASSERT_NOT_NULL(m); if (m->cls != svm::map_type) {FATAL("Should be of type <system.Map>.\n");abort();}
#else
   #define SVM_ASSERT_MAP(m)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_MAP(m) SVM_CHECK_NOT_NULL(m);if (m->cls != svm::map_type){WARNING("Bad type given, expected <system.Map>.\n");}
#else
   #define SVM_CHECK_MAP(m)
#endif

namespace svm
{
   extern Object* map_type;

   class Map : public Object
   {
      public: int length;
      public: Object** keys;
      public: Object** items;

      public: Map();
      public: static Object* build();
      public: static bool check(Object* m);
      public: static Object* clear(Object* map);
      public: static int find_key(Map* map, Object* key);
      public: static void print(Object* map);
      public: static Object* set_item(Object* map, Object* key, Object* value);
      public: static Object* set_item(Object* map, std::string key, std::string value);
      public: static Object* slice(Object* map, Object* key1, Object* key2);
   };
}

#endif
