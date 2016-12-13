package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "this is a test"
local b = "wow"
local c = "wto"

print(strings.Containsany(a,b))
print(strings.Containsany(a,c))