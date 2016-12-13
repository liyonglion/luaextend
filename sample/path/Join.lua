package.cpath = package.cpath .. ";/mnt/share/lion/sample/path/?.so"

local path = require("path")
local plat = os.getenv("LIONTEST")
local tb = {"/","tmp","1234"}
local j, err = path.Join(tb)
if err ~= nil then
	print(err)
	return
end
print(j)