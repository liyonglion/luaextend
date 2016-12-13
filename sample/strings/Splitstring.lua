package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")
local a = "thisisatest"
local tb = strings.Splitstring(a, "is")

for _,v in ipairs(tb) do
	print(v)
end

local tb = strings.Splitstring(a, "table")

for _,v in ipairs(tb) do
	print(v)
end