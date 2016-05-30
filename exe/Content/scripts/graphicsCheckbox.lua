require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

	resoname = {
		"HIGH",
		"GOOD",
		"NOOB"
	}
	
	resovaluex = {
		1600,
		1280,
		1080
	}
	
	resovaluey = {
		900,
		720,
		720
	}
	
	state = 1
	
	rx, ry = Graphics.SceneResolution("get")
	
	checkState = function ()
		if rx == 1600 and ry == 900 then
			state = 1
		elseif rx == 1280 and ry == 720 then
			state = 2
		elseif rx == 1080 and ry == 720 then
			state = 3
		end
	end
	
	checkState()
	OWN.getGUIText.setTextString(resoname[state])
	
end


function Update(dt)
	
  if OWN.getAABB.isCollide(1) then
    
    OWN.getGUIText.setTextColor(1, 0.5, 0)
    
    if Input.isMouseClick(0) then
		state = state + 1
		if state > 3 then
			state = 1
		end
		OWN.getGUIText.setTextString(resoname[state])
		
		-- set the resolution
		Graphics.SceneResolution(resovaluex[state], resovaluey[state])
    end
    
  else
     OWN.getGUIText.setTextColor(1, 0.1, 0)
  end
  
end