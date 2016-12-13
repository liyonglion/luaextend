package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "this is a test"
print(strings.Lastindex(a, "is"))
print(strings.Lastindex(a, "a"))
print(strings.Lastindex(a, "tmp"))