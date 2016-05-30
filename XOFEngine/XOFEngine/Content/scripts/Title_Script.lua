require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()
   Camera.setMouseControl(false)
   Input.CursorEnable(true)
   Scene.PlayerEnable(false)
   Scene.SkyboxEnable(false)
   Graphics.BlurBackground(true)
   Graphics.Fade(2)
   Graphics.ShadowSize(80)
   
   
end

function Update(dt)
  
  Input.CursorVsGUIAABB()
  
  
end