package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local hello = "aGVsbG8="
print(hello.." unbase64 is: "..strings.unbase64(hello))
