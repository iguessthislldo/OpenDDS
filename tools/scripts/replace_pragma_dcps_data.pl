#!/usr/bin/perl

use strict;
use warnings;

use File::Temp qw/tempfile/;
use File::Find qw/find/;

sub get_dcps_data_types {
  my @types = (); 
  open(my $fd, $_);
  while (my $line = <$fd>) {
    if ($line =~ /^#pragma DCPS_DATA_TYPE\s+"(.*)"/) {
      my $type = "$1";
      chomp($type);
      push(@types, $type);
    }
  }
  close($fd);
  return @types;
}

sub process_file {
  return unless /\.idl$/;
  my @types = get_dcps_data_types($_);
  if (scalar @types) {
    print " - $File::Find::name\n";
    for my $type (@types) {
      print "   - $type\n";
    }
  }
}

if (!defined($ARGV[0]) || !-d $ARGV[0]) {
  print STDERR "Pass a directory with idl files to process.\n";
  exit(1);
}

my $topdir = $ARGV[0];
print "Searching $topdir for idl files\n";
find({wanted => \&process_file, follow => 0}, $topdir);
print "Done\n";
# my ($tmp_fd, $tmp_filename) = tempfile();
# close($tmp_fd);
# unlink($tmp_filename)
#   or warn "Unable to delete temporary file $tmp_filename: $!";
