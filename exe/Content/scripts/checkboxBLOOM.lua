require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

  bloomenable = Graphics.BloomEnable("get")
  
  active = bloomenable
  
  if active == true then
        OWN.getGUIText.setAlpha(0)
  else
        OWN.getGUIText.setAlpha(1)
  end

end


function Update(dt)
	
  if OWN.getAABB.isCollide(1) then
    
    --OWN.getGUIText.setTextColor(1, 0.2, 0)
    
    if Input.isMouseClick(0) then
      
      if active == true then
        OWN.getGUIText.setAlpha(1)
        active = false
		Graphics.BloomEnable(false)
      else
        OWN.getGUIText.setAlpha(0)
        active = true
		Graphics.BloomEnable(true)
      end
      
      
    end
    
  else
     --OWN.getGUIText.setTextColor(1, 0.5, 0)
  end
  
end