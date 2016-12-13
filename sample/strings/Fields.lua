package.cpath = package.cpath .. ";/mnt/share/lion/sample/strings/?.so"
local strings = require("strings")

local a = "\t this is a te\nst"

local t = strings.Fields(a)
for _,v in ipairs(t) do
	print(v)
end