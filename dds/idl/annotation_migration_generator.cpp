#include "annotation_migration_generator.h"

#include <iostream>

annotation_migration_generator::annotation_migration_generator()
{
}

bool
annotation_migration_generator::gen_struct(
  AST_Structure*, UTL_ScopedName* name,
  const std::vector<AST_Field*>&, AST_Type::SIZE_TYPE, const char*)
{
  std::string cxx = scoped(name);
  IDL_GlobalData::DCPS_Data_Type_Info* info = idl_global->is_dcps_type(name);
  if (info) {
    std::cout << cxx << std::endl;
  }
  return true;
}
