require("Content//scripts//waypoint")


function Init()
    wp = waypoint.New()
    wp:add(20,0,20)
    wp:add(-20,0,20)
    wp:add(-20,0,-20)
    wp:add(20,-0,-20)
    
    jump = false
    
    vel = vec3.New()
    vel:Set(0,5,0)
    gravity = vec3.New()
    gravity:Set(0,-4,0)
    
end

function Update(dt)
    
    OWN.getEllipsoidCollider.setR3Gravity(vel.x, vel.y, vel.z)
    local tempG = vec3.New()
    tempG.x = gravity.x * dt
    tempG.y = gravity.y * dt
    tempG.z = gravity.z * dt
    vel = vel + tempG 
    
    if OWN.getEllipsoidCollider.isCollide(false) then
        vel:Set(0,5,0)
    end
    
	wp:Update(dt,5)

end
