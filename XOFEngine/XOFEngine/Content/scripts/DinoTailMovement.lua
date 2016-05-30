require("Content//scripts//Keys")
require("Content//scripts//vec3")

DinoTMC = {
  
  currentPos = vec3.New(),
	movingDir = vec3.New(),
  movingSpeed = 0.2, 
  
  -- Follow the body parent
  MovementFollowUpdate = function(self, destination, dt)
		self.currentPos.x, self.currentPos.y, self.currentPos.z = OWN.getTransform.getPosition()
		
		self.movingDir = destination - self.currentPos
		self.movingDir = self.movingDir * self.movingSpeed 
		
		--OWN.getEllipsoidCollider.setR3Vel(self.movingDir.x, self.movingDir.y, self.movingDir.z)
	end,
  
  -- Follow the tail parent
  MovementFollowUpdateTail = function(self, destination, dt)
		self.currentPos.x, self.currentPos.y, self.currentPos.z = 
		OWN.getTransform.getPosition()
		
		self.movingDir = destination - self.currentPos
		self.movingDir = self.movingDir * self.movingSpeed  

    OWN.getEllipsoidCollider.setR3Vel(self.movingDir.x, self.movingDir.y, self.movingDir.z)
        
		OWN.getTransform.Translate(self.movingDir.x, self.movingDir.y, self.movingDir.z)
	end,
  
  	-- oop new
	New = function()

		local dinoTMC = {}

		-- copy all the variables into new table 
		for k, v in pairs(DinoTMC) do
			dinoTMC[k] = v
		end

		return dinoTMC
	end,
}

