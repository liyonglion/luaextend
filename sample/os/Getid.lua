package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
print("Getuid:"..lionos.Getuid())
print("Geteuid:"..lionos.Geteuid())
print("Getgid:"..lionos.Getgid())
print("Getegid:"..lionos.Getegid())
print("Getgroups:")
local tb = lionos.Getgroups()
for _,v in ipairs(tb) do
	print(v)
end
print("Getpid:"..lionos.Getpid())
print("Getppid:"..lionos.Getppid())