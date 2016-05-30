require("Content//scripts//CamMovementC")

function Init()
  
  uistate = {
	title = true,
	mainMenu = false,
	LevelSelection = false,
	option = false,
	continue = false
  }
  
  
  translateDistance_Y = 0
  translateDistance_X = 0
  translated = false
  
  Graphics.BlurBackground(true)
   
  -- common movement stuff
  camlookingdir = vec3.New() -- this is the lookingdir
  camlookingtdir = vec3.New() -- tangent looking dir
  up = vec3.New()
  up:Set( 0, 1, 0 )
	
  Camera.setMouseControl(false)
  Camera.setZoomDistance(35)
  Camera.setCamMode(1)
  Camera.setLookingDir(1, -0.25, 0)
  Camera.setPitchLimit(85)
  
  cameraControl = cam:New()
  
  timer = 0
  
  fade = 2
  
end

function Update(dt)
  
  -- rotation camera
  camlookingdir.x, camlookingdir.y, camlookingdir.z = Camera.getLookingDir()
  camlookingdir:Normalize()
  camlookingtdir = camlookingdir:Cross(up)
	
  camlookingdir = camlookingdir + camlookingtdir * dt * 0.025
	
  Camera.setLookingDir(camlookingdir.x, camlookingdir.y, camlookingdir.z)
  
  local level1select = OWN.getCanvas.getInstruction(5)
  local level2select = OWN.getCanvas.getInstruction(6)
  local level3select = OWN.getCanvas.getInstruction(7)
  local level4select = OWN.getCanvas.getInstruction(8)
    
  -- animation
  if uistate.mainMenu == true then
	local pos = vec3.New()
	pos:Set(0, 1.25, 2)
	cameraControl:TPSCameraGOTO(pos, dt)
	cameraControl:ZOOMto(12.5, dt)
  
  elseif uistate.option == true then
	local pos = vec3.New()
	pos:Set(-8, 2, 7)
	cameraControl:TPSCameraGOTO(pos, dt)
	cameraControl:ZOOMto(9, dt)
	
  elseif uistate.LevelSelection == true then
	local pos = vec3.New()
	pos:Set(7, 1.3, -8)
	cameraControl:TPSCameraGOTO(pos, dt)
        
    if 
            level1select == false and 
            level2select == false and 
            level3select == false and 
            level4select == false 
            then
            
	   cameraControl:ZOOMto(12.5, dt)
            
    else
            
		cameraControl:ZOOMto(1000, dt)
            
    end
        
  else
    local pos = vec3.New()
	pos:Set(0, 0, 0)
	cameraControl:TPSCameraGOTO(pos, dt)
	
  end
  
  
  
  --[[ To Main Menu]]--
  
  if Input.isKeyTouched(keys.KEY_SPACE) then
    translated = true
  end
  
  if translated == true then
  
    Graphics.BlurBackground(false)
    translateDistance_Y = translateDistance_Y + dt * 2
    OWN.getTransform.Translate(0, dt * 2, 0)
    
    if (translateDistance_Y > 1.25) then
      translated = false
      OWN.getTransform.setPosition(0, 1.25, 0)
	  
      uistate.title = false
	  uistate.mainMenu = true
	  
    end
    
  end 
  
  --[[ To Level Select ]]--
  
  if OWN.getCanvas.getInstruction(0) == true then
    
    translateDistance_X = translateDistance_X + dt * 2
    OWN.getTransform.Translate(-dt * 2, 0, 0)
    
	uistate.mainMenu = false
	uistate.LevelSelection = true
	
    if (translateDistance_X > 1.25) then
    
      OWN.getCanvas.setInstruction(0, false)
      translateDistance_X = 0
      
      OWN.getTransform.setPosition(-1.25, 1.25, 0)
    end
    
  
  
  --[[ To Options ]]--
  
  elseif OWN.getCanvas.getInstruction(1) == true then
    
    translateDistance_X = translateDistance_X + dt * 2
    OWN.getTransform.Translate(dt * 2, 0, 0)
    
	uistate.mainMenu = false
	uistate.option = true
	  
    if (translateDistance_X > 1.3) then
    
      OWN.getCanvas.setInstruction(1, false)
      translateDistance_X = 0
      OWN.getTransform.setPosition(1.3, 1.25, 0)
      
	  
	  
    end
    
  
  --[[ To Main Menu, From Level Select ]]--
  
  elseif OWN.getCanvas.getInstruction(2) == true then
    
    translateDistance_X = translateDistance_X + dt * 2
    OWN.getTransform.Translate(dt * 2, 0, 0)
    
	uistate.mainMenu = true
	uistate.LevelSelection = false
	
    if (translateDistance_X > 1.25) then
    
      OWN.getCanvas.setInstruction(2, false)
      translateDistance_X = 0
      
      OWN.getTransform.setPosition(0, 1.25, 0)
      
    end
    
  
  --[[ To Main Menu, From Options ]]--
  
  elseif OWN.getCanvas.getInstruction(3) == true then
    
    translateDistance_X = translateDistance_X + dt * 2
    OWN.getTransform.Translate(-dt * 2, 0, 0)
    
	uistate.mainMenu = true
	uistate.option = false
	  
    if (translateDistance_X > 1.25) then
    
      OWN.getCanvas.setInstruction(3, false)
      translateDistance_X = 0
      
      OWN.getTransform.setPosition(0, 1.25, 0)
      
	  
	  
    end
    
  
  
  
  --[[ Continue the level ]]--
  
  elseif OWN.getCanvas.getInstruction(4) == true then
    
    translateDistance_Y = translateDistance_Y + dt * 2
    OWN.getTransform.Translate(0, dt * 2, 0)
    timer = timer + dt
	cameraControl:ZOOMto(1000, dt)
	fade = fade - dt * 1.5
	if fade < 0 then
		fade = 0
	end
	Graphics.Fade(fade)
	
	uistate.mainMenu = false
	uistate.continue = true
	  
	if timer > 2 then
		timer = 0
	
	  OWN.getCanvas.setInstruction(4, false)
	  OWN.getCanvas.setInstruction(1, true)
	  OWN.getTransform.setPosition(1.3, 1.25, 0)
      
      Scene.SkyboxEnable(true)
      Scene.PlayerEnable(true)
	  
      Graphics.BlurBackground(false)
	  Graphics.Fade(0)
	  fade = 2
	  
	  uistate.title = false
	  uistate.mainMenu = false
	  uistate.LevelSelection = false
	  uistate.option = true
	  uistate.continue = false
	  
	  translateDistance_Y = 0
	  translateDistance_X = 1.3
	  translated = false
	  
	  Input.CursorEnable(false)
	  Camera.setMouseControl(true)
	  Camera.setZoomDistance(35)
	  Camera.setPitchLimit(85)
	  
	  Scene.LoadScene(Scene.CurrentLevel(true)) -- determined which scene pls
	end
	
    --[[level 1]]--
	
	elseif level1select == true then
		translateDistance_Y = translateDistance_Y + dt * 2
        OWN.getTransform.Translate(0, dt * 2, 0)
		timer = timer + dt
		fade = fade - dt * 1.5
		if fade < 0 then
			fade = 0
		end
		Graphics.Fade(fade)
		
		uistate.mainMenu = false
		uistate.continue = true
		  
		if timer > 2 then
			timer = 0
		
		  OWN.getCanvas.setInstruction(5, false)
		  OWN.getCanvas.setInstruction(1, true)
		  OWN.getTransform.setPosition(1.3, 1.25, 0)
		  
		  Scene.SkyboxEnable(true)
		  Scene.PlayerEnable(true)
		  
		  Graphics.BlurBackground(false)
		  Graphics.Fade(0)
		  fade = 2
		  
		  uistate.title = false
		  uistate.mainMenu = false
		  uistate.LevelSelection = false
		  uistate.option = true
		  uistate.continue = false
		  
		  translateDistance_Y = 0
		  translateDistance_X = 1.3
		  translated = false
		  
		  Input.CursorEnable(false)
		  Camera.setMouseControl(true)
		  Camera.setZoomDistance(35)
		  Camera.setPitchLimit(85)
		  
          Scene.Restart("Level1")
          Scene.Restart("Level2")
          Scene.Restart("Level3")
          Scene.Restart("Level4")
		  Scene.LoadScene("Level1") -- determined which scene pls
	 
	end
	
	
	--[[level 2]]--
        
	elseif level2select == true then
		translateDistance_Y = translateDistance_Y + dt * 2
		OWN.getTransform.Translate(0, dt * 2, 0)
		timer = timer + dt
		fade = fade - dt * 1.5
		if fade < 0 then
			fade = 0
		end
		Graphics.Fade(fade)
		
		uistate.mainMenu = false
		uistate.continue = true
		  
		if timer > 2 then
			  timer = 0
		
              OWN.getCanvas.setInstruction(6, false)
              OWN.getCanvas.setInstruction(1, true)
              OWN.getTransform.setPosition(1.3, 1.25, 0)

              Scene.SkyboxEnable(true)
              Scene.PlayerEnable(true)

              Graphics.BlurBackground(false)
              Graphics.Fade(0)
              fade = 2

              uistate.title = false
              uistate.mainMenu = false
              uistate.LevelSelection = false
              uistate.option = true
              uistate.continue = false

              translateDistance_Y = 0
              translateDistance_X = 1.3
              translated = false

              Input.CursorEnable(false)
              Camera.setMouseControl(true)
              Camera.setZoomDistance(35)
              Camera.setPitchLimit(85)

              Scene.Restart("Level1")
              Scene.Restart("Level2")
              Scene.Restart("Level3")
              Scene.Restart("Level4")
              Scene.LoadScene("Level2") -- determined which scene pls
	 
	end
        
        
    --[[level 3]]--
    elseif level3select == true then
		translateDistance_Y = translateDistance_Y + dt * 2
		OWN.getTransform.Translate(0, dt * 2, 0)
		timer = timer + dt
		fade = fade - dt * 1.5
		if fade < 0 then
			fade = 0
		end
		Graphics.Fade(fade)
		
		uistate.mainMenu = false
		uistate.continue = true
		  
		if timer > 2 then
			  timer = 0
		
              OWN.getCanvas.setInstruction(7, false)
              OWN.getCanvas.setInstruction(1, true)
              OWN.getTransform.setPosition(1.3, 1.25, 0)

              Scene.SkyboxEnable(true)
              Scene.PlayerEnable(true)

              Graphics.BlurBackground(false)
              Graphics.Fade(0)
              fade = 2

              uistate.title = false
              uistate.mainMenu = false
              uistate.LevelSelection = false
              uistate.option = true
              uistate.continue = false

              translateDistance_Y = 0
              translateDistance_X = 1.3
              translated = false

              Input.CursorEnable(false)
              Camera.setMouseControl(true)
              Camera.setZoomDistance(35)
              Camera.setPitchLimit(85)

              Scene.Restart("Level1")
              Scene.Restart("Level2")
              Scene.Restart("Level3")
              Scene.Restart("Level4")
              Scene.LoadScene("Level3") -- determined which scene pls
	 
	end
        
    --[[level 4]]--
    elseif level4select == true then
		translateDistance_Y = translateDistance_Y + dt * 2
		OWN.getTransform.Translate(0, dt * 2, 0)
		timer = timer + dt
		fade = fade - dt * 1.5
		if fade < 0 then
			fade = 0
		end
		Graphics.Fade(fade)
		
		uistate.mainMenu = false
		uistate.continue = true
		  
		if timer > 2 then
			  timer = 0
		
              OWN.getCanvas.setInstruction(8, false)
              OWN.getCanvas.setInstruction(1, true)
              OWN.getTransform.setPosition(1.3, 1.25, 0)

              Scene.SkyboxEnable(true)
              Scene.PlayerEnable(true)

              Graphics.BlurBackground(false)
              Graphics.Fade(0)
              fade = 2

              uistate.title = false
              uistate.mainMenu = false
              uistate.LevelSelection = false
              uistate.option = true
              uistate.continue = false

              translateDistance_Y = 0
              translateDistance_X = 1.3
              translated = false

              Input.CursorEnable(false)
              Camera.setMouseControl(true)
              Camera.setZoomDistance(35)
              Camera.setPitchLimit(85)

              Scene.Restart("Level1")
              Scene.Restart("Level2")
              Scene.Restart("Level3")
              Scene.Restart("Level4")
              Scene.LoadScene("Level4") -- determined which scene pls
	 
	end
    
  end
  
  
  
  
  
  
  
  
  
end