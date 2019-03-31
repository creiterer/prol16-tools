# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: lexer.rb 614 2008-09-29 12:41:40Z rfindeni $
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

require 'strscan'

# this function is taken from http://snippets.dzone.com/posts/show/1040
class String
  #partitions a string based on regex.  matches are included in results
  #ex. 'a b  c'.partition(/ +/) returns ['a', ' ', 'b', '  ', 'c']
  #ex. ' b '.partition(/ +/) returns [' ', 'b', ' ']
  def partition(regex)
    results = []
    s = StringScanner.new(self)
    last_pos = 0
    while(s.skip_until(regex))
      matched_size = s.matched_size
      pos = s.pos
      #add the non-delimiter string if it exists (it may not if the string starts with a delimiter)
      results << self[last_pos ... pos - matched_size] if last_pos < pos - matched_size
      #add the delimiter
      results << self[pos - matched_size ... pos]
      #update the last_pos to the current pos
      last_pos = pos
    end
    #add the last non-delimiter string if one exists after the last delimiter.  It would not have
    #been added since s.skip_until would have returned nil
    results << self[last_pos ... self.length] if last_pos < self.length
    results
  end
end

class ASMSymbol
	MNEMONIC = 1
	ASMSTMT = 2
	NUMBER = 3
	IDENT = 4
	COMMA = 5
	COLON = 6
	REGISTER = 7
	STRING = 8
	EOF = 99

	attr_reader :t, :val

	def self.NumberToString(i)
		return {
			1 =>  "mnemonic",
			2 =>  "asmstmt",
			3 =>  "number",
			4 =>  "ident",
			5 =>  "comma",
			6 =>  "colon",
			7 =>  "register",
			8 =>  "string",
			99 => "eof"
		}[i]
	end

	def initialize(value, type)
		@val = value
		@t = type
	end

	def to_s
		return NumberToString(@t) + ": " + @val.to_s
	end
end

class Lexer
	MNEMONICS = %w{
		nop sleep loadi load store jmp jmpc jmpz jump jumpc jumpz move and or
		xor not add addc sub subc comp inc dec shl shr shlc shrc
		}
	ASSEMBLERSTMT = %w{
		org db equ macro endm
		}
	SYMBOLS = {
		"," => ASMSymbol::COMMA,
		":" => ASMSymbol::COLON,
	}

	attr_reader :line, :col

	def initialize(file)
		# get an array of all input ASMSymbols
		@input = File.open(file).read.partition(/[ \n\t,:;]/)

		# make all input lowercase
		@input.collect!{|x| x = x.downcase }

		# remove all symbols from ";" to "\n"
		while i = @input.index(";")
			while @input[i] != "\n"
				@input.delete_at(i)
			end
		end

		@line = 1
		@col = 0
	end

	def shift
		sym = @input.shift
		return nil unless sym

		if sym == "\n"
			@line += 1
			@col = 1
		else
			@col += sym.length
		end

		return sym
	end

	def nextSym
		# get the next input ASMSymbol and remove it from @input ("pop_front")
		sym = shift()

		# skip whitespaces
		while sym =~ /[ \n\t]+/
			sym = shift()
		end

		# notify the outside if we reached eof
		return ASMSymbol.new("", ASMSymbol::EOF) unless sym

		# check the ASMSymbol's type
		if MNEMONICS.member?(sym)
			return ASMSymbol.new(sym, ASMSymbol::MNEMONIC)
		elsif ASSEMBLERSTMT.member?(sym)
			return ASMSymbol.new(sym, ASMSymbol::ASMSTMT)
		elsif SYMBOLS.member?(sym)
			return ASMSymbol.new(sym, SYMBOLS[sym])
		elsif r = /r(\d+)/.match(sym)
			return ASMSymbol.new(r[1], ASMSymbol::REGISTER)
		elsif r = /"(.*)"/.match(sym)
			return ASMSymbol.new(r[1], ASMSymbol::STRING)
		else
			# this ought to be a number or an ident, try converting it to a number
			begin
				# hex numbers of the form ????h
				if r = /([0-9][0-9a-f]*)h/.match(sym)
					return ASMSymbol.new(Integer("0x" + r[1]), ASMSymbol::NUMBER)
				end

				# hex numbers of the form 0x????
				return ASMSymbol.new(Integer(sym), ASMSymbol::NUMBER)
			rescue ArgumentError
				# converting failed; this is an ident
				return ASMSymbol.new(sym, ASMSymbol::IDENT)
			end
		end
	end
end
