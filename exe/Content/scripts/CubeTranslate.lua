require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  
end

function Update(dt)
  
  OWN.getTransform.Translate(0, 0, -dt * 7.5)
  OWN.getTransform.Rotate(-dt * 500, 0, 0)
  
end