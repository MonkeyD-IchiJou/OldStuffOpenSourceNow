require("Content//scripts//CamMovementC")

function Init()
	cameraControl = cam:New()
end

function Update(dt)
	isAABBInside = OWN.getAABB.collideInfo(1)
	
	OWN.getAABB.checkCollide(1, "player")
	
	if isAABBInside == 0 then
		Player.EndGame(true)
        Scene.CurrentLevel("none")
	end
end