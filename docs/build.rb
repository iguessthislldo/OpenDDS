# Generate Documentation using Asciidoctor
# Requires asciidoctor>=2.0.0, asciidoctor-diagram, and coderay ruby packages:
# gem install asciidoctor asciidoctor-diagram coderay

require 'asciidoctor'
require 'asciidoctor-diagram'
require 'asciidoctor-diagram/graphviz'

require 'fileutils'
require 'pathname'

# Basic Info
project = 'OpenDDS'
org = 'Object Computing, Inc.'
copyright = "2020, #{org}"

# Make sure we're in the docs directory
docs_path = Pathname.new(__dir__)
root_path = docs_path.parent()
FileUtils.cd(docs_path.to_s())

# Get Version Data
version_file_path = root_path / 'dds/Version.h'
version_file_contents = version_file_path.read()
major = version_file_contents.match(/DDS_MAJOR_VERSION (.*)$/)[1]
minor = version_file_contents.match(/DDS_MINOR_VERSION (.*)$/)[1]
micro = version_file_contents.match(/DDS_MICRO_VERSION (.*)$/)[1]
metadata_match = version_file_contents.match(/OPENDDS_VERSION_METADATA "(.*)"$/)
version = "#{major}.#{minor}.#{micro}"
if not metadata_match.nil?
  version = "#{version}-#{metadata_match[1]}"
end
is_release =
  version_file_contents.match(/OPENDDS_IS_RELEASE (.*)$/)[1] == "1" ?
    true : false

# Generate Documentation
dest_path = "build"
FileUtils.rm_rf(dest_path)
Asciidoctor.convert_file('index.adoc',
  :to_dir => dest_path,
  :mkdirs => true,
  :safe => 'unsafe',
  attributes: {
    'doctitle' => "#{project}",
    'author' => org,
    'orgname' => org,
    'copyright' => copyright,
    'lang' => 'en',
    'revnumber' => version,
    'opendds-version' => version,
    'opendds-is-release' => is_release ? 1 : nil,
    'source-language' => 'c++',
    'icons' => 'font',
  }
)
FileUtils.cp(docs_path / "devguide/devguide_dcps.png", dest_path)
