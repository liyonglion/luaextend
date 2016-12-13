package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local plat = lionos.Getenv("LIONTEST")
if plat == "windows" then
	print("window not support link")
	return
end

local name = "./Link.lua"
local linkname = "./Link.lua.link"
local err = lionos.Link(name , linkname)
if err ~= nil then
	print(err)
	return
end
print("create link success")
return