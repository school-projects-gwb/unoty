#include "gtest/gtest.h"
#include "data_handler/data_object.h"

namespace engine::data_handler::tests {

class DataObjectTest : public testing::Test {
 protected:
  DataObject data_object_;
};

class Player : public entities::GameObject {

};

// Test for setting and getting string values
TEST_F(DataObjectTest, SetGetStringValue) {
  std::string test_string = "Hello";
  data_object_.SetValue("test_string", test_string);
  EXPECT_EQ(std::get<std::string>(data_object_.GetValue("test_string")), test_string);
}

// Test for setting and getting int values
TEST_F(DataObjectTest, SetGetIntegerValue) {
  int test_int = 42;
  data_object_.SetValue("test_int", test_int);
  EXPECT_EQ(std::get<int>(data_object_.GetValue("test_int")), test_int);
}

// Test for setting and getting double values
TEST_F(DataObjectTest, SetGetDoubleValue) {
  double test_double = 3.14;
  data_object_.SetValue("test_double", test_double);
  EXPECT_EQ(std::get<double>(data_object_.GetValue("test_double")), test_double);
}

// Test for setting and getting boolean values
TEST_F(DataObjectTest, SetGetBooleanValue) {
  bool test_bool = true;
  data_object_.SetValue("test_bool", test_bool);
  EXPECT_EQ(std::get<bool>(data_object_.GetValue("test_bool")), test_bool);
}

// Test for setting and getting array values
TEST_F(DataObjectTest, SetGetVectorValue) {
  std::vector<DataObject> test_vector = { DataObject(), DataObject() };
  data_object_.SetValue("test_vector", test_vector);
  EXPECT_EQ(std::get<std::vector<DataObject>>(data_object_.GetValue("test_vector")).size(), test_vector.size());
}
// Test for setting and getting DataObject values
TEST_F(DataObjectTest, SetGetDataObjectValue) {
  DataObject nested_object;
  nested_object.SetValue("nestedKey", 100);
  data_object_.SetValue("nested_object", nested_object);
  const auto& retrieved_nested_object = std::get<DataObject>(data_object_.GetValue("nested_object"));
  EXPECT_EQ(std::get<int>(retrieved_nested_object.GetValue("nestedKey")), 100);
}

// Test for key not found exception
TEST_F(DataObjectTest, KeyNotFound) {
  try {
    const auto& value = data_object_.GetValue("nonExistentKey"); // Capture return value
    (void)value; // Explicitly ignore the unused variable
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error& err) {
    EXPECT_EQ(err.what(), std::string("Key not found: nonExistentKey"));
  } catch (...) {
    FAIL() << "Expected std::runtime_error";
  }
}

// Test for removing a key
TEST_F(DataObjectTest, RemoveKey) {
  data_object_.SetValue("testKey", 123);
  data_object_.RemoveKey("testKey");
  try {
    const auto& value = data_object_.GetValue("testKey"); // Capture return value
    (void)value; // Explicitly ignore the unused variable
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error& err) {
    EXPECT_EQ(err.what(), std::string("Key not found: testKey"));
  } catch (...) {
    FAIL() << "Expected std::runtime_error";
  }
}
// Test for overwriting an existing value
TEST_F(DataObjectTest, OverwriteValue) {
  data_object_.SetValue("testKey", 123);
  data_object_.SetValue("testKey", 456);
  EXPECT_EQ(std::get<int>(data_object_.GetValue("testKey")), 456);
}

// Test for the GetData() method
TEST_F(DataObjectTest, GetDataMethod) {
  std::string test_string = "Hello";
  int test_int = 42;

  data_object_.SetValue("test_string", test_string);
  data_object_.SetValue("test_int", test_int);

  const auto& data = data_object_.GetData();
  ASSERT_EQ(data.size(), 2);
  EXPECT_EQ(std::get<std::string>(data.at("test_string")), test_string);
  EXPECT_EQ(std::get<int>(data.at("test_int")), test_int);
}

// Test for parsing GameObject into DataObject
TEST_F(DataObjectTest, ParseGameObject) {
  Player player_game_object = Player();
  player_game_object.GetTransform()->Position = {5, 10};

  DataObject data_object = DataObject::Parse(player_game_object);
  auto transform_data = std::get<DataObject>(data_object.GetValue("transform"));

  EXPECT_EQ(std::get<std::string>(data_object.GetValue("script_name")), "Player");
  EXPECT_EQ(std::get<int>(transform_data.GetValue("position_x")), 5);
  EXPECT_EQ(std::get<int>(transform_data.GetValue("position_y")), 10);
}

// Test for setting and getting std::vector<int> values
TEST_F(DataObjectTest, SetGetVectorIntValue) {
  std::vector<int> test_vector = {1, 2, 3, 4, 5};
  data_object_.SetValue("test_vector_int", test_vector);
  EXPECT_EQ(std::get<std::vector<int>>(data_object_.GetValue("test_vector_int")), test_vector);
}

// Test for setting and getting C-style array values
TEST_F(DataObjectTest, SetGetCStyleArrayValue) {
  int test_array[] = {1, 2, 3, 4, 5};
  data_object_.SetArrayValue("test_array", test_array);
  auto retrievedArray = std::get<std::vector<int>>(data_object_.GetValue("test_array"));
  for (size_t i = 0; i < sizeof(test_array) / sizeof(test_array[0]); ++i) {
    EXPECT_EQ(retrievedArray[i], test_array[i]);
  }
}

}
