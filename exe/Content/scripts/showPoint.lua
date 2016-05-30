require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	
end	

function Update(dt)
    
	nextpoint, timing = Scene.Point()
    OWN.getGUIText.setTextString(string.format("Score: %07d", nextpoint))
    
end

