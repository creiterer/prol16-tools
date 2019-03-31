# This file is part of ProlASM.
#
# Copyright (C) 2008 Rainer Findenig
# $Id: vhdlfilewriter.rb 530 2008-08-19 18:20:22Z rfindeni $
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

class VhdlFileWriter
	FORMAT = "    %04d => X\"%04x\",\n"
	
	PRE = '
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Ram is
  generic (
    gAddrWidth : integer := 14);
  port (
    iClk  : in  std_ulogic;
    iData : in  std_ulogic_vector(15 downto 0);
    oData : out std_ulogic_vector(15 downto 0);
    iAddr : in  std_ulogic_vector(15 downto 0);
    iRd   : in  std_ulogic;
    iWr   : in  std_ulogic;
    iSel  : in  std_ulogic);
end Ram;

architecture Rtl of Ram is
  subtype aDataVec is std_ulogic_vector(15 downto 0);
  type    aMem is array (2**gAddrWidth-1 downto 0) of aDataVec;

  signal mem : aMem := (
'
	POST = '    others => X"0000"
    );
begin  -- Rtl

  -----------------------------------------------------------------------------
  -- write
  wrt : process (iClk)
  begin  -- process write
    if iClk\'event and iClk = \'0\' then   -- FALLING clock edge
      if iSel = \'1\' then
        if iWr = \'1\' then
          mem(to_integer(unsigned(iAddr))) <= iData;
        end if;
        oData <= mem(to_integer(unsigned(iAddr)));
      end if;
    end if;
  end process wrt;
end Rtl;
'
end
