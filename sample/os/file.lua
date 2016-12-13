package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

--Create
local create_fd, err = lionos.Create("testcreate")
if err ~= nile then
	print(err)
	return
end

print("name: ".. create_fd:Name())
local stat,err = create_fd:Stat()

if err ~= nil then
	print(err)
	return
end

if stat:Isregular() then
	print("It's regular file")
else
	if stat:IsDir() then
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

print("Fd: ".. create_fd:Fd())
create_fd:Chdir()
print("FdChdir: " .. lionos.Getcwd())

err = create_fd:Chmod(lionos.S_IRWXU)
if err ~= nil then
	print(err)
	return
end

local num, err = create_fd:Writestring("this is a test")
if errr ~= nil then
	print(err)
	return
end
print("write in ".. num .." byte(s)")
local writenum = create_fd:Seek(0,lionos.SEEK_CUR)
if  writenum ~= num then
	print("write error.except "..num.." but "..writenum)
	return
end

err = create_fd:Truncate(4)
if err ~= nil then
	print(err)
end
if create_fd:Seek(0,lionos.SEEK_CUR) ~= 4 then
	print("Truncate 4, but file size is not 4")
	return
end


create_fd:Truncate(0)

--content is: this is  a test.
_, err = create_fd:Writestring("this is  a test.")
if err ~= nil then
	print(err)
	return 
end
--content is: this is  a test.you
_, err = create_fd:Write("you know", 3)

_,err = create_fd:Writeat("are",3, 5, lionos.SEEK_SET)
if err ~= nil then
	print(err)
	return;
end

--Seek
create_fd:Seek(0, lionos.SEEK_SET)

--readall
local buf, err = create_fd:Read("*all")
if err == lionos.EOF then
	print("readall done")
elseif err ~= nil then
	print("Readall error: ".. err)
	return 
end
print("readall: "..buf)

--read line
create_fd:Seek(0, lionos.SEEK_SET)

local buf, err = create_fd:Read("*line")
if err == lionos.EOF then
	print("read line done")
elseif err ~= nil then
	print("read line error:".. err)
	return
end
print("readline: ".. buf)
--read *number
create_fd:Seek(0, lionos.SEEK_SET)
local buf, err = create_fd:Read("*5")
if err == lionos.EOF then
	print("read number done")
elseif err ~= nil then
	print("read number error.")
	return
end
print("read number: ".. buf)

--readat all
create_fd:Seek(0, lionos.SEEK_SET)
local buf, err = create_fd:Readat("*all", 4, lionos.SEEK_CUR);
if err == lionos.EOF then
	print("readat all done")
elseif err ~= nil then
	print("readat all error.")
	return
end
print("readat all: ".. buf)


--readat line
create_fd:Seek(0, lionos.SEEK_SET)

local buf, err = create_fd:Readat("*line", 4, lionos.SEEK_CUR)
if err == lionos.EOF then
	print("readat line done")
elseif err ~= nil then
	print("readat line error:".. err)
	return
end
print("readat: ".. buf)

--read *number
create_fd:Seek(0, lionos.SEEK_SET)
local buf, err = create_fd:Readat("*5", 4, lionos.SEEK_SET)
if err == lionos.EOF then
	print("ReadAt number done")
elseif err ~= nil then
	print("ReadAt number error.")
	return
end
print("ReadAt number: ".. buf)


