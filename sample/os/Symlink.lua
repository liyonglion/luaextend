package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local plat = lionos.Getenv("LIONTEST")
if plat == "windows" then
	print("window not support Symlink")
	return
end

local name = "./Link.lua"
local linkname = "./Link.lua.symlink"
local err = lionos.Symlink(name , linkname)
if err ~= nil then
	print(err)
	return
end
print("create symlink success")
return