package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
print("md5 of hello: " .. strings.md5("hello"))