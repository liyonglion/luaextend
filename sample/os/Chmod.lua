package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
--初始权限为 rw-r--r
local a = "./Chmod.lua"
local plat = os.getenv("LIONTEST")
local err = nil
if plat == "linux" then
	err = lionos.Chmod(a, lionos.S_IRWXU| lionos.S_IRWXG | lionos.S_IRWXO)-- rwx-rwx-rwx
elseif plat == "window" then
	err = lionos.Chmod(a, lionos.S_IRWXU)
end
if err ~= nil then
	print(err)
	return
end