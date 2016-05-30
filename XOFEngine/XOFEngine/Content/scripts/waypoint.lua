require("Content//scripts//Keys")
require("Content//scripts//vec3")

--------------- waypoint class -------------------
waypoint = {
    
    waypoints = {},
    size = 1,
    deltaTime = vec3.New(),

    dir = vec3.New(),

    index = 1,
    n = 1,
    
    imaginaryFriendPos = vec3.New(),
    
add = function (self,nx,ny,nz)
   local position = vec3.New() 
    position:Set(nx,ny,nz)
   self.waypoints[self.size] = position
   self.size = self.size + 1
        
end,

Update = function (self,dt,movespeed)
        
        
	self.deltaTime:Set(dt, dt, dt)

    local direction = vec3.New()
    
    local position = vec3.New()
    position.x , position.y, position.z = OWN.getTransform.getPosition()
    position.y = 0
    local distance = (self.waypoints[self.index] - position):Length()
        
    direction = (self.waypoints[self.index] - position):Normalized()
    direction.y = 0
        
    OWN.getEllipsoidCollider.setR3Vel(direction.x * dt * movespeed, 0 , direction.z * dt * movespeed)
    
    -- ***********************  no gravity for waypoint *************************
    --OWN.getEllipsoidCollider.setR3Gravity(0, -3, 0)
        
    --OWN.getEllipsoidCollider.CollisionCheck(dt)
    
    if distance < 1 then

        self.index = self.index +1
        if(self.index > self.size -1) then
            self.index = 1
        end

        self.n = self.n * -1
    end    
    
    OWN.getTransform.LookAt(direction.x * 1000 , direction.y * 1000, direction.z * 1000, 1 )

end,
    
    
UpdateE = function(self, dt, moveSpeed)
  
    local direction = vec3.New()
    direction = self.waypoints[self.index] - self.imaginaryFriendPos
    local distance = direction:Length()
    direction = direction:Normalized()
    direction.y = 0
        
    self.imaginaryFriendPos = self.imaginaryFriendPos + direction * dt * moveSpeed
    
    if distance < 1.0 then

        self.index = self.index +1
        if(self.index > self.size -1) then
            self.index = 1
        end
      -- Make sure that the index is positive
        self.n = self.n * -1
    end
end,

    
New = function()
    local wp = {}
        
    for k, v in pairs(waypoint) do
			wp[k] = v
		end
        
    return wp
end,
}
