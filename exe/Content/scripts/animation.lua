animation = {
	swing = 0,
	timer = 0,
	SWINGING_SPEED = 20,
  offsetAngle = 0,
	
	SwingingAnimation = function (self, dt, limit)
		self.timer = self.timer + dt * self.SWINGING_SPEED

		if self.timer > limit then
		
			self.timer = 0
		end

		self.swing = math.deg(math.sin(self.timer))
	end,
	
	stationaryPosition = function(self, dt)
		if self.swing < 0 then
		
			self:SwingingAnimation(dt, math.pi * 2.0)

		elseif self.swing > 0 then
		
			self:SwingingAnimation(dt, math.pi)
		end
	end,
	
	-- oop new
	New = function()

		local anim = {}

		-- copy all the variables into new table 
		for k, v in pairs(animation) do
			anim[k] = v
		end

		return anim
	end,
	
}


