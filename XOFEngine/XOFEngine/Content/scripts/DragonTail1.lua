require("Content//scripts//DragonMovementC")

function Init()

	BodyMC = DragonMC:New()
	BodyMC:jump()
	BodyMC:updateJumpvel(1)
	BodyMC:jumpMovement()
	
	BodyMC.gravity:Set( 0,  -90 , 0)
	BodyMC.jumpVel:Set(0, -1, 0)
    
    BodyMC.gotospeed = 0.9
end

function Update(dt)
	
    local tail = vec3.New()
    tail.x, tail.y, tail.z = Player.getTailAssPos()
    tail.y = tail.y - 0.45
    BodyMC:MovementFollowUpdateTail(tail, dt)
    
    tail.x, tail.y, tail.z = Player.getTailPos()
    OWN.getLineRenderer.EndLine(tail.x, tail.y, tail.z)
	
	
end
