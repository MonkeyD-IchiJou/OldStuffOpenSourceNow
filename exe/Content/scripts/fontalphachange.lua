require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  
  fade = 0
  change = false
  
end

function Update(dt)
  
  if (change == false) then
    fade = fade + dt * 0.4
    
    if fade >= 0.7 then
      change = true
    end
    
  else 
     fade = fade - dt * 0.4
     
     if fade <= 0 then
      change = false
    end
    
  end
  
  
  OWN.getGUIText.setAlpha(fade)
  
  
end