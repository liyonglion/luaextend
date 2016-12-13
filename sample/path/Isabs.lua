package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")
if plat == "linux" then
	print("/tmp is abs?:",path.Isabs("/tmp"))
	print("tmp is abs?:",path.Isabs("tmp"))
end

if plat == "windows" then
	print("c:\\tmp is abs?", path.Isabs("c:\\tmp"))
	print("tmp is abs?", path.Isabs("tmp"))
end
