#include "tst_create.h"

#include "my_testlib.h"

#include <gtest/gtest.h>

TEST(my_testlibapi, Create) {
    EXPECT_EQ(CreateLib(), true);

    EXPECT_NO_THROW(PostTask([]{}));
    EXPECT_NO_THROW(ExecTask([]{}));

    EXPECT_NO_THROW(ReleaseLib());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
