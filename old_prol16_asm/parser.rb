# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: parser.rb 530 2008-08-19 18:20:22Z rfindeni $
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

require 'lexer.rb'
require 'code.rb'
require 'label.rb'
require 'macro.rb'
require 'vhdlfilewriter.rb'

class Parser
	def initialize(infile, outfile=nil, verbosity=0)
		@infile = infile
		@verbosity = verbosity

		if outfile
			@outfile = outfile
		else
			if m = /(.*)\.as./.match(infile)
				@outfile = m[1] + ".vhd"
			else
				raise "Cannot infer output file name, please supply one!"
			end
		end
		
		@lexer = Lexer.new(infile)
		@code = Code.new
		@la = nil
		@constants = {}
		@macros = {}
		@labels = {}
	end

	attr_accessor :labels, :code

	def skip
		@t = @la
		@la = @lexer.nextSym
	end

	def check(sym, name=nil)
		if @la.t != sym
			if name
				error("#{ASMSymbol::NumberToString(sym)} (#{name}) expected, got #{ASMSymbol::NumberToString(@la.t)}")
			else
				error("#{ASMSymbol::NumberToString(sym)} expected, got #{ASMSymbol::NumberToString(@la.t)}")
			end
		end
		skip
	end

	def error(msg)
		puts "Info:"
		p @code, @constants, @macros
		raise "Error at #{@lexer.line}:#{@lexer.col}: " + msg
	end

	def parse
		skip
		ASM16Assembler()

		# check for any labels that were not defined
		for l in @labels.values
			if not l.defined
				error("Label #{l.name} undefined!")
			end
		end

		if (@verbosity >= 1)
			puts "Labels:"
			for l in @labels.values
				printf("%04x: #{l.name}\n", l.addr)
			end
		end

		if @verbosity >= 2
			puts "Code:"
			@code.prnt
		end

		@code.writeFile(VhdlFileWriter, @outfile)
	end

	def EmitAsmCode(op, ra=0, rb=0, macro=nil)
		if macro
			macro.code.put(Code::OPCODES[op] << 10 | ra.to_i << 5 | rb.to_i)
		else
			if @verbosity >= 3
				printf("%04x: #{op} #{ra}, #{rb}\n", @code.pc)
			end
			@code.put(Code::OPCODES[op] << 10 | ra.to_i << 5 | rb.to_i)
		end
	end

	def EmitAsmConst(c, macro=nil)
		if macro
			macro.code.put(c)
		else
			@code.put(c)
		end
	end

	def ASM16Assembler
		while true
			if @la.t == ASMSymbol::MNEMONIC
				MnemonicStatement()
			elsif @la.t == ASMSymbol::ASMSTMT
				AssemblerStatement()
			elsif @la.t == ASMSymbol::IDENT
				LabelStatementOrMacroCall()
			else
				break
			end
		end

		check(ASMSymbol::EOF)
	end
		
	def ZeroRegOpCode(op, macro=nil)
		skip
		EmitAsmCode(op, 0, 0, macro)
	end

	def OneRegOpCode(op, macro=nil)
		skip
		check(ASMSymbol::REGISTER)
		ra = @t.val
		EmitAsmCode(op, ra, 0, macro)
	end

	def TwoRegOpCode(op, macro=nil)
		skip
		check(ASMSymbol::REGISTER)
		ra = @t.val
		check(ASMSymbol::COMMA)
		check(ASMSymbol::REGISTER)
		rb = @t.val
		EmitAsmCode(op, ra, rb, macro)
	end

	# macro != nil means that we are inside a macro. there, all emitted code
	# needs to be put into the macro, and not into the real code! therefore,
	# pass macro on to EmitAsmCode which will take care of this.
	def MnemonicStatement(macro = nil)
		case @la.val
			when "nop", "sleep":
				ZeroRegOpCode(@la.val, macro)
			when "loadi":
				skip
				check(ASMSymbol::REGISTER)
				ra = @t.val
				check(ASMSymbol::COMMA)
				EmitAsmCode("loadi", ra, 0, macro)
				e = Expression(macro)
				# if e was a label, it will return nil
				EmitAsmConst(e, macro) if e
			when "load", "store", "move", "and", "or", "xor", "add", "addc",
					"sub", "subc", "comp":
				TwoRegOpCode(@la.val, macro)
			when "jump", "jmp", "jumpc", "jmpc", "jumpz", "jmpz", "not", "inc",
					"dec", "shl", "shr", "shlc", "shrc":
				OneRegOpCode(@la.val, macro)
			else
				error( "Illegal mnemonic, this is a bug in the assembler!")
		end
	end

	def AssemblerStatement
		case @la.val
			when "org":
				skip
				@code.pc = Expression()
			when "db":
				skip
				while true
					if @la.t == ASMSymbol::NUMBER
						@code.put(@la.val)
						skip
					elsif @la.t == ASMSymbol::STRING
						for c in @la.val.split('')
							@code.put(c[0]) # [0] converts to ascii ;)
						end
						skip
					else
						error("Numer or string expected!")
					end

					break if @la.t != ASMSymbol::COMMA
					skip # the colon
				end
			when "equ":
				skip
				check(ASMSymbol::IDENT)
				name = @t.val
				check(ASMSymbol::COMMA)
				check(ASMSymbol::NUMBER)
				val = @t.val
				AddConstant(name, val)
			when "macro":
				skip
				check(ASMSymbol::IDENT)
				if @macros.member?(@t.val)
					error("Macro #{@t.val} already defined!")
				end
				m = @macros[@t.val] = Macro.new(@t.val)
				while true
					if @la.t == ASMSymbol::MNEMONIC
						MnemonicStatement(m)
					elsif @la.t == ASMSymbol::IDENT
						LabelStatementOrMacroCall(m)
					else
						break
					end
				end
				check(ASMSymbol::ASMSTMT, "endm")
				if (@t.val != "endm")
					error("endm expected!")
				end
			else
				error("Illegal assembler statement, this is a bug in the assembler!")
		end
	end

	def AddConstant(const, val)
		if @constants.member?(const)
			error("Constant #{const} already defined!")
		end
		if @labels.member?(const)
			error("Cannot use the same name for a label and a constant!")
		end
		@constants[const] = val
	end

	# NOTE: to add macro call support to the ATG, we need to change
	# LabelStatement to LabelStatementOrMacroCall, otherwise there would be an
	# LL(1) conflict between MacroCall and LabelStatement (First() of both would
	# be ident).
	def LabelStatementOrMacroCall(macro = nil)
		check(ASMSymbol::IDENT)
		ident = @t.val

		# if we are inside a macro, all stuff needs to go there, and we need to
		# create LabelInMacro instances instead of Label instances
		if macro
			parent = macro
			label_type = LabelInMacro
		else
			parent = self
			label_type = Label
		end
		
		if @la.t == ASMSymbol::COLON
			# this is a label statment
			skip

			if @constants.member?(ident)
				error("Cannot use the same name for a label and a constant!")
			end

			# add a new label if it has not already been defined
			if parent.labels[ident] == nil
				parent.labels[ident] = label_type.new(ident, parent.code)
			end
			
			parent.labels[ident].here
		else
			# do not allow calling macros from inside macros to avoid calling
			# ourselves which ends in an endless loop
			error("Cannot call macro from inside macro!") if macro
			
			# this is a macro call
			if not @macros.member?(ident)
				error("Macro #{ident} undefined or colon after label missing!")
			end

			# macros can cause some errors during fixup; if there is one, catch
			# it and pipe it through our error function to add line and column
			# information
			begin
				@macros[ident].put(parent.code)
			rescue
				error($!)
			end
		end
	end

	def Expression(macro = nil)
		# if we are inside a macro, all stuff needs to go there
		if macro
			parent = macro
			label_type = LabelInMacro
		else
			parent = self
			label_type = Label
		end
	
		if @la.t == ASMSymbol::NUMBER
			skip
			return @t.val
		elsif @la.t == ASMSymbol::IDENT
			skip

			# this could either be a constant or a label, check both
			if @constants.member?(@t.val)
				return @constants[@t.val]
			elsif parent.labels.member?(@t.val)
				# it is a label and it already exists
				parent.labels[@t.val].put
				return nil
			else
				# it is a label that is not yet defined
				parent.labels[@t.val] = (l = label_type.new(@t.val, parent.code))
				l.put
				return nil
			end
		else
			error("Expected number or ident!")
		end
	end
end
