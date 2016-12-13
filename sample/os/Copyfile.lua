package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local src = "./Copyfile.lua"
local dst = "./Copyfile_back"
local err = lionos.Copyfile(src, dst,true)
if err ~= nil then
	print(err)
	return
end
print("copy "..src.." to "..dst.. " success")
