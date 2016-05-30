require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  
  --[[
  
    Positions:
      OG Pos - 102.2
      Level2 Pos - 132.2
      Level3 Pos - 162.2
      Level4 Pos - 192.2 - optional
  
  ]]--
 
	Player.setPos(0, -10, 102.2, -30)
  Scene.Checkpoint(-10, 102.2, 30)
	Player.setPos(1, 5, 102.2, -30)
	Player.setPos(2, 10, 102.2, -30)
	Player.setPos(3, 15, 102.2, -30)
	
	Player.setHeadCommandState(2)
	Player.setState(0)
  
end


function Update(dt)
   
end

