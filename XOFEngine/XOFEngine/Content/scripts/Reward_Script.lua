require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
	
end	

function Update(dt)
    
    if Input.isKeyTouched(keys.KEY_SPACE)  then
		Scene.LoadScene("Title")
    end
    
end

