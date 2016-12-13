package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local file = "/tmp"
local isexist = lionos.Isexist(file)
if isexist then
	print(file .." is exist")
else
	print(file .. "is not exist")
end

file = "txt.txt"
local isexist = lionos.Isexist(file)
if isexist then
	print(file .." is exist")
else
	print(file .. " is not exist")
end