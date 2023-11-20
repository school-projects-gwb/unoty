#include <cxxabi.h>
#include "data_object_builder.h"
namespace engine::data_handler {

DataObjectBuilder::DataObjectBuilder() : data_object_(std::make_unique<DataObject>()) {}


DataObjectBuilder &DataObjectBuilder::WithScriptName(const engine::entities::GameObject &game_object) {
  const std::type_info& info = typeid(game_object);

  int status = -1;
  std::unique_ptr<char, void(*)(void*)> res {
      abi::__cxa_demangle(info.name(), nullptr, nullptr, &status),
      std::free
  };

  std::string demangled_name = (status == 0) ? res.get() : info.name();

  size_t last_scope_operator = demangled_name.rfind("::");
  if (last_scope_operator != std::string::npos) {
    demangled_name = demangled_name.substr(last_scope_operator + 2);
  }

  data_object_->SetValue("script_name", demangled_name);

  return *this;
}

DataObjectBuilder &DataObjectBuilder::WithTransform(const engine::entities::GameObject &game_object) {
  auto transform = game_object.GetTransform();
  auto transform_data_object = DataObject();

  if (transform) {
    transform_data_object.SetValue("position_x", transform->Position.x);
    transform_data_object.SetValue("position_y", transform->Position.y);
    data_object_->SetValue("transform", transform_data_object);
  }
  return *this;
}

DataObject DataObjectBuilder::Build() {
  return std::move(*data_object_);
}

}