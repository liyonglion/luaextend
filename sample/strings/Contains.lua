package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "I am lion, this is string test. you know this is"
print(strings.Contains(a, "this"))
print(strings.Contains(a, "tmp"))