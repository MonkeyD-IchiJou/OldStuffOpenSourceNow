require("Content//scripts//DragonMovementC")


function Init()

	-- common movement stuff
	camlookingdir = vec3.New() -- this is the lookingdir
	camlookingtdir = vec3.New() -- tangent looking dir
	up = vec3.New()
	up:Set( 0, 1, 0 )
	
	TailMC = DragonMC:New()
	TailMC:jump()
	TailMC:updateJumpvel(1)
	TailMC:jumpMovement()
	
	TailMC.gravity:Set( 0,  -90 , 0)
	TailMC.jumpVel:Set(0, -1, 0)
    
    doubleJump = false
    
    floattimer = 0
    
    --TailMC.gotospeed = 0.3
    ownPos = vec3.New() -- must have
	
	TailMC.FRICTIONAL_STR = 0.05
end

function Update(dt)
	
	camlookingdir.x, camlookingdir.y, camlookingdir.z = Camera.getLookingDir()
	camlookingdir.y = 0
	camlookingdir:Normalize()
	camlookingtdir = camlookingdir:Cross(up)

	ownPos.x,ownPos.y,ownPos.z = OWN.getTransform.getPosition()
	
	-- need const update the jumpVel
	--TailMC:updateJumpvel(dt)
    if TailMC:updateJumpvel(dt) == true then
        doubleJump = false
	end
    
	commandState = Player.getHeadCommandState()
	
	if  commandState == 2 then
	
		
		
		if Player.getState() == 3 then
			TailMC:MovementUpdate(dt)
            
             if Input.isKeyTouched(keys.KEY_SPACE) and  TailMC.isInAir == true and doubleJump == false then
                TailMC.isInAir = false
                doubleJump = true
                TailMC:jump()
		    end
            
            if Input.isKeyPressed(keys.KEY_SPACE) and  TailMC.isInAir == true then
                floattimer = floattimer + dt
                if floattimer > 0.5 then
                    TailMC.gravityMaxStrength = 5
                    
                    TailMC:TailWiggle(dt)
                end
            else
                TailMC.gravityMaxStrength = 90
                floattimer = 0
            end
            
			TailMC:jumpMovement()
			TailMC:applyFriction()
           
		else
			TailMC.vel.x, TailMC.vel.y, TailMC.vel.z = OWN.getEllipsoidCollider.getR3Vel()
			TailMC:applyFriction()
            
			OWN.getEllipsoidCollider.setR3Vel(TailMC.vel.x, TailMC.vel.y, TailMC.vel.z)
			
		end
		
		if ownPos.y < -10 then
			OWN.getEllipsoidCollider.setR3Gravity(0, 0, 0)
			OWN.getEllipsoidCollider.setR3Vel(0, 0, 0)
			local restartpos = vec3.New()
			restartpos.x, restartpos.y, restartpos.z = Player.getBody2AssPos()
			OWN.getTransform.setPosition(restartpos.x, restartpos.y + 10.0, restartpos.z)
		else
			OWN.getEllipsoidCollider.setR3Gravity(TailMC.jumpVel.x, TailMC.jumpVel.y, TailMC.jumpVel.z)
		end
        
	elseif commandState == 0 or commandState > 2 then
	
		dieliaomah = Player.DeadState("GET")
		local body2 = vec3.New()
		body2.x,body2.y,body2.z = Player.getBody2Pos()
		
		
		
		if dieliaomah == false then
		
			OWN.getLineRenderer.StartLine(ownPos.x,ownPos.y,ownPos.z)
			OWN.getLineRenderer.EndLine(body2.x,body2.y,body2.z)
			
			if Player.isBodyPartsMoving(0) == true then
			
				local dist = (body2 - ownPos):LengthSquare()
				
				if dist < 900 then
					local body2ass = vec3.New()
					body2ass.x, body2ass.y, body2ass.z = Player.getBody2AssPos()
				  
					TailMC:MovementFollowUpdate(body2ass, dt)
				end
				
				OWN.getEllipsoidCollider.setR3Gravity(0, 0, 0)
				
			else
				OWN.getEllipsoidCollider.setR3Gravity(0, -6, 0)
				OWN.getEllipsoidCollider.setR3Vel(TailMC.vel.x, TailMC.vel.y, TailMC.vel.z)
				TailMC:applyFriction()
			end
			
		else
			OWN.getEllipsoidCollider.setR3Gravity(0, 0, 0)
			OWN.getEllipsoidCollider.setR3Vel(0, 0, 0)
			OWN.getTransform.setPosition(0, 1, 0)
			
		end
	end
	
	
	OWN.getEllipsoidCollider.CollisionCheck(dt)
	
end
