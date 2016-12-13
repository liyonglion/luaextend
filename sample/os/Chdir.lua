package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")

print("current workspace dir befor changing: " .. lionos.Getcwd())
local a = "/tmp"
print("chang dir to "..a)
lionos.Chdir(a)
print("current workspace dir after changing: " .. lionos.Getcwd())