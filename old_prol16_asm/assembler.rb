#!/usr/bin/env ruby
# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: assembler.rb 614 2008-09-29 12:41:40Z rfindeni $
#
# ProlASM is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Foobar is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

$: << File.expand_path(File.dirname(__FILE__))
require 'parser.rb'

infile = nil
outfile = nil
debuglevel = 0

while i = ARGV.shift
	if i == "-h"
		puts "Prol16 Assembler"
		puts "Usage: ./assembler.rb -i infile -o outfile"
		exit
	elsif i == "-i"
		infile = ARGV.shift
	elsif i == "-o"
		outfile = ARGV.shift
	elsif i == "-d"
		debuglevel = Integer(ARGV.shift)
	else
		puts "Ignoring misplaced argument #{i}"
	end
end

raise "No input file specified." unless infile
p = Parser.new(infile, outfile, debuglevel)
p.parse
