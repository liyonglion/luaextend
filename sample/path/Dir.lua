package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))
	a = "."
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))
	a = "/"
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))
	a = ""
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))
	a = "."
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Dir :"..path.Dir(a))	
end