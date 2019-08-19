/*
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include <fstream>
#include <string>
#include <vector>

#include <ace/OS_NS_sys_stat.h>

#include "python_generator.h"
#include "be_extern.h"

namespace {
  std::vector<std::string>
  sn_to_strvec(UTL_ScopedName* x)
  {
    std::vector<std::string> rv;
    for (; x; x = static_cast<UTL_ScopedName*>(x->tail())) {
      const char* element = x->head()->get_string();
      if (element[0]) {
        rv.push_back(element);
      }
    }
    return rv;
  }

  bool
  open_python_file(std::ofstream& stream, UTL_ScopedName* name)
  {
    /*
     * Convert IDL modules to Python modules.
     */
    std::vector<std::string> names = sn_to_strvec(name);
    std::string path = be_global->output_dir_.c_str();
    const char* ext = ".py";
    const char* init = "__init__.py";
    if (names.size() > 1) {
      const size_t last = names.size() - 1;
      const size_t second_last = names.size() - 2;
      for (size_t i = 0; i < last; i++) {
        std::string& n = names[i];
        if (i == second_last) {
          path += n + ext;
        } else {
          path += n + "/";
          if (ACE_OS::mkdir(path.c_str()) && errno != EEXIST) {
            ACE_ERROR((LM_ERROR,
              ACE_TEXT("Error creating directories for Python module.\n")));
            return false;
          }
          ACE_stat s;
          const std::string init_path = path + init;
          if (ACE_OS::stat(init_path.c_str(), &s)) {
            if (!be_global->writeFile(init_path.c_str(), "")) {
              return false;
            }
          }
        }
      }
    } else {
      path = be_global->filename_base() + ext;
    }

    stream.open(path);
    if (!stream.is_open()) {
      ACE_ERROR((LM_ERROR,
        ACE_TEXT("Error opening Python module: %C\n"), path.c_str()));
    }
    stream
      << "import dataclasses" << std::endl
      << "import enum" << std::endl
      << "from typing import Any" << std::endl;
    return stream.is_open();
  }
}

void
python_generator::gen_includes()
{
  /* be_global->add_include("<Python.h>", BE_GlobalData::STREAM_H); */
}

bool
python_generator::gen_enum(
  AST_Enum*, UTL_ScopedName*,
  const std::vector<AST_EnumVal*>&, const char*)
{
  return true;
}

bool
python_generator::gen_union(
  AST_Union*, UTL_ScopedName*,
  const std::vector<AST_UnionBranch*>&,
  AST_Type*, const char*)
{
  return true;
}

bool
python_generator::gen_struct(
  AST_Structure* node, UTL_ScopedName* name,
  const std::vector<AST_Field*>& fields,
  AST_Type::SIZE_TYPE, const char*)
{
  std::ofstream python_file;
  if (!open_python_file(python_file, name)) {
    return false;
  }

  python_file << std::endl
    << "@dataclasses.dataclass" << std::endl
    << "class " << node->local_name()->get_string() << ":" << std::endl;

  for (std::vector<AST_Field*>::const_iterator pos = fields.begin(),
       done = fields.end(); pos != done; ++pos) {
    AST_Field* field = *pos;
    python_file
      << "  " << field->local_name()->get_string() << ": Any = None" << std::endl;
  }

  return true;
}

bool
python_generator::gen_typedef(
  AST_Typedef*, UTL_ScopedName*,
  AST_Type* /*type*/, const char*)
{
  return true;
}
