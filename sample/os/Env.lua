package.cpath = package.cpath .. ";/mnt/share/lion/sample/os/?.so"

local lionos = require("lionos")
local tb = lionos.Getenv()
for k,v in pairs(tb) do
	print(k..": "..v)
end

--setenv
local envkey = "LION"
local envval = "test"
local err = lionos.Setenv(envkey, envval)
if err ~= nil then
	print(err)
	return
end

--GetEnv

envval, err = lionos.Getenv(envkey)
if err ~= nil then
	print(err)
	return
end
print("Env["..envkey.."]: ".. envval)

--CleanEnv

err = lionos.Cleanenv(envkey)
if err ~= nil then
	print(err)
	return
end
envval, err = lionos.Getenv(envkey)
if err ~= nil then
	print(err)
	return
end
if envval ~= nil then
	print("Env["..envkey.."]: ".. envval.. "clean failed")
	return 
end
print("clean env ".. envkey.. " success")