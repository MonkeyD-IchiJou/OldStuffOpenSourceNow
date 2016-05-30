require("Content//assets//DinoFSMs")
require("Content//scripts//waypoint")


function Init()
  ownRotationAngle = 0
  bodyLookingDir = vec3.New()
  bodyLookingDir:Set(1, 0, 0.5)
  bodyrotatespeed = 2

  waypointWP = waypoint.New()
  waypointWP:add(90, 0, -20)
  waypointWP:add(100, 0, 20)
  waypointWP:add(90, 0, 20)
  waypointWP:add(100, 0, -20)
  
  basePoint = vec3.New()
  basePoint:Set(110, 0, 0)

  countTimer = 0
  givenTimeWalking = 10
  givenTimeRest = 2
  changeState = false
  
  headLookingDir = vec3.New()
  myHeadPos = vec3.New()
  waypointPos = vec3.New()
  
  headLookingDir:Set(1, 0, 0)
  playerPos = vec3.New()
  
  swingAttack = false
  swingTimer = 0
end

function Update(dt)

	--My Head always stick with the Body

  myHeadPos.x, myHeadPos.y, myHeadPos.z = OWN.getDinoAI.getBodyPosition()
  myHeadPos.y = myHeadPos.y -4.8
  OWN.getTransform.setPosition(myHeadPos.x, myHeadPos.y, myHeadPos.z)
  
	headsaw = OWN.getDinoAI.dinoSeePlayer(0)
	body1saw = OWN.getDinoAI.dinoSeePlayer(1)
	body2saw = OWN.getDinoAI.dinoSeePlayer(2)
	tailsaw = OWN.getDinoAI.dinoSeePlayer(3)
	
  -- Let the head decide what to do with the body
  if(changeState == false) then
    -- Set the timer
    countTimer = countTimer + dt

    if(countTimer > givenTimeWalking) then
      changeState = true
      OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.DINOIDLE)
    end

  else
  
    countTimer = countTimer - dt

    if(countTimer < givenTimeWalking - givenTimeRest) then
      countTimer = 0
      changeState = false  
      OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.WALK)
    end

  end
  
  if body2saw == true then
		OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.CHASE)
		playerPos.x, playerPos.y, playerPos.z = Player.getBody2Pos()
		
		OWN.getDinoAI.AttackPlayer(false)
		if ((playerPos - myHeadPos):LengthSquare() < 5.0 * 5.0 ) then
			swingAttack = true
			OWN.getDinoAI.AttackPlayer(true)
		end
		
  
		
  elseif body1saw == true then
		OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.CHASE)
		playerPos.x, playerPos.y, playerPos.z = Player.getBody1Pos()
		
		OWN.getDinoAI.AttackPlayer(false)
		if ((playerPos - myHeadPos):LengthSquare() < 5.0 * 5.0 ) then
			swingAttack = true
			OWN.getDinoAI.AttackPlayer(true)
		end
  
  
  elseif headsaw == true then
		OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.CHASE)
		playerPos.x, playerPos.y, playerPos.z = Player.getHeadPos()
		
		OWN.getDinoAI.AttackPlayer(false)
		if ((playerPos - myHeadPos):LengthSquare() < 8.0 * 8.0 ) then
			swingAttack = true
			OWN.getDinoAI.AttackPlayer(true)
		end
		
  elseif tailsaw == true then
		OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.CHASE)
		playerPos.x, playerPos.y, playerPos.z = Player.getTailPos()
		OWN.getDinoAI.AttackPlayer(false)
		if ((playerPos - myHeadPos):LengthSquare() < 8.0 * 8.0 ) then
			OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.DINOIDLE)
		end
  end
  
  if swingAttack == true then
	swingTimer = swingTimer + dt
	if swingTimer < 1 then
		OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.SWINGATTACK)
	else
		swingTimer = 0
		swingAttack = false
	end
  end
  
  
  -- if go too far .. dun chase liao
  if ((basePoint - myHeadPos):LengthSquare() > 40.0 * 40.0 ) then
	OWN.getDinoAI.setDinoHeadFSM(DINOHEAD_FSM.WALK)
  end

  

  -- Update the Waypoint for dinosaur
  waypointWP:UpdateE(dt, 10)
  bodyrotatespeed = 2
  -- Dinosaur will look at the waypoint

  state = OWN.getDinoAI.getDinoHeadFSM()
  if(state == DINOHEAD_FSM.WALK or state == DINOHEAD_FSM.DINOIDLE) then
  
	if tailsaw == true then
		waypointPos = playerPos
	else
		waypointPos = waypointWP.imaginaryFriendPos
	end

    OWN.getTransform.LookAt(waypointPos.x, waypointPos.y, waypointPos.z, false)

    headLookingDir = waypointPos - myHeadPos
    OWN.getDinoAI.setDinoHeadLookingDir(headLookingDir.x, headLookingDir.y, headLookingDir.z)

  end

  if(state == DINOHEAD_FSM.CHASE) then
    waypointPos = playerPos

    OWN.getTransform.LookAt(waypointPos.x, waypointPos.y, waypointPos.z, false)

    headLookingDir = waypointPos - myHeadPos
    OWN.getDinoAI.setDinoHeadLookingDir(headLookingDir.x, headLookingDir.y, headLookingDir.z)
  end


  if(state == DINOHEAD_FSM.SWINGATTACK) then
    
    bodyrotatespeed = 25
    
    local Cross = vec3.New()
    local Up = vec3.New()
    Up:Set(0, 1, 0)
    Cross = Up:Cross(headLookingDir)
    headLookingDir = headLookingDir + Cross * dt * 20
    
    OWN.getDinoAI.setDinoHeadLookingDir(headLookingDir.x, headLookingDir.y, headLookingDir.z)
    
    OWN.getTransform.LookAt(headLookingDir.x, headLookingDir.y, headLookingDir.z, true)
    
  end


  -- The head will decide the body looking direction
  bodyLookingDir = bodyLookingDir + headLookingDir:Normalized() * dt * bodyrotatespeed
  bodyLookingDir:Normalize()
  OWN.getDinoAI.setDinoBodyLookingDir(bodyLookingDir.x, bodyLookingDir.y, bodyLookingDir.z)



end
