require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  Rotation = 0
end

function Update(dt)
    if OWN.getTrigger.isTrigger(0) == true and OWN.getTrigger.isTrigger(1) == true then 
      
      if Rotation < 25 then
        Rotation = Rotation + dt * 15
        OWN.getTransform.Rotate(dt * 15, 0, 0)
      end
    
    end
    
end

