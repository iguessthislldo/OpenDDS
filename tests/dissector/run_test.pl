#!/usr/bin/perl

use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/../../tools/scripts/modules/";

use run_command;

my $tshark_stdout;
my $dissector_name = 'OpenDDS_Dissector_for_test';

if (scalar(@ARGV) != 1) {
}

sub tshark {
  my ($failed, $exit_status) = run_command::run_command(
    ["$ENV{WIRESHARK_SRC}/tshark", @_],
    capture_stdout => \$tshark_stdout,
    verbose => 1,
  );
  print(
    "begin stdout ------------------------------------------------------------------\n" .
    $tshark_stdout);
  if (length($tshark_stdout) == 0) {
    print("\n");
  }
  print("end stdout --------------------------------------------------------------------\n");
  return $failed;
}

print("Install Plugin ================================================================\n");

# TODO
# - Take directory from arguments or maybe envvar
# - Determine the name of the plugin file
# - Copy it

my $failed = 0;

print("Verify Dissector Plugin is Loaded =============================================\n");
if (tshark('-G', 'plugins')) {
  $failed = 1;
}
elsif ($tshark_stdout =~ /^$dissector_name/m) {
  print("Looks like $dissector_name was loaded\n");
}
else {
  print STDERR ("ERROR: Could not verify $dissector_name was loaded\n");
  $failed = 1;
}

print("Filter Samples ================================================================\n");
my $filter = 'opendds.sample.publication[14:2] == 01:02 && opendds.sample.id == SAMPLE_DATA';
if (tshark('-r', 'messenger.pcap', '-T', 'text', $filter)) {
  $failed = 1;
}

print("Dissect and Filter Sample Payload Contents ====================================\n");
my $field = 'opendds.sample.payload.Messenger.Message.subject_id';
if (tshark('-r', 'messenger.pcap', '-T', 'fields', '-e', $field, "$field < 100")) {
  $failed = 1;
}
my $value = '99';
if ($tshark_stdout =~ /$value/) {
  print("Found $value\n");
}
else {
  print STDERR ("ERROR: Could not find $value in the above output\n");
  $failed = 1;
}

exit($failed);
