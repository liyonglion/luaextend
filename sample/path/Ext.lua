package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	print("\""..a .."\"" .. " Ext :"..path.Ext(a))
	a = "./tmp.txt"
	print("\""..a .."\"" .. " Ext :"..path.Ext(a))
	a = "/tmp"
	print("\""..a .."\"" .. " Ext :"..path.Ext(a))
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Ext :"..path.Ext(a))
	a = "."
	print("\""..a .."\"" .. " Ext :"..path.Ext(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Ext :"..path.Ext(a))	
end