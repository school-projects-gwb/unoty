#include "gtest/gtest.h"
#include "data_handler/serializer.h"

namespace engine::data_handler::tests {

class SerializerTest : public testing::Test {
 protected:
  static DataObject simple_data_object() {
    DataObject obj;
    obj.SetValue("string_value", std::string("Hello World"));
    obj.SetValue("int_value", 42);
    obj.SetValue("double_value", 3.14);
    obj.SetValue("bool_value", true);
    obj.SetValue("nested_object", nested_data_object()); // Defined below

    std::vector<std::string> string_vec = {"Hello", "World"};
    obj.SetValue("string_vector", string_vec);

    std::vector<int> int_vec = {1, 2, 3};
    obj.SetValue("int_vector", int_vec);

    std::vector<double> double_vec = {1.1, 2.2, 3.3};
    obj.SetValue("double_vector", double_vec);

    std::vector<bool> bool_vec = {true, false, true};
    obj.SetValue("bool_vector", bool_vec);

    return obj;
  }

  static DataObject nested_data_object() {
    DataObject nested_obj;
    nested_obj.SetValue("nested_int", 100);
    nested_obj.SetValue("nested_string", std::string("Nested"));
    return nested_obj;
  }

  static DataObject complex_data_object() {
    DataObject obj;
    obj.SetValue("nested_object", simple_data_object());
    std::vector<DataObject> test_vector = {simple_data_object(), simple_data_object()};
    obj.SetValue("test_vector", test_vector);
    return obj;
  }
};

TEST_F(SerializerTest, SimpleJsonSerializationDeserialization) {
  DataObject simple_obj = simple_data_object();
  std::string serialized = Serializer::Serialize(SerializerType::Json, simple_obj);
  DataObject deserialized_obj = Serializer::Deserialize(SerializerType::Json, serialized);

  // Test each value type
  EXPECT_EQ(std::get<std::string>(deserialized_obj.GetValue("string_value")), "Hello World");
  EXPECT_EQ(std::get<int>(deserialized_obj.GetValue("int_value")), 42);
  EXPECT_DOUBLE_EQ(std::get<double>(deserialized_obj.GetValue("double_value")), 3.14);
  EXPECT_EQ(std::get<bool>(deserialized_obj.GetValue("bool_value")), true);

  // Test vector types
  EXPECT_EQ(std::get<std::vector<std::string>>(deserialized_obj.GetValue("string_vector")), std::vector<std::string>({"Hello", "World"}));
  EXPECT_EQ(std::get<std::vector<int>>(deserialized_obj.GetValue("int_vector")), std::vector<int>({1, 2, 3}));
  EXPECT_EQ(std::get<std::vector<double>>(deserialized_obj.GetValue("double_vector")), std::vector<double>({1.1, 2.2, 3.3}));
  EXPECT_EQ(std::get<std::vector<bool>>(deserialized_obj.GetValue("bool_vector")), std::vector<bool>({true, false, true}));

  // Check serialization string for presence of key-value pairs
  EXPECT_NE(serialized.find("\"string_value\":\"Hello World\""), std::string::npos);
  EXPECT_NE(serialized.find("\"int_value\":42"), std::string::npos);
  EXPECT_NE(serialized.find("\"double_value\":3.14"), std::string::npos);
  EXPECT_NE(serialized.find("\"bool_value\":true"), std::string::npos);
  EXPECT_NE(serialized.find("\"string_vector\":[\"Hello\",\"World\"]"), std::string::npos);
  EXPECT_NE(serialized.find("\"int_vector\":[1,2,3]"), std::string::npos);
  EXPECT_NE(serialized.find("\"double_vector\":[1.1,2.2,3.3]"), std::string::npos);
  EXPECT_NE(serialized.find("\"bool_vector\":[true,false,true]"), std::string::npos);
}

TEST_F(SerializerTest, ComplexJsonSerializationDeserialization) {
  DataObject complex_obj = complex_data_object();
  std::string serialized = Serializer::Serialize(SerializerType::Json, complex_obj);
  DataObject deserialized_obj = Serializer::Deserialize(SerializerType::Json, serialized);

  // Test nested object
  auto nested_object = std::get<DataObject>(deserialized_obj.GetValue("nested_object"));
  EXPECT_EQ(std::get<std::string>(nested_object.GetValue("string_value")), "Hello World");

  // Test vector of DataObjects
  auto test_vector = std::get<std::vector<DataObject>>(deserialized_obj.GetValue("test_vector"));
  ASSERT_EQ(test_vector.size(), 2);  // Ensure there are two elements in the vector
  EXPECT_EQ(std::get<int>(test_vector[0].GetValue("int_value")), 42);
  EXPECT_EQ(std::get<std::string>(test_vector[1].GetValue("string_value")), "Hello World");

  // Check serialization string for presence of complex structures
  EXPECT_NE(serialized.find("\"nested_object\""), std::string::npos);
  EXPECT_NE(serialized.find("\"test_vector\""), std::string::npos);
}

} // namespace engine::data_handler::engine_tests
