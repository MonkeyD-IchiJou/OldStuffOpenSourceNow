require("Content//scripts//Keys")
require("Content//scripts//vec3")


function Init()
    timer = 0
end

function Update(dt)
	timer = timer + dt  * 100
	
	if timer < 315 then
		OWN.getDirLight.changeLightDirection(0, 1, 0, dt * 100)
	end
    
end


