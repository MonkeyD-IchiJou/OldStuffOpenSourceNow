require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  
	Player.setPos(0, -10, 30, 0)
  Scene.Checkpoint(-10,30,0)
  
	Player.setPos(1, 5, 30, 0)
	Player.setPos(2, 10, 30, 0)
	Player.setPos(3, 15, 30, 0)
	
	Player.setHeadCommandState(2)
	Player.setState(0)
  
end


function Update(dt)
   
end

