require("Content//scripts//CamMovementC")

function Init()
  fade = 0
  toOption = false
  timer = 0
  
  cameraControl = cam:New()

   toendgame = false
  
end

function Update(dt)
	
	toendgame = Player.EndGame("GET")
	
	if toendgame == true then
		
		fade = Graphics.getFade()
		if fade >= 0.0 then
			fade = fade - dt * 10
			
			if fade < 0.0 then 
				fade = 0.0
			end
		
			Graphics.Fade(fade)
		end
		
		timer = timer + dt
		
		if timer > 0.75 then
			
			Scene.SkyboxEnable(false)
			Scene.PlayerEnable(false)
			Camera.setMouseControl(false)
			Camera.setLookingDir(0, -1, 1) 
			Camera.setZoomDistance(36.5) 
			Graphics.BlurBackground(true)
			Input.CursorEnable(true)
			
			Scene.Restart("Title")
			Scene.Restart("Level1")
			Scene.Restart("Level2")
			Scene.Restart("Level3")
			Scene.Restart("Level4")
			Scene.LoadScene("Reward")
			
	
		end
		
	end
	
	
	if Input.isKeyTouched(keys.KEY_ESCAPE) then
		toOption = true
	end
	
	if toOption == false then
	
		fade = Graphics.getFade()
		
		if fade <= 2.0 then
			fade = fade + dt
			
			if fade > 2.0 then 
				fade = 2.0
			end
		
			Graphics.Fade(fade)
		end
	
	else 
	
		fade = Graphics.getFade()
		if fade >= 0.0 then
			fade = fade - dt * 10
			
			if fade < 0.0 then 
				fade = 0.0
			end
		
			Graphics.Fade(fade)
		end
		
		timer = timer + dt
		
		if timer > 0.75 then
			Scene.SkyboxEnable(false)
			Scene.PlayerEnable(false)
			Input.CursorEnable(true)
			
			Camera.setMouseControl(false)
			Camera.setLookingDir(1, -0.25, 0) 
			Camera.setZoomDistance(36.5) 
			Camera.setPitchLimit(80)
			Camera.setCamTarget(0 ,0, 0) 
			Camera.setCamPosition(0 ,0, 0) 

			fade = 2
			Graphics.Fade(fade)
			toOption = false
			
			timer = 0
			
			Scene.LoadScene("Title")
		end
	
	end
	
end