# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: label.rb 530 2008-08-19 18:20:22Z rfindeni $
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

class Label
	def initialize(name, code)
		@name = name
		@code = code
		@to_put = []
		@defined = false
	end

	attr_reader :defined, :name, :addr

	def here
		raise "Label already defined" if @defined

		@defined = true
		@addr = @code.pc

		# fix up the occurrences of the label before it was defined
		while to_put = @to_put.shift()
			@code.code[to_put] = @addr
		end
	end

	def put
		if @defined
			@code.put(@addr)
		else
			@to_put << @code.pc
			@code.put(0xbeef)	# put some dummy value here, we're going to fix
								# it up as soon as the label is defined
		end
	end
end

class LabelInMacro < Label
	def here
		raise "Label already defined" if @defined

		@defined = true
		@addr = @code.pc

		# do not yet fix up any occurrences of the label, this will be done when
		# the macro is being put
	end

	def put
		# we do not care whether the label was already defined: even if it was,
		# we need to fix it up as soon as the macro is being put
		@to_put << @code.pc
		@code.put(0xbeef)	# put some dummy value here, we're going to fix
							# it up as soon as the macro is being put
	end

	def fixup(startpc)
		# this will be called when the macro is being put; fixup all the label's
		# references
		if not @defined
			raise "Label in macro undefined!"
		end

		# do not change our to_put list since the macro can be instantiated more
		# than once
		@to_put_tmp = @to_put.clone
		
		while to_put = @to_put_tmp.shift()
			@code.code[to_put] = startpc + @addr
		end
	end
end