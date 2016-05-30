require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
  fade = 0
  timer = 0.0
end

function Update(dt)
  
  -- When > 2s, load Outer Heaven Splash
  timer = timer + dt
  
  if timer > 4.25 then
	fade = fade + dt
  end
  OWN.getGUIText.setAlpha(fade)
  
end