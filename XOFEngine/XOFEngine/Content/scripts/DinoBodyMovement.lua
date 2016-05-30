require("Content//assets//DinoFSMs")
require("Content//scripts//DinoMovementC")

function Init()
  dinoBodyMC = DinoMC.New()
  dinoBodyMC.gravity:Set( 0,  -90 , 0)
	dinoBodyMC.jumpVel:Set(0, -1, 0)
  dinoBodyMC.JUMP_POWER = 50
end

function Update(dt)
  
  -- need const update the jumpVel
	dinoBodyMC:updateJumpvel(dt)
 
  local bodyLookingDir = vec3.New()
  bodyLookingDir.x, bodyLookingDir.y, bodyLookingDir.z = OWN.getDinoAI.getDinoBodyLookingDir()
  OWN.getTransform.LookAt(bodyLookingDir.x, bodyLookingDir.y, bodyLookingDir.z, true)
  
  
  local state = OWN.getDinoAI.getDinoHeadFSM()
  if(state == DINOHEAD_FSM.WALK) then
    bodyLookingDir = bodyLookingDir:Normalized() * 0.2
    dinoBodyMC.vel:Set(bodyLookingDir.x, 0, bodyLookingDir.z)
    
  elseif(state == DINOHEAD_FSM.CHASE) then
    bodyLookingDir = bodyLookingDir:Normalized() * 0.4
    dinoBodyMC.vel:Set(bodyLookingDir.x, 0, bodyLookingDir.z)
  
elseif(state == DINOHEAD_FSM.SWINGATTACK) then
    --bodyLookingDir = bodyLookingDir:Normalized() * 1.2
    --dinoBodyMC.vel:Set(bodyLookingDir.x, 0, bodyLookingDir.z)
 
  elseif(state == DINOHEAD_FSM.DINOIDLE) then
    
  
  end
  
  dinoBodyMC:MovementUpdate(dt)
  dinoBodyMC:applyFriction()
  
  OWN.getEllipsoidCollider.setR3Gravity(dinoBodyMC.jumpVel.x, dinoBodyMC.jumpVel.y, dinoBodyMC.jumpVel.z)
  OWN.getEllipsoidCollider.CollisionCheck(dt)
end
