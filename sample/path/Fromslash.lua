package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	print("\""..a .."\"" .. " Fromslash :"..path.Fromslash(a))
	a = "./tmp.txt"
	print("\""..a .."\"" .. " Fromslash :"..path.Fromslash(a))
	a = "/tmp"
	print("\""..a .."\"" .. " Fromslash :"..path.Fromslash(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Fromslash :"..path.Fromslash(a))
	a = "."
	print("\""..a .."\"" .. " Fromslash :"..path.Fromslash(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Fromslash :"..path.Fromslash(a))	
end
