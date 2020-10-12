#include <string>
#include <cstring>
#include <algorithm>

#include <gtest/gtest.h>

extern "C" {
#include "../project/include/utils.h"
}

const std::string TEST_PATH = "./test/test_database/";
TEST(FileIsEmpty, test2){
    FILE* example1 = nullptr;
    ASSERT_EQ(read_base(example1,(TEST_PATH +"case1").c_str()), EXIT_NORMAL) <<
    "Read_base normal check empty file";
    ASSERT_EQ(read_base(example1," "), EXIT_FAILURE) <<
    "Error with fake path in";
}

TEST(TryToSort, test2){
    FILE* example2 = NULL;
    example2 = fopen((TEST_PATH + "case3").c_str(), "r");
    char** test_paragraph1 = NULL;
    test_paragraph1 = alloc_for_array(test_paragraph1, 3);
    char** test_paragraph2 = NULL;
    test_paragraph2 = alloc_for_array(test_paragraph2, 3);
    const char row1[] = "2           squidvard      tentickles          2100.00\n";
    const char row2[] = "11          petr           ivanov              3100.00\n";
    const char row3[] = "21          anton          kazakov              234.00\n";
    char* test_check[3];
    test_check[0] = const_cast<char *>(row1);
    test_check[1] = const_cast<char *>(row2);
    test_check[2] = const_cast<char *>(row3);
    EXPECT_NE(write_to_memory(example2, test_paragraph2, (TEST_PATH + "case3").c_str()), nullptr);

    EXPECT_NE(write_to_memory(example2, test_paragraph1, (TEST_PATH + "case3").c_str()), nullptr);
    ASSERT_EQ(sort_str(test_paragraph1, test_paragraph2, 3), EXIT_SUCCESS);

    const char* test[3];
    test[0] = test_paragraph2[0];
    test[1] = test_paragraph2[1];
    test[2] = test_paragraph2[2];
    for (size_t i = 0; i < 3; i++)
        ASSERT_STREQ(test_check[i], test[i]);
    free_alloc(test_paragraph1, 3);
    free_alloc(test_paragraph2, 3);
    fclose(example2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}