package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "this is a test"
print(strings.Lastindexany(a, "tw"))
print(strings.Lastindexany(a, "at"))
print(strings.Lastindexany(a, "wv"))