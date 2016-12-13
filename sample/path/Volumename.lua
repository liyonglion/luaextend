package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	print("\""..a .."\"" .. " Volumename :"..path.Volumename(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Volumename :"..path.Volumename(a))
	a = "."
	print("\""..a .."\"" .. " Volumename :"..path.Volumename(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Volumename :"..path.Volumename(a))	
end
