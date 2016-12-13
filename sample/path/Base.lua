package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	print("\""..a .."\"" .. " base :"..path.Base(a))
	a = "."
	print("\""..a .."\"" .. " base :"..path.Base(a))
	a = "/"
	print("\""..a .."\"" .. " base :"..path.Base(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " base :"..path.Base(a))
	a = "."
	print("\""..a .."\"" .. " base :"..path.Base(a))
	a = "c:\\"
	print("\""..a .."\"" .. " base :"..path.Base(a))	
end