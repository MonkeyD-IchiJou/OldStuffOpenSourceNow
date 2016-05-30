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
	
	limit = 1
	timer = 0
	
end	

function Update(dt)
   
	
	currentPos.x, currentPos.y, currentPos.z = OWN.getTransform.getPosition()
	OWN.getAABB.checkCollide(1, "Body")
	
	if OWN.getAABB.isCollide(1) == true then
		movedown = true
		OWN.getRenderer.setColor(0.1, 1.0, 0.1)
	else
		movedown = false
		timer = 0
		OWN.getRenderer.setColor(originalColor.x, originalColor.y, originalColor.z)
	end
	
	if movedown == true then
		timer = timer + dt
		if timer < limit then
			vel = gravity * dt
		else
			vel:Set(0, 0, 0)
      print("dui")
			-- triger set true
			OWN.getTrigger.setTrigger(0, true)
		end
	else
		if currentPos.y <= originalPos.y then
			vel = gravity * -dt
		else
			OWN.getTransform.setPosition(originalPos.x, originalPos.y, originalPos.z)
			vel:Set(0, 0, 0)
			OWN.getTrigger.setTrigger(0, false)
		end
	end
	
	OWN.getTransform.Translate(vel.x, vel.y, vel.z)
end

