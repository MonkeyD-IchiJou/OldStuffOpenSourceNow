require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

	timer = 0
	
end	

function Update(dt)

	timer = timer + dt* 0.85
	
	if timer < math.pi then
		OWN.getTransform.Rotate(0, timer, 0)
	end
	
end

