package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local b64 = strings.base64("hello")
print("base64 of hello: ".. b64)