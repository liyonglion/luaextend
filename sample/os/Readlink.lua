package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local plat = lionos.Getenv("LIONTEST")

if plat == "windows" then
	print("Readlink not support this on windows")
	return
end

local a = "./Link.lua.symlink"

local res , err = lionos.Readlink(a)
if err ~= nil then
	print(err)
	return
end

print(res)
return