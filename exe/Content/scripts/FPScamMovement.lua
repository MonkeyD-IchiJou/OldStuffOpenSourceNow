require("Content//scripts//Keys")
require("Content//scripts//vec3")


function Init()

	dir = vec3.New()
	tdir = vec3.New()
	up = vec3.New()
	pos = vec3.New()
	speed = vec3.New()
	deltaTime = vec3.New()

	speed:Set(50, 50, 50)
	up:Set( 0,  1, 0)

	pos.x, pos.y, pos.z = Camera.getCamPosition()
end

function Update(dt)

	deltaTime:Set(dt, dt, dt)

	dir.x, dir.y, dir.z = Camera.getLookingDir()
	dir.y = 0;
	tdir = dir:Cross(up);

	if Input.isKeyPressed(keys.KEY_W) == true then
		pos = pos + dir * speed * deltaTime;
	end

	if Input.isKeyPressed(keys.KEY_S) == true then
		pos = pos - dir * speed * deltaTime;
	end

	if Input.isKeyPressed(keys.KEY_A) == true then
		pos = pos - tdir * speed * deltaTime;
	end

	if Input.isKeyPressed(keys.KEY_D) == true then
		pos = pos + tdir * speed * deltaTime;
	end
	
	if Input.isKeyPressed(keys.KEY_SPACE) == true then
		pos.y = pos.y + 1.0 * speed.y * dt;
	end
	
	if Input.isKeyPressed(keys.KEY_C) == true then
		pos.y = pos.y - 1.0 * speed.y * dt;
	end

	-- set the camera pos
	Camera.setCamPosition(pos.x, pos.y, pos.z)
	

end

