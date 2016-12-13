package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "this is index of test"
print(strings.Index(a, "of"))
print(strings.Index(a, "fo"))