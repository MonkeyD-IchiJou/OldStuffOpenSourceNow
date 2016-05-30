require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

  drag = false
  leftlmt = 0.44 - 1.3
  rightlmt = 0.796 - 1.3

end


function Update(dt)
	
  x, y = Input.CursorPosition()
  move = x - 1.3
  
  if OWN.getAABB.isCollide(1) then
    
    OWN.getGUIText.setTextColor(1, 0.2, 0)
    
    if Input.isMouseHold(0) then
      
      --x = x + dt * 0.2
      
      drag = true
      
    end
    
  else
     OWN.getGUIText.setTextColor(1, 0.5, 0)
  end
  
  if Input.isMouseHold(0) == false then
    drag = false
  end
  
  if drag == true then
    
    if move <= leftlmt then
      move = leftlmt
    elseif move >= rightlmt then
      move = rightlmt
    end
    
    OWN.getGUIText.setTextColor(0.5, 1, 0)
    OWN.getTransform.setPosition(move, -1.495, 0)
  end
  
  
end