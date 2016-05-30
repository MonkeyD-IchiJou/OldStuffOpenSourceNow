require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

	timer = 0.0
	Scene.SkyboxEnable(false)
	Scene.PlayerEnable(false)
	fade = 2
end	

function Update(dt)

	Camera.setCamTarget(0, 0, 0) 
	Camera.setCamMode(1) -- FPS
	Camera.setMouseControl(false)
	Camera.setLookingDir(0, -1, 0.01) 
	Camera.setZoomDistance(46.5) 
	Camera.setPitchLimit(90)
  
  -- When > 2s, load Level 1
    timer = timer + dt
    
	
	if timer > 4.1  then
		fade = fade - dt
		if fade < 0.0 then
			fade = 0
		end
	end
	
	Graphics.Fade(fade)
	
    if timer > 6.5 or Input.isKeyTouched(keys.KEY_SPACE) then
	  Scene.LoadScene("Title")
      Scene.SkyboxEnable(false)
      Scene.PlayerEnable(false)
      Camera.setMouseControl(false)
      Camera.setLookingDir(0, -1, 1) 
      Camera.setZoomDistance(36.5) 
      Camera.setPitchLimit(80)
      Graphics.BlurBackground(true)
	  Input.CursorEnable(true)
      timer = 0
	  Graphics.Fade(2)
	  Graphics.ShadowSize(80)
	  
    end
	
	
end

