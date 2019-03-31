# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: code.rb 614 2008-09-29 12:41:40Z rfindeni $
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

class Code
	OPCODES = {
		"nop"   => 0b000000,
		"sleep" => 0b000001,
		"loadi" => 0b000010,
		"load"  => 0b000011,
		"store" => 0b000100,
		"jmp"   => 0b001000,
		"jmpc"  => 0b001010,
		"jmpz"  => 0b001011,
		"jump"  => 0b001000,
		"jumpc" => 0b001010,
		"jumpz" => 0b001011,
		"move"  => 0b001100,
		"and"   => 0b010000,
		"or"    => 0b010001,
		"xor"   => 0b010010,
		"not"   => 0b010011,
		"add"   => 0b010100,
		"addc"  => 0b010101,
		"sub"   => 0b010110,
		"subc"  => 0b010111,
		"comp"  => 0b011000,
		"inc"   => 0b011010,
		"dec"   => 0b011011,
		"shl"   => 0b011100,
		"shr"   => 0b011101,
		"shlc"  => 0b011110,
		"shrc"  => 0b011111
	}
	
	def initialize(name = "main")
		@name = name
		@pc = 0
		@code = []
	end

	def put(x)
		@code[@pc] = x
		@pc += 1
	end

	def prnt
		i = 0
		for c in @code
			printf("%04x: %04x\n", i, c)
			i = i + 1
		end
	end

	def writeFile(fileWriter, filename)
		File.open(filename, 'w') do |f|
			f.write(fileWriter::PRE)

			i = 0
			for c in @code
				f.write(sprintf(fileWriter::FORMAT, i, c)) if c
				i = i + 1
			end

			f.write(fileWriter::POST)
		end
	end

	attr_accessor :pc, :code
end
