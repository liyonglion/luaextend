package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local dir = "./testRemovedir"
local err = lionos.Mkdir(dir, lionos.S_IRWXU);
if err ~= nil then
	print(err)
	return
end

err = lionos.Remove(dir);
if err ~= nil then
	print("Remove failed: ".. err)
	return
end

print("Remove ".. dir.. " success")