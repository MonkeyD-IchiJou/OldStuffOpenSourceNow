require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  originalPos = vec3.New()
  originalPos.x , originalPos.y, originalPos.z = OWN.getTransform.getPosition()
  
  currentPos = vec3.New()
end

function Update(dt)
    currentPos.x , currentPos.y, currentPos.z = OWN.getTransform.getPosition()
    
    if OWN.getTrigger.isTrigger(0) == true then 
      if currentPos.x > originalPos.x - 20 then 
        OWN.getTransform.Translate(dt * -8, 0, 0)
      end
      
    elseif OWN.getTrigger.isTrigger(0) == false then
       if currentPos.x < originalPos.x then 
        OWN.getTransform.Translate(dt * 8, 0, 0)
      end
    end
end

