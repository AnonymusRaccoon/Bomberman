------------ JOHN AI


local debug = true
--local debug = false
if not debug then
    log = function() end
end

function PrintMap(map, maxX, maxZ)
	for i=0,maxX + 1 do
		local s = "| "
    	for j=0,maxZ + 1 do
			s = s .. tostring(map[i][j]) .. " | ";
		end
		log(s)
		log(string.rep("-", (maxZ - 1) * 5 - 1))
    end
end

function CreateMyMap(infos, maxX, maxZ)
	local map = {}
    for i=0,maxX + 1 do
    	map[i] = {}
    	for j=0,maxZ + 1 do
    		map[i][j] = 0
    	end
    end
	for i, info in ipairs(infos) do
		map[info.x][info.z] = info.type
	end
	PrintMap(map, maxX, maxZ)
	return map
end

function Update(player, infos, players)
	local maxX = 0
	local maxZ = 0
	for i, info in ipairs(infos) do
		if info.x > maxX then
			maxX = info.x
		end
		if info.z > maxZ then
			maxZ = info.z
		end
	end
	local myMap = CreateMyMap(infos, maxX, maxZ);
	if (isInExplosionRange()) then
		--play defensive RUN
	else
		--play offensive
	end
	return 1, 1, false, false;
end