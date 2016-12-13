package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local hostname, err = lionos.Gethostname()
if err ~= nil then
	print(err)
	return
end
print(hostname)