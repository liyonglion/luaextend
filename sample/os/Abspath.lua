package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local a = "../.."
print(a .. "abs path is "..lionos.Abspath(a))
a = "../tmp"
local file, err = lionos.Abspath(a)
if err ~= nil then
	print(a..":"..err)

else
	print(a .. "abs path is "..file)
end

a = "/tmp"
local file, err = lionos.Abspath(a)
if err ~= nil then
	print(err)

else
print(a .. " abs path is "..file)
end