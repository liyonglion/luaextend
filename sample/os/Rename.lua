package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local dir = "./testRemove"
local otherdir = "othername"
local err = lionos.Mkdir(dir, lionos.S_IRWXU)
if err ~= nil then
	print(err)
	return
end
err = lionos.Rename(dir, otherdir)
if err ~= nil then
	print("Rename failed: "..err)
	return
end

err = lionos.Remove(otherdir)
if err ~= nil then
	print("Remove ".. otherdir.. "failed")
	return
end

print("Rename success")