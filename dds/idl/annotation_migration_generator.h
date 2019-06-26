/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef ANNOTATION_MIGRATION_GENERATOR_HEADER
#define ANNOTATION_MIGRATION_GENERATOR_HEADER

#include "dds_generator.h"

class annotation_migration_generator : public dds_generator {
public:
  annotation_migration_generator();

  bool gen_struct(AST_Structure* node, UTL_ScopedName* name,
    const std::vector<AST_Field*>&, AST_Type::SIZE_TYPE, const char*);

  bool gen_enum(AST_Enum*, UTL_ScopedName*, const std::vector<AST_EnumVal*>&,
    const char*)
  {
    return true;
  }

  bool gen_typedef(AST_Typedef*, UTL_ScopedName*, AST_Type*, const char*)
  {
    return true;
  }

  bool gen_union(AST_Union*, UTL_ScopedName*,
    const std::vector<AST_UnionBranch*>&, AST_Type*, const char*)
  {
    return true;
  }
};

#endif
