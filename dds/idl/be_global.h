/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef OPENDDS_IDL_BE_GLOBAL_H
#define OPENDDS_IDL_BE_GLOBAL_H

#include "ace/SString.h"
#include "idl_defines.h"
#include "utl_scoped_name.h"

#include <string>
#include <sstream>
#include <set>
#include <vector>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#ifndef TAO_IDL_HAS_ANNOTATIONS
#  error "Annotation support in tao_idl is required, please use a newer version of TAO"
#endif

class AST_Generator;
class AST_Decl;
class UTL_Scope;
class AST_Structure;
class AST_Field;
class AST_Union;
class AST_Annotation_Decl;

// Defines a class containing all back end global data.

class BE_GlobalData {
public:
  // = TITLE
  //    BE_GlobalData
  //
  // = DESCRIPTION
  //    Storage of global data specific to the compiler back end
  //
  BE_GlobalData();

  virtual ~BE_GlobalData();

  // Data accessors.

  const char* holding_scope_name() const;

  void destroy();
  // Cleanup function.

  const char* filename() const;
  void filename(const char* fname);

  ACE_CString spawn_options();
  // Command line passed to ACE_Process::spawn. Different
  // implementations in IDL and IFR backends.

  void parse_args(long& i, char** av);
  // Parse args that affect the backend.

  void open_streams(const char* filename);

  std::ostringstream header_, impl_, idl_, itl_, facets_header_, facets_impl_,
    lang_header_;
  ACE_CString header_name_, impl_name_, idl_name_, itl_name_,
    facets_header_name_, facets_impl_name_, lang_header_name_,
    output_dir_, tao_inc_pre_;

  /// Contents of the idl_file
  std::vector<std::string> idl_file_contents_;

  ///print message to all open streams
  void multicast(const char* message);

  enum stream_enum_t {
    STREAM_H, STREAM_CPP, STREAM_IDL, STREAM_ITL,
    STREAM_FACETS_H, STREAM_FACETS_CPP,
    STREAM_LANG_H
  };

  void reset_includes();

  void add_include(const char* file, stream_enum_t which = STREAM_H);

  /// Called to indicate that OpenDDS marshaling (serialization) code for the
  /// current file will depend on marshaling code generated for the indicated
  /// file.  For example, if the current file is A.idl and it contains a struct
  /// which has a field of type B, defined in B.idl, the full path to B.idl is
  /// passed to this function.
  void add_referenced(const char* file);

  void set_inc_paths(const char* cmdline);
  void add_inc_path(const char* path);

  std::string get_include_block(stream_enum_t which);

  ACE_CString export_macro() const;
  void export_macro(const ACE_CString& str);

  ACE_CString export_include() const;
  void export_include(const ACE_CString& str);

  ACE_CString versioning_name() const;
  void versioning_name(const ACE_CString& str);

  ACE_CString versioning_begin() const;
  void versioning_begin(const ACE_CString& str);

  ACE_CString versioning_end() const;
  void versioning_end(const ACE_CString& str);

  ACE_CString pch_include() const;
  void pch_include(const ACE_CString& str);

  const std::set<std::string>& cpp_includes() const;
  void add_cpp_include(const std::string& str);

  bool java() const;
  void java(bool b);

  bool no_default_gen() const;
  void no_default_gen(bool b);

  /// Returns true if not to generate *TypeSupportImpl.* files
  bool no_impl() const;

  /// Do not generate absolutely anything by default
  void suppress_default_output();

  bool itl() const;
  void itl(bool b);

  bool v8() const;
  void v8(bool b);

  bool rapidjson() const;
  void rapidjson(bool b);

  bool face_ts() const;
  void face_ts(bool b);

  bool annotation_migration() const;
  void annotation_migration(bool b);

  ACE_CString java_arg() const;
  void java_arg(const ACE_CString& str);

  enum LanguageMapping {
    LANGMAP_NONE, ///< Don't generate, let tao_idl handle it
    LANGMAP_FACE_CXX, ///< Generate C++ language mapping from FACE spec
    LANGMAP_SP_CXX, ///< Generate C++ language mapping for Safety Profile
    LANGMAP_CXX11, ///< Generate OMG IDL-to-C++11
  };

  LanguageMapping language_mapping() const;
  void language_mapping(LanguageMapping lm);

  ACE_CString sequence_suffix() const;
  void sequence_suffix(const ACE_CString& str);

  bool suppress_idl() const { return suppress_idl_; }
  bool suppress_typecode() const { return suppress_typecode_; }

  static bool writeFile(const char* fileName, const std::string &content);

  /**
   * Cache annotations for use during parsing.
   */
  void cache_annotations();

  /**
   * Based on annotations and global_default_nested_, determine if a type is a
   * topic type and needs type support.
   *
   * Does not check for specific types of types (struct vs array).
   */
  bool is_topic_type(AST_Decl* node);

  /**
   * Global default for if a type is nested (is_nested_type = !is_topic_type)
   * Set to true by passing --default-nested
   */
  bool global_default_nested_;

  /**
   * Check if a struct field has been declared a key.
   */
  bool is_key(AST_Field* node);

  /**
   * Check if the discriminator in a union has been declared a key.
   */
  bool has_key(AST_Union* node);

  /**
   * Give a warning that looks like tao_idl's, but out of context of tao_idl.
   */
  void warning(const char* filename, unsigned lineno, const char* msg);

private:
  /// Name of the IDL file we are processing.
  const char* filename_;

  bool java_, suppress_idl_, suppress_typecode_,
    no_default_gen_, no_impl_, generate_itl_, generate_v8_,
    generate_rapidjson_, face_ts_, annotation_migration_;

  ACE_CString export_macro_, export_include_,
    versioning_name_, versioning_begin_, versioning_end_,
    pch_include_, java_arg_, seq_;
  std::set<std::string> cpp_includes_;

  LanguageMapping language_mapping_;

  /**
   * Hold these for the convenience of not having to do a lookup for the nodes
   */
  ///{
  AST_Annotation_Decl* topic_annotation_;
  AST_Annotation_Decl* key_annotation_;
  AST_Annotation_Decl* nested_annotation_;
  AST_Annotation_Decl* default_nested_annotation_;
  ///}

  bool is_nested(AST_Decl* node);
  bool is_default_nested(UTL_Scope* scope);
};

class BE_Comment_Guard {
public:

  BE_Comment_Guard(const char* type, const char* name);
  ~BE_Comment_Guard();

private:
  const char *type_, *name_;
};

#endif /* OPENDDS_IDL_BE_GLOBAL_H */
