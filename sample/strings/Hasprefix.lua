package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
print(strings.Hasprefix("/test","tmptest"))
print(strings.Hasprefix("/test","tmp"))
print(strings.Hasprefix("/test","/"))
