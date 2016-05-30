require("Content//scripts//DragonMovementC")

function Init()

	-- common movement stuff
	camlookingdir = vec3.New() -- this is the lookingdir
	camlookingtdir = vec3.New() -- tangent looking dir
	up = vec3.New()
	up:Set( 0, 1, 0 )
	
	BodyMC = DragonMC:New()
	BodyMC:jump()
	BodyMC:updateJumpvel(1)
	BodyMC:jumpMovement()
	
	BodyMC.gravity:Set( 0,  -90 , 0)
	BodyMC.jumpVel:Set(0, -1, 0)
    
    BodyMC.JUMP_POWER = 20
	
	BodyMC.speed = 0.45
	
	ownPos = vec3.New() -- must have
end

function Update(dt)
	
	dieliaomah = Player.DeadState("GET")
	
	camlookingdir.x, camlookingdir.y, camlookingdir.z = Camera.getLookingDir()
	camlookingdir.y = 0
	camlookingdir:Normalize()
	camlookingtdir = camlookingdir:Cross(up)
	
	-- need const update the jumpVel
	BodyMC:updateJumpvel(dt)
	
	ownPos.x,ownPos.y,ownPos.z = OWN.getTransform.getPosition()
	
	commandState = Player.getHeadCommandState()
	
	-- if is on your own .. then can control
	if commandState == 2 then
		BodyMC.FRICTIONAL_STR = 0.05
		
		if Player.getState() == 1 then
			BodyMC:MovementUpdate(dt)
			BodyMC:jumpMovement()
			BodyMC:applyFriction()
			
		else
			BodyMC.vel.x, BodyMC.vel.y, BodyMC.vel.z = OWN.getEllipsoidCollider.getR3Vel()
			BodyMC:applyFriction()
            
            BodyMC.jumpVel.y = -20
			OWN.getEllipsoidCollider.setR3Vel(BodyMC.vel.x, BodyMC.vel.y, BodyMC.vel.z)
		end
		
		if ownPos.y < -10 then
			OWN.getEllipsoidCollider.setR3Gravity(0, 0, 0)
			OWN.getEllipsoidCollider.setR3Vel(0, 0, 0)
			local restartpos = vec3.New()
			restartpos.x, restartpos.y, restartpos.z = Player.getHeadAssPos()
			OWN.getTransform.setPosition(restartpos.x, restartpos.y + 10.0, restartpos.z)
		else
			OWN.getEllipsoidCollider.setR3Gravity(BodyMC.jumpVel.x, BodyMC.jumpVel.y, BodyMC.jumpVel.z)
		end
    
	-- if not .. then is kena control by the dragon head .. 
	elseif commandState == 0 or commandState > 2 then
	
		dieliaomah = Player.DeadState("GET")
		local head = vec3.New()
		head.x,head.y,head.z = Player.getHeadPos()
		
		if dieliaomah == false then
		
			BodyMC.FRICTIONAL_STR = 0.01
			
			OWN.getLineRenderer.StartLine(ownPos.x,ownPos.y,ownPos.z)
			OWN.getLineRenderer.EndLine(head.x,head.y,head.z)
			
			if Player.isBodyPartsMoving(0) == true then
			
				local dist = (head - ownPos):LengthSquare()
				if dist < 900 then
					local headPos = vec3.New()
					headPos.x, headPos.y, headPos.z = Player.getHeadAssPos()
				
					BodyMC:MovementFollowUpdate(headPos, dt)
				end
				
				OWN.getEllipsoidCollider.setR3Gravity(0, 0, 0)
				
			else
			
				OWN.getEllipsoidCollider.setR3Gravity(0, -60, 0)
				OWN.getEllipsoidCollider.setR3Vel(BodyMC.vel.x, BodyMC.vel.y, BodyMC.vel.z)
				BodyMC:applyFriction()
			end
			
		else
			OWN.getEllipsoidCollider.setR3Gravity(0, 0, 0)
			OWN.getEllipsoidCollider.setR3Vel(0, 0, 0)
			OWN.getTransform.setPosition(0, 1, 0) -- checkpoint position pls
		
		end
	end
	
	OWN.getEllipsoidCollider.CollisionCheck(dt)
	
end