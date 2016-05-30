require("Content//scripts//Keys")
require("Content//scripts//vec3")

cam = {
	camCurrentTar = vec3.New(),
	movingDir = vec3.New(),
	nextPoint = vec3.New(),
	gotospeed = 6.25,
	
	camCurrentZoom = 0,
	originalZoomSpeed = 10,
	zoomspeed = 10,
	nextZoomDist = 0,

	TPSCameraGOTO = function (self, destination, dt)
		
		self.camCurrentTar.x, self.camCurrentTar.y, self.camCurrentTar.z = Camera.getCamTarget()
		
		self.movingDir = destination - self.camCurrentTar
		
		self.nextPoint = self.nextPoint + self.movingDir * dt * self.gotospeed
		Camera.setCamTarget(self.nextPoint.x, self.nextPoint.y, self.nextPoint.z)
		
	end,
	
	ZOOMto = function(self, zoomdestination, dt)
		self.nextZoomDist = Camera.getZoomDistance()
		
		if self.nextZoomDist < zoomdestination then
		
			self.nextZoomDist = self.nextZoomDist + dt * self.zoomspeed
			self.zoomspeed = self.zoomspeed + dt * 600
			
			if self.nextZoomDist > zoomdestination then
				self.nextZoomDist = zoomdestination
				self.zoomspeed = self.originalZoomSpeed
			end
			
			Camera.setZoomDistance(self.nextZoomDist)
			
		elseif self.nextZoomDist > zoomdestination then
		
			self.nextZoomDist = self.nextZoomDist - dt * self.zoomspeed
			self.zoomspeed = self.zoomspeed + dt * 500
			
			if self.nextZoomDist < zoomdestination then
				self.nextZoomDist = zoomdestination
				self.zoomspeed = self.originalZoomSpeed
			end
			
			Camera.setZoomDistance(self.nextZoomDist)
		end
		
		
	end,
	
	-- oop new
	New = function()

		local camera = {}

		-- copy all the variables into new table 
		for k, v in pairs(cam) do
			camera[k] = v
		end

		return camera
	end,
	
	
}

