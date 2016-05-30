require("Content//scripts//vec3")

function Init()
	currentpoint = 0
	nextpoint = 0
	
	effect = false
	timer = 0
	
	color = vec3.New()
	color:Set(1, 1, 1)
end

function Update(dt)
  
  nextpoint, timing = Scene.Point()
  
  if nextpoint ~= currentpoint then
	effect = true
  end
  
  if effect == true then
  
	timer = timer + dt
	if timer < 1 then
		color:Set(1.0, 0.7, 0.1)
	else
		timer = 0
		effect = false
		
	end
	
  else
	color.x = color.x + dt
	if color.x > 1.0 then
		color.x = 1.0
	end
	
	color.y = color.y + dt
	if color.y > 1.0 then
		color.y = 1.0
	end
	
	color.z = color.z + dt
	if color.z > 1.0 then
		color.z = 1.0
	end
  
  end
  
  OWN.getGUIText.setTextColor(color.x, color.y, color.z)
  OWN.getGUIText.setTextString(string.format("%07d", nextpoint))
  
  currentpoint = nextpoint
    
end