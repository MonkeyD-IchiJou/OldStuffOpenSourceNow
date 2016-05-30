require("Content//scripts//CamMovementC")

function Init()
	
	Player.setState(0)
	pos = vec3.New()
	
	Camera.setCamMode(1) -- tps pls
	
	cameraControl = cam:New()
end

function Update(dt)

	if Input.isKeyTouched(keys.KEY_1) then
		Player.setState(0)
		Player.setHeadCommandState(2)
	end
	if Input.isKeyTouched(keys.KEY_2) then
		Player.setState(1)
		Player.setHeadCommandState(2)
	end
	if Input.isKeyTouched(keys.KEY_3) then
		Player.setState(2)
		Player.setHeadCommandState(2)
	end
	if Input.isKeyTouched(keys.KEY_4) then
		Player.setState(3)
		Player.setHeadCommandState(2)
	end
	
	if Player.getHeadCommandState() == 0 then
		-- set the camera pos
		pos.x,pos.y,pos.z = Player.getHeadAssPos()
		local x, y, z = Player.getHeadPos()
		pos.y = y
		cameraControl:TPSCameraGOTO(pos, dt)
		cameraControl:ZOOMto(35, dt)
		
	elseif Player.getHeadCommandState() == 2 then
		-- set the camera pos
		pos.x,pos.y,pos.z = Player.getPos()
		cameraControl:TPSCameraGOTO(pos, dt)
		cameraControl:ZOOMto(25, dt)
		
	end
	

    
end

