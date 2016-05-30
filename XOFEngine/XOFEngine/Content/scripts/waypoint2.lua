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
    self.waypoints[self.index].y = 0 
    local distance = (self.waypoints[self.index] - position):Length()

    direction = (self.waypoints[self.index] - position):Normalized()
    direction.y = 0
    
    OWN.getTransform.Translate(direction.x * dt * movespeed, 0 , direction.z * dt * movespeed)

    if distance < 1 then
        self.index = self.index +1
        if(self.index > self.size -1) then
            self.index = 1
        end

        self.n = self.n * -1
    end
    
    OWN.getTransform.LookAt(direction.x * 1000 , direction.y * 1000, direction.z * 1000, 1 )
        
end,
    
Reverse = function (self,dt,movespeed)
    
            
	self.deltaTime:Set(dt, dt, dt)

    local direction = vec3.New()
    
    local position = vec3.New()
    position.x , position.y, position.z = OWN.getTransform.getPosition()
    position.y = 0
    self.waypoints[self.index].y = 0
    local distance = (self.waypoints[self.index] - position):Length()
    
    direction = (self.waypoints[self.index] - position):Normalized()
    direction.y = 0
    
    if distance < 1 and self.index > 1 then
        self.index = self.index - 1

        self.n = self.n * -1
    end    
        
    if distance > 1 then
        OWN.getTransform.Translate(direction.x * dt * movespeed, 0 , direction.z * dt * movespeed)
        OWN.getTransform.LookAt(direction.x * 1000 , direction.y * 1000, direction.z * 1000, 1 )
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