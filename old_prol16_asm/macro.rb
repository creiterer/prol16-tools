# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: macro.rb 530 2008-08-19 18:20:22Z rfindeni $
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

class Macro
	def initialize(name)
		@name = name
		@code = Code.new(name)
		@labels = {}
	end

	def put(code)
		# fixup all labels inside the macro
		for i in @labels.values
			i.fixup(code.pc)
		end
		
		# add ourself to code
		for i in @code.code
			code.put(i)
		end
	end

	attr_accessor :code, :labels
end