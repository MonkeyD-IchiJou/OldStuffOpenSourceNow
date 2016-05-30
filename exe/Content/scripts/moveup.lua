require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	vel = vec3.New()
	gravity = vec3.New()
	originalPos = vec3.New()
	currentPos = vec3.New()
	originalColor = vec3.New()
	
	
	originalPos.x, originalPos.y, originalPos.z = OWN.getTransform.getPosition()
	gravity:Set(0, -20, 0)
	
	movedown = false
	
	originalColor.x, originalColor.y, originalColor.z =	OWN.getRenderer.getColor()
end	

function Update(dt)
    
	collideMah = OWN.getEllipsoidCollider.isCollide(false)
	
	currentPos.x, currentPos.y, currentPos.z = OWN.getTransform.getPosition()
	OWN.getAABB.checkCollide(1, "player")
	
	if OWN.getAABB.isCollide(1) == true then
		movedown = true
		OWN.getRenderer.setColor(1.0, 0.1, 0.1)
	else
		movedown = false
		OWN.getRenderer.setColor(originalColor.x, originalColor.y, originalColor.z)
	end
	
	if movedown == true then
		if collideMah == false then
      vel.y = -10.0
			vel = vel + gravity * dt 
		else
			vel:Set(0, 0, 0)
		end
	else
		if currentPos.y <= originalPos.y then
			if collideMah == false then
				vel = vel - gravity * dt
			else
				vel:Set(0, 0, 0)
			end
		else
			vel:Set(0, 0, 0)
		end
	end
	
	OWN.getEllipsoidCollider.setR3Gravity(vel.x, vel.y, vel.z)
	OWN.getEllipsoidCollider.CollisionCheck(dt)
    OWN.getEllipsoidCollider.setR3Vel(0, 0, 0)
end

