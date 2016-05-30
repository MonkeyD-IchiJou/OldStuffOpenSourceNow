require("Content//scripts//Keys")
require("Content//scripts//vec3")

function Init()

end

function Update(dt)

	if OWN.getTrigger.isTrigger() == true then
       OWN.getTransform.Translate(0, 2 * dt, 0)
  end
    
end

