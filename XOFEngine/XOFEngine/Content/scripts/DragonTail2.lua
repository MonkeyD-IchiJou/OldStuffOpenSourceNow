require("Content//scripts//DragonMovementC")

function Init()

	BodyMC = DragonMC:New()
	BodyMC:jump()
	BodyMC:updateJumpvel(1)
	BodyMC:jumpMovement()
	
	BodyMC.gravity:Set( 0,  -90 , 0)
	BodyMC.jumpVel:Set(0, -1, 0)
    
    BodyMC.gotospeed = 0.8
end

function Update(dt)
	
	
    local tail1 = vec3.New()
    tail1.x, tail1.y, tail1.z = Player.getTail1AssPos()
     tail1.y = tail1.y - 0.25
    BodyMC:MovementFollowUpdateTail(tail1, dt)
		
    tail1.x, tail1.y, tail1.z = Player.getTail1Pos()
    OWN.getLineRenderer.EndLine(tail1.x, tail1.y, tail1.z)
end
