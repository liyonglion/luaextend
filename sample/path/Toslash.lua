package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	print("\""..a .."\"" .. " Toslash :"..path.Toslash(a))
	a = "./tmp.txt"
	print("\""..a .."\"" .. " Toslash :"..path.Toslash(a))
	a = "/tmp"
	print("\""..a .."\"" .. " Toslash :"..path.Toslash(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Toslash :"..path.Toslash(a))
	a = "."
	print("\""..a .."\"" .. " Toslash :"..path.Toslash(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Toslash :"..path.Toslash(a))	
end
