package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local pagesize, err = lionos.Getpagesize()
if err ~= nil then
	print(err)
	return
end
print(pagesize)