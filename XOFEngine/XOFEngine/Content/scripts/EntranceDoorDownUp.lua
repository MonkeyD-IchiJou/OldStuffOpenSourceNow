require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  countTimer = 0
end

function Update(dt)
    
    if OWN.getTrigger.isTrigger(0) == true and OWN.getTrigger.isTrigger(1) == true then 
      countTimer = countTimer + dt

      if(countTimer < 4) then
        OWN.getTransform.Translate(0, dt * -8, 0)
      end
        
    else
      countTimer = 0
    end
    
end

