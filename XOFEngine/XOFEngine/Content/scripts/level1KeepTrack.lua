require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	Player.setPos(0, 0, 10, 0)
	Scene.Checkpoint(0, 10, 0)

	Player.setPos(1, 5, 10, 0)
	Player.setPos(2, 10, 10, 0)
	Player.setPos(3, 15, 10, 0)
	
	Player.setHeadCommandState(2)
	Player.setState(0)
end


function Update(dt)
   
end

