require("Content//scripts//Keys")
require("Content//scripts//vec3")

DinoAMC = {
  -- Variables
  rotateSpeed = 1,
  countTimer = 0,
  whack = true,
  rotationAmount = 0,

Update = function(self, dt)
  
  local x, y, z = OWN.getTransform.getRotation()
  
  self.rotationAmount = self.rotationAmount + 1
  
  if(self.rotationAmount > 90) then
    self.rotationAmount = self.rotationAmount - 1
  end
      
  OWN.getTransform.setRotation(0, self.rotationAmount, 0)
          
  print(self.rotationAmount)
    
end,

New = function()
    local dinoamc = {}
        
    for k, v in pairs(DinoAMC) do
			dinoamc[k] = v
		end
        
    return dinoamc
end,

}
