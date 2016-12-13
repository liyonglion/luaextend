package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

local file = "/tmp"
local isexist = lionos.Isnotexist(file)
if isexist then
	print(file .." is not exist")
else
	print(file .. "is exist")
end

file = "txt.txt"
local isexist = lionos.Isnotexist(file)
if isexist then
	print(file .." is not exist")
else
	print(file .. " is exist")
end