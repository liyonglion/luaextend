package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "this is a test. author is lion."
print(strings.Count(a, "is"))
print(strings.Count(a, "."))
print(strings.Count(a, "wow"))