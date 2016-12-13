package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local file = "./stat.lua"
local plat = lionos.Getenv("LIONTEST")
local stat,err = lionos.Stat(file)
if err ~= nil then
	print(err)
	return
end

if stat:Isregular() then
	print("It's regular file")
else
	if stat:Isdir() then
		print("It's dir")
	else 
		print("It not regular file")
	end
end

local perm = stat:Perm()
print("perm: "..perm)
local size = stat:Size()
print("size: " .. size)
local modtime = stat:Getmodtime()
print("modify time: "..modtime)
local createtime = stat:Getcreatetime()
print("create time: "..createtime)
local lasttime = stat:Getlastaccesstime()
print("last access time: "..lasttime)

local tp = stat:Gettype()
if tp == lionos.S_IFDIR then
	print("type: dir")
elseif tp == lionos.S_IFIFO then
	print("type: fifo file")
elseif tp == lionos.S_IFCHR then
	print("type: chr file")
elseif tp == lionos.S_IFBLK then
	print("type: block file")
elseif tp == lionos.S_IFREG  then
	print("type: regular file")
end 

if plat == "linux" then
	if tp == S_IFSOCK then
		print("type: socket file")
	elseif tp == S_IFLNK then
		print("type: link file")
	end
end
