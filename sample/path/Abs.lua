package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "./"
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))
	a = "."
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))
	a = "/"
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))
	a = "../.."
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))
	a = "."
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Abs :"..path.Abs(a))	
end