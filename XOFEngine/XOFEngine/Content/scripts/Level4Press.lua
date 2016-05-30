require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

end


function Update(dt)
	
  if OWN.getAABB.isCollide(1) then
    
     OWN.getGUIText.setTextColor(1, 0.2, 0)
    
    if Input.isMouseClick(0) then
      
      OWN.getCanvas.setInstruction(8, true)
      Scene.CurrentLevel("Level4")
    end
    
  else
    
     OWN.getGUIText.setTextColor(1, 0.5, 0)
    
  end
  
end