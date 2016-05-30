require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	
	timer = 0.0
	Scene.SkyboxEnable(false)
	Scene.PlayerEnable(false)
	  
	Camera.setCamTarget(0, 0, 0) 
	Camera.setCamMode(1) -- TPS
	Camera.setMouseControl(false)
	Camera.setLookingDir(-1, 0, 0) 
end	

function Update(dt)
    
    timer = timer + dt
    
    if timer > 5.75 or Input.isKeyTouched(keys.KEY_SPACE) then
	
		Graphics.BlurBackground(false)
		Scene.PlayerEnable(false)
		Scene.SkyboxEnable(false)
		Scene.LoadScene("OuterHeaven")
      
    end
    
end

