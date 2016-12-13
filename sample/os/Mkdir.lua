package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local dir = "./tmptest"
local err = lionos.Mkdir(dir,lionos.S_IRWXU)
if err ~= nil then
	print(err)
	return
end
