#include "data_handler/data_object.h"
#include "data_handler/data_object/builders/data_object_builder.h"

namespace engine::data_handler {

class DataObject::Impl {
public:
  void SetValue(const std::string& key, const VariantValue& value) {
    data_[key] = value;
  }

  const VariantValue& GetValue(const std::string& key) const {
    auto it = data_.find(key);
    if (it != data_.end()) {
      return it->second;
    }
    throw std::runtime_error("Key not found: " + key);
  }

  void RemoveKey(const std::string& key) {
    auto it = data_.find(key);
    if (it != data_.end()) {
      data_.erase(it);
    } else {
      throw std::runtime_error("Key not found: " + key);
    }
  }

  const std::unordered_map<std::string, VariantValue>& GetData() const {
    return data_;
  }

 private:
  std::unordered_map<std::string, VariantValue> data_;

};

DataObject::DataObject() : impl_(std::make_shared<Impl>()) {}

void DataObject::SetValue(const std::string& key, const VariantValue& value) {
  impl_->SetValue(key, value);
}

const VariantValue& DataObject::GetValue(const std::string& key) const {
  return impl_->GetValue(key);
}

void DataObject::RemoveKey(const std::string& key) {
  impl_->RemoveKey(key);
}

const std::unordered_map<std::string, VariantValue> &DataObject::GetData() const {
  return impl_->GetData();
}

DataObject DataObject::Parse(const entities::GameObject &object) {
  return DataObjectBuilder()
      .WithScriptName(object)
    .WithTransform(object)
    .Build();
}
}