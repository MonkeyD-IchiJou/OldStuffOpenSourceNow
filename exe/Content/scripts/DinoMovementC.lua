require("Content//scripts//Keys")
require("Content//scripts//vec3")

DinoMC = {
	-- gravity stuff
	jumpVel = vec3.New(),
	gravity = vec3.New(),
	gravityMaxStrength = 90,
	JUMP_POWER = 30,
	isInAir = false,
	isHitHead = false,
	SLIDING_POWER = -10,
	
	-- movement stuff
	vel = vec3.New(),
	speed = 0.6,
	THRUST_FORCE = 5.7, -- easy to move around when this is high value
	FRICTIONAL_STR = 0.05,
	
    
	jump = function(self)

		if (self.isInAir == false) and (self.isHitHead == false) then
			self.jumpVel.y = self.JUMP_POWER
			self.isInAir = true
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
		end
		
	end,
	
	MovementUpdate = function (self, dt)
		-- Movement -- 
		OWN.getEllipsoidCollider.setR3Vel(self.vel.x, self.vel.y, self.vel.z)
		
	end,
	
	-- oop new
	New = function()

		local dinoMC = {}

		-- copy all the variables into new table 
		for k, v in pairs(DinoMC) do
			dinoMC[k] = v
		end

		return dinoMC
	end,
}
