require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	timing = 0
	nextpoint = 0
	
	nextpoint, timing = Scene.Point()
    OWN.getGUIText.setTextString(tostring(timing))
end	

function Update(dt)
    
   
    
end

