require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	vel = vec3.New()
	gravity = vec3.New()
	originalPos = vec3.New()
	currentPos = vec3.New()
	originalColor = vec3.New()
	
	originalPos.x, originalPos.y, originalPos.z = OWN.getTransform.getPosition()
	gravity:Set(0, -1, 0)
	
	movedown = false
	
	originalColor.x, originalColor.y, originalColor.z =	OWN.getRenderer.getColor()
	
	limit = 3
	timer = 0
	
end	

function Update(dt)
   
	
	currentPos.x, currentPos.y, currentPos.z = OWN.getTransform.getPosition()
	
	movedown = OWN.getTrigger.isTrigger(0)
	
	
	
	if movedown == true then
		gravity.y = -1
		timer = timer + dt
		if timer < limit then
			vel = gravity * dt
		else
			vel:Set(0, 0, 0)
		end
	else
		gravity.y = -0.1
		timer = 0
		if currentPos.y <= originalPos.y then
			vel = gravity * -dt
		else
			OWN.getTransform.setPosition(originalPos.x, originalPos.y, originalPos.z)
			vel:Set(0, 0, 0)
		end
	end
	
	OWN.getTransform.Translate(vel.x, vel.y, vel.z)
end

