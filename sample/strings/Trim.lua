package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "a \r\t this is a test \n\ra"
local b = "a \r\t\n"
print(strings.Trim(a,b))