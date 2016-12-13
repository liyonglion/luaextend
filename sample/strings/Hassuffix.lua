package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
print(strings.Hassuffix("/tmp","/"))
print(strings.Hassuffix("/tmp","tmptest"))
print(strings.Hassuffix("/tmp","tmp"))