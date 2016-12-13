package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "this is a test"
print(strings.Trimsuffix(a, "test"))
print(strings.Trimsuffix(a, "tts"))