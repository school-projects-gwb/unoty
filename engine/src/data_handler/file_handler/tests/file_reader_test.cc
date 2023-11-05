#include "../file_handler.h"

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace engine::data_handler::tests {

class FileReaderTest : public testing::Test {

 protected:
  void SetUp() override {
    fh = *new FileHandler;
  }

  FileHandler fh;
};

TEST_F(FileReaderTest, CorrectlyParsesMockJson) {
  json j = fh.ReadFile(MOCK_JSON);
  EXPECT_EQ(j["name"], "Henk de Vries");
}

TEST_F(FileReaderTest, CorrectlyParsesToJsonObject) {
  auto a = fh.ReadFile(MOCK_JSON);
  EXPECT_EQ(typeid(a), typeid(json));
}

TEST_F(FileReaderTest, ExitsOnWrongFileType) {
  EXPECT_EXIT(fh.ReadFile("./mock.txt"), testing::ExitedWithCode(1), "DEATH");
}


} // namespace engine::data_handler::tests