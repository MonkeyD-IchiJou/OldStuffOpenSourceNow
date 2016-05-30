require("Content//scripts//DragonMovementC")


function Init()

	-- common movement stuff
	camlookingdir = vec3.New() -- this is the lookingdir
	camlookingtdir = vec3.New() -- tangent looking dir
	up = vec3.New()
	up:Set( 0, 1, 0 )
	
	headMC = DragonMC:New()
	headMC:jump()
	headMC:updateJumpvel(1)
	headMC:jumpMovement()
	
	headMC.gravity:Set( 0,  -90 , 0)
	headMC.jumpVel:Set(0, -1, 0)
	headMC.JUMP_POWER = 50
	
	headMC.speed = 0.5
	
	fadeSceneMah = false
	fade = 0
	
	ownPos = vec3.New()
	
end

function Update(dt)
	
	camlookingdir.x, camlookingdir.y, camlookingdir.z = Camera.getLookingDir()
	camlookingdir.y = 0
	camlookingdir:Normalize()
	camlookingtdir = camlookingdir:Cross(up)
	
	-- need const update the jumpVel
	headMC:updateJumpvel(dt)
	
	if fadeSceneMah == false then
		if Player.getState() == 0 then
		
			
			if Player.getHeadCommandState() == 0 then
				headMC.JUMP_POWER = 35
				headMC.speed = 0.5
				headMC.FRICTIONAL_STR = 0.05
			else
				headMC.JUMP_POWER = 20
				headMC.speed = 0.45
				headMC.FRICTIONAL_STR = 0.02
			end
		
			if Input.isKeyPressed(keys.KEY_F) then
				Player.setHeadCommandState(0)
			end
			
			headMC:MovementUpdate(dt)
			
			headMC:jumpMovement()
			headMC:applyFriction()
			
		else
			-- if it is not controlling .. check whether got kena push or not
			headMC.vel.x, headMC.vel.y, headMC.vel.z = OWN.getEllipsoidCollider.getR3Vel()
			headMC:applyFriction()
			
			OWN.getEllipsoidCollider.setR3Vel(headMC.vel.x, headMC.vel.y, headMC.vel.z)
		end
	end
	
	
	-- always keep track of dieing
	cx, cy, cz = OWN.getTransform.getPosition()
	
	if cy < -10 and fadeSceneMah == false then
		fadeSceneMah = true
	end
	
	if fadeSceneMah == true then
	
		fade = fade - dt
		
		if fade < 0.0 then
		
			fade = 0
			cx,cy,cz = Scene.Checkpoint(true)
      OWN.getTransform.setPosition(cx, cy, cz) -- checkpoint
			
			Player.DeadState(true)
			fadeSceneMah = false -- go back to gameplay
			
		end
		
		Graphics.Fade(fade)
	
	else
		Player.DeadState(false)
		fade = Graphics.getFade()
	end
	
	
	
	OWN.getEllipsoidCollider.setR3Gravity(headMC.jumpVel.x, headMC.jumpVel.y, headMC.jumpVel.z)
	OWN.getEllipsoidCollider.CollisionCheck(dt)
	
end


