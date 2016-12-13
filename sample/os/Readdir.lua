package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local dir = "/mnt/share/lion/sample/os/"
local tb, err = lionos.Readdir(dir)
if err ~= nil then
	print(err)
	return
end
for _,v in ipairs(tb) do
	print(v)
end