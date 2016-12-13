package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "this is a test"
print(strings.Replace(a, "is", "are", 1))
print(strings.Replace(a, "is", "are", 2))
print(strings.Replace(a, "is", "are", 3))
print(strings.Replace(a, "is", "are", -1))
print(strings.Replace(a, "are", "is", -1))