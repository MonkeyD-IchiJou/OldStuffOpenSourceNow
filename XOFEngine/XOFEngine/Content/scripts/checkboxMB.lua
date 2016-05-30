require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

  mbenable = Graphics.MotionBlurEnable("get")
  
  active = mbenable
  
  if active == true then
        OWN.getGUIText.setAlpha(0)
  else
        OWN.getGUIText.setAlpha(1)
  end

end


function Update(dt)
	
  if OWN.getAABB.isCollide(1) then
    
    
    if Input.isMouseClick(0) then
      
      if active == true then
        OWN.getGUIText.setAlpha(1)
        active = false
		Graphics.MotionBlurEnable(false)
      else
        OWN.getGUIText.setAlpha(0)
        active = true
		Graphics.MotionBlurEnable(true)
      end
      
    end
    
  end
  
end