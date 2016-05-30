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
	
    local tail2 = vec3.New()
    tail2.x, tail2.y, tail2.z = Player.getTail2AssPos()
     tail2.y = tail2.y - 0.1
    BodyMC:MovementFollowUpdateTail(tail2, dt)
    
    tail2.x, tail2.y, tail2.z = Player.getTail2Pos()
    OWN.getLineRenderer.EndLine(tail2.x, tail2.y, tail2.z)
	
end
