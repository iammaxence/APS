#!/usr/bin/perl

use strict;
use warnings;
use autodie qw(system);
use feature 'say';


# Since tests are ran in alphabetical order; keeping this list sorted
# should help debugging.
#
# Note that in the following list, the results are formed from a
# concatenation of the program's stdout with their result.
my %tests = (
    #    test name               =>    result
         'arg2'       			 => '5',
         'basic_fun'        	 => '5',
         'prog000'               => '42',
         'prog001'               => '42',
         'prog002'               => '42',
         'prog003'               => '42',
         'prog004'               => '42',
         'prog005'               => '42',
         'prog006'               => '42',
         'prog007'               => '42',
         'prog008'               => '42',
         'prog009'               => '42',
         'prog010'               => '42',
         'prog011'               => '42',
         'prog012'               => '42',
         'prog013'               => '42',
         'prog014'               => '42',
         'prog015'               => '42',         
    );

# Recompiling the vm
system("make --directory=src clean && make --directory=src ");
say "Compilation OK.\n\nRunning tests...\n";


# Running the tests
my ($err_count, $total) = (0, 0);

for my $test (sort keys %tests) {
    my $filename = "./tests/APS0_OK/$test.aps";
    my $res = `./src/as < $filename -e`;
    chomp $res;
    if ($res ne $tests{$test}) {
        $err_count++;
        say "[error] $test";
        say "  expected: $tests{$test}";
        say "  got: $res";
    } else {
        say "[OK] $test";
    }
    $total++;
}

# Outputting statistics
say "\n\nRun $total tests. $err_count failure" .
    ($err_count > 1 ? "s" : "") . ". " .
    ($total-$err_count) . " success" .
    ($total-$err_count > 1 ? "es" : "") . ".\n";
