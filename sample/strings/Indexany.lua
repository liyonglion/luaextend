package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "this is a test"
print(strings.Indexany(a, "ts"))
print(strings.Indexany(a, "wt"))
print(strings.Indexany(a, "vs"))
print(strings.Indexany(a, "vw"))