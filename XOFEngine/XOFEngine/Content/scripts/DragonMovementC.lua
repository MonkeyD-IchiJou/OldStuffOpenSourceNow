require("Content//scripts//Keys")
require("Content//scripts//vec3")

DragonMC = {
	-- gravity stuff
	jumpVel = vec3.New(),
	gravity = vec3.New(),
	gravityMaxStrength = 90,
	JUMP_POWER = 30,
	isInAir = false,
	isHitHead = false,
	SLIDING_POWER = -10,
	lastStandPos = vec3.New(),
	
	-- movement stuff
	vel = vec3.New(),
	speed = 0.6,
	THRUST_FORCE = 5.7, -- easy to move around when this is high value
	FRICTIONAL_STR = 0.15,
    rotateSpeed = -10,
    
	-- following variables
	currentPos = vec3.New(),
	movingDir = vec3.New(),
	gotospeed = 0.25,
    
	
    -- tail moving 
    sintimer = 0,
    wigglespeed = 10.0,
    wigglestrength = 10.0, -- higher number = wiggle less
	
    
	jump = function(self)

		if (self.isInAir == false) and (self.isHitHead == false) then
			self.jumpVel.y = self.JUMP_POWER
			self.lastStandPos.x, self.lastStandPos.y, self.lastStandPos.z  = OWN.getTransform.getPosition()
			self.isInAir = true
		end
		
	end,

	jumpMovement = function(self)
		-- jump vel update 
		if Input.isKeyPressed(keys.KEY_SPACE) then
			self:jump()
		end
	end,
	
	updateJumpvel = function(self, dt)

		if OWN.getEllipsoidCollider.isCollide(false) == false then
			
			self.jumpVel = self.jumpVel + self.gravity * dt
				
			-- const velocity when falling if velocity magnitude is too high
			if self.jumpVel:Length() > self.gravityMaxStrength then
				self.jumpVel = self.jumpVel:Normalized() * self.gravityMaxStrength
			end
		
		else
			
			self.isInAir = false
			
			-- if it is still moving upward .. and i found a collision .. confirm hit head
			if self.jumpVel.y > 0.0 then
			
				self.isHitHead = true
				
			else
			
				self.isHitHead = false
				
			end

			--jumpVel:Set(0, -jumpVel.y, 0) // bumper ??
			self.jumpVel:Set(0, self.SLIDING_POWER, 0)
		    return true
		end
		
	end,
	
	applyFriction = function(self)
	
		if self.isInAir == false then
			local frictionDir = vec3.New()
				
			-- cannot be zero
			frictionDir = self.vel:Normalized() * self.FRICTIONAL_STR
				
			local oldVel = vec3.New()
			oldVel = self.vel
			self.vel = self.vel - frictionDir
				
			if self.vel:Dot(oldVel) < 0.0 then
				self.vel:SetZero()
			end
		else
			local frictionDir = vec3.New()
				
			-- cannot be zero
			frictionDir = self.vel:Normalized() * 0.025
				
			local oldVel = vec3.New()
			oldVel = self.vel
			self.vel = self.vel - frictionDir
				
			if self.vel:Dot(oldVel) < 0.0 then
				self.vel:SetZero()
			end
		end
		
	end,
	
	MovementUpdate = function (self, dt)
		-- Movement -- 
		
		if Input.isKeyPressed(keys.KEY_W) then
			self.vel = self.vel + camlookingdir * dt * self.THRUST_FORCE
		end
		if Input.isKeyPressed(keys.KEY_S) then
			self.vel = self.vel + camlookingdir * -dt * self.THRUST_FORCE
		end
		if Input.isKeyPressed(keys.KEY_D) then
			self.vel = self.vel + camlookingtdir * dt * self.THRUST_FORCE
		end
		if Input.isKeyPressed(keys.KEY_A) then
			self.vel = self.vel + camlookingtdir * -dt * self.THRUST_FORCE
		end
		
		if self.vel:Length() > self.speed then
			self.vel = self.vel:Normalized() * self.speed
		end
		
        
		OWN.getEllipsoidCollider.setR3Vel(self.vel.x, self.vel.y, self.vel.z)
		
	end,
	
    TailWiggle = function (self,dt)
        
        self.sintimer = self.sintimer + dt * self.wigglespeed
        
        if self.sintimer > 360.0 then
           self.sintimer = 0 
        end
        
        local rad = math.sin(self.sintimer)
        
        OWN.getEllipsoidCollider.setR3Vel(self.vel.x, self.vel.y + rad / self.wigglestrength, self.vel.z)
    end,
	
	MovementFollowUpdate = function(self, destination, dt)
		self.currentPos.x, self.currentPos.y, self.currentPos.z = 
		OWN.getTransform.getPosition()
		
		self.movingDir = destination - self.currentPos
		self.movingDir = self.movingDir * self.gotospeed
		
		OWN.getLineRenderer.StartLine(self.currentPos.x, self.currentPos.y, self.currentPos.z)
		
		OWN.getEllipsoidCollider.setR3Vel(self.movingDir.x, self.movingDir.y, self.movingDir.z)
		
		self.vel:Set(self.movingDir.x, self.movingDir.y, self.movingDir.z)
	end,
    
    MovementFollowUpdateTail = function(self, destination, dt)
		self.currentPos.x, self.currentPos.y, self.currentPos.z = 
		OWN.getTransform.getPosition()
		
		self.movingDir = destination - self.currentPos
		self.movingDir = self.movingDir * self.gotospeed
		
		OWN.getLineRenderer.StartLine(self.currentPos.x, self.currentPos.y, self.currentPos.z)
        
        OWN.getEllipsoidCollider.setR3Vel(self.movingDir.x, self.movingDir.y, self.movingDir.z)
        
		OWN.getTransform.Translate(self.movingDir.x, self.movingDir.y, self.movingDir.z)
	end,
    
	
	-- oop new
	New = function()

		local dragonMC = {}

		-- copy all the variables into new table 
		for k, v in pairs(DragonMC) do
			dragonMC[k] = v
		end

		return dragonMC
	end,
}
