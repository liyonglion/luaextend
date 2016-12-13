package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")

if plat == "linux" then
	local a = "//../workspace/lion/../.././test"
	print("\""..a .."\"" .. " clean :",path.Clean(a))
	local b = "../test"
	print("\""..b .."\"" .. " clean :",path.Clean(b))
	local c = "./tmp"
	print("\""..c .."\"" .. " clean :",path.Clean(c))
end

if plat == "windows" then
	local a = "c:\\..\\workspace\\lion\\..\\..\\.\\test"
	print("\""..a .."\"" .. " clean :",path.Clean(a))
	local b = "../test"
	print("\""..b .."\"" .. " clean :",path.Clean(b))
	local c = "./tmp"
	print("\""..c .."\"" .. " clean :",path.Clean(c))
	c = "c:tmp"
	print("\""..c .."\"" .. " clean :",path.Clean(c))
	c = "\\servername\\share\\lion\\..\\test\\.\\you"
	print("\""..c .."\"" .. " clean :",path.Clean(c))
end