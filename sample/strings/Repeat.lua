package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "Repeat"
print(strings.Repeat(a, 3))
print(strings.Repeat(a, 0))