package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "a \r\t this is a test \ta"
local b = "\r\t a"
print(strings.Trimleft(a,b))