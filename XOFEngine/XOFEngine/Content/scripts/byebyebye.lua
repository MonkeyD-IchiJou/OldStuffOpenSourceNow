require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  translate = 0
end

function Update(dt)
  
    if OWN.getTrigger.isTrigger(0) == true then 
      if translate < 1000 then
        translate = translate + dt * 1000
        OWN.getTransform.Translate(dt * 1000, 0, 0)
      end
    end
    
end

