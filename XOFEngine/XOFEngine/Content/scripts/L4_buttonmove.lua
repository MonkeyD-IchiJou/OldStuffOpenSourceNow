require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  translate = 0
end

function Update(dt)
  
    if OWN.getTrigger.isTrigger(0) == true then 
      if translate < 1.5 then
        translate = translate + dt * 10
        OWN.getTransform.Translate(0, dt * 10, 0)
      end
      
    else
      
      if translate > 0 then
        translate = translate - dt * 10
        OWN.getTransform.Translate(0, -dt * 10, 0)
      end
    
    end
    
end

