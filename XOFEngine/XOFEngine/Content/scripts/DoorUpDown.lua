require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
    
end

function Update(dt)
    
    if OWN.getTrigger.isTrigger(0) == true and OWN.getTrigger.isTrigger(1) == true then 
      OWN.getTransform.Translate(0, dt * 10, 0)
	end
end

