package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "/workspace/luaworkspace/"
	local dir,file = path.Splitpath(a)
	print("\""..a .."\"" .. " Splitpath :"..dir.." "..file)
	a = "./tmp.txt"
	dir,file = path.Splitpath(a)
	print("\""..a .."\"" .. " Splitpath :"..dir.." "..file)
	a = "/tmp"
	dir,file = path.Splitpath(a)
	print("\""..a .."\"" .. " Splitpath :"..dir.." "..file)
elseif plat == "windows" then
	local a = "c:\\workspace\\luaworkspace\\"
	print("\""..a .."\"" .. " Splitpath :"..path.Splitpath(a))
	a = "."
	print("\""..a .."\"" .. " Splitpath :"..path.Splitpath(a))
	a = "c:\\"
	print("\""..a .."\"" .. " Splitpath :"..path.Splitpath(a))	
end
