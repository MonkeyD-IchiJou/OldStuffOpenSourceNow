require("Content//scripts//animation")
require("Content//scripts//Keys")
require("Content//scripts//vec3")
require("Content//assets//DinoFSMs")

function Init()
  swingHand = animation.New()
	swingHand.SWINGING_SPEED = 8
end

function Update(dt)
  if(OWN.getDinoAI.getDinoHeadFSM() == DINOHEAD_FSM.DINOIDLE) then
    swingHand:stationaryPosition(dt)
    swingHand.offsetAngle = 0
  
  else
    swingHand:SwingingAnimation(dt, math.pi)
    swingHand.offsetAngle = 0
  end
  
  -- default rotation
	OWN.getTransform.setRotation(-swingHand.swing +swingHand.offsetAngle, 0, 0)
end