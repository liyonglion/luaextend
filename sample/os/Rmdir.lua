package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local dir = "./testRmdir"
local err = lionos.Mkdir(dir,lionos.S_IRWXU)
if err ~= nil then
	print(err)
	return
end
err = lionos.Rmdir(dir)
if err ~= nil then
	print("Rmdir failed: "..err)
	return
end
print("Rmdir success")