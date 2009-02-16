#include <gtest/gtest.h>

#include "svm/Array.h"
#include "svm/EngineStarter.h"

TEST(test_array, test_array_build)
{
   svm::EngineStarter starter;
   starter.setup();

   starter.tear_down();
}

int
main(int argc, char *argv[])
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

