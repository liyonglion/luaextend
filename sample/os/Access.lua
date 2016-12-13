package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local a = "./Access.lua"
local isok, err = lionos.Access(a, lionos.R_OK)
if err ~= nil then
	print(err)
	return 
end
if isok then
	print("read ok")
else
	print("read deny")
end
isok, err = lionos.Access(a, lionos.W_OK)
if err ~= nil then
	print(err)
	return 
end
if isok then
	print("write ok")
else
	print("write deny")
end
isok, err = lionos.Access(a, lionos.X_OK)
if err ~= nil then
	print(err)
	return 
end
if isok then
	print("execute ok")
else
	print("execute deny")
end