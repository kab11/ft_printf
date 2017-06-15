# Ft_printf

__Installation:__

* `git clone https://github.com/mikim42/Ft_printf.git`
* `make`

**Usage:**
* `Representation of bulit in function [printf]`

**Conversions:**
* All of the original printf conversions.
* `%b` `%B`: the int argument is converted to binary.
* `%r`: print non-printable(control) characters.
* `%w`: change the out-put file descriptor.
* `%q`: roll a dice. (need int argument, returns 1 - 6).

**Options:**
* may be different depends on terminal.
* `{OFF}` off setting.
* `{SET:BO}` set bold.
* `{SET:FT}` set faint.
* `{SET:IT}` set italic.
* `{SET:UL}` set underline.
* `{SET:RE}` set reverse.
* `{SET:CC}` set conceal.
* `{SET:RV}` set reveal.

**Color:**
* `{***}` set color.
* `{BGC:***}` set background color.
* `{LT:***}` set light color.
* `BLK` black.
* `RED` red.
* `GRN` green.
* `YEL` yellow.
* `BLU` blue.
* `MGT` magenta.
* `CYN` cyan.
* `WHT` white.
