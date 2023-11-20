#include "data_handler/file_handler/file_handler.h"

#include <string>
#include <memory>
#include <filesystem>

#include "gtest/gtest.h"

namespace engine::data_handler::tests {

class FileHandlerTest : public testing::Test {
 protected:
  void TearDown() override {
    if (std::filesystem::exists(MOCK_JSON_TEMP))
      std::remove(MOCK_JSON_TEMP);
  }
};

TEST_F(FileHandlerTest, ReadFileParsedJsonIsNotEmpty) {
  std::string s = FileHandler::GetInstance().ReadFile(MOCK_JSON);
  EXPECT_EQ(s.empty(), false);
}

TEST_F(FileHandlerTest, ReadFileThrowsErrorOnEmptyPath) {
  EXPECT_THROW(FileHandler::GetInstance().ReadFile(""), std::invalid_argument);
}

TEST_F(FileHandlerTest, ReadFileThrowsErrorOnNonJsonFile) {
  EXPECT_THROW(FileHandler::GetInstance().ReadFile("MOCKFILE.txt"), std::invalid_argument);
}

TEST_F(FileHandlerTest, WriteFileWritesFileSuccesfully) {
  FileHandler::GetInstance().WriteFile("MOCK2.json", R"({"name":"Henk de Vries")");
  EXPECT_EQ(FileHandler::GetInstance().ReadFile("MOCK2.json").empty(), false);
}

TEST_F(FileHandlerTest, WriteFileThrowsErrorOnEmptyPath) {
  EXPECT_THROW(FileHandler::GetInstance().WriteFile("", R"({"name":"Henk de Vries")"), std::invalid_argument);
}

TEST_F(FileHandlerTest, WriteFileThrowsErrorOnEmptyFile) {
  EXPECT_THROW(FileHandler::GetInstance().WriteFile(MOCK_JSON_TEMP, ""), std::invalid_argument);
}

} // namespace engine::data_handler::engine_tests