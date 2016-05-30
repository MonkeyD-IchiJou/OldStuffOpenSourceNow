require("Content//assets//finalendpointassets")
require("Content//assets//dinoassets")
require("Content//assets//cloudassets")

--[[

  Colors:
    Moving plaftorm (0.5, 1, 0.5)
    Normal platform (0.8, 0.8, 0.8)
    Wall (1, 0.8, 0.8)
    Ramp (0.5, 0.5, 1)
    "Cloud" (0.4, 1, 0.9)
    Body buttons (1, 0, 0)
    Head button (1, 0, 1)
    
]]--

AddDinoEntity(900, 0, 150, 0, 'Content//scripts//dinogerall4.lua')

Entity.New(4, 'Level 1' ) 
Entity.setActive(4, true) 
Entity.addTag(4, "wall") 
Entity.getTransform.setPosition(4, 0, 100, 0) 
Entity.getTransform.setRotation(4, 0, 0, 0) 
Entity.getTransform.setScale(4, 100, 1, 100) 
Entity.addMeshRenderer(4) 
Entity.getMeshRenderer.setName(4, 'CUBE') 
Entity.getMeshRenderer.setColor(4, 0.5, 1, 0.5) 
Entity.getMeshRenderer.setShininess(4, 32) 
Entity.getMeshRenderer.setEmissive(4, 0) 
Entity.addSphereCollider(4) 
Entity.getSphereCollider.setRadius(4, 50) 
Entity.getSphereCollider.addTag(4, "MESHCULL")
Entity.addAABBCollider(4, 1) 
Entity.getAABBCollider.setHalfSize(4, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(4, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(4, 1, "wall")
Entity.addMeshCollider(4)
Entity.getMeshCollider.setName(4, "CUBE")
Entity.addTrigger(4)
Entity.addScript(4)
Entity.getScript.setPath(4, 'Content//scripts//byebyebye.lua')

--[[ Four Walls]]--

--[
Entity.New(5 , 'wall 1' ) 
Entity.setActive(5 , true) 
Entity.addTag(5 , "wall") 
Entity.getTransform.setPosition(5, 0, 180, -49.5) 
Entity.getTransform.setRotation(5, 90, 0, 0) 
Entity.getTransform.setScale(5, 100, 1, 180) 
--[[Entity.addMeshRenderer(5) 
Entity.getMeshRenderer.setName(5, 'CUBE') 
Entity.getMeshRenderer.setColor(5, 1, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(5, 32) 
Entity.getMeshRenderer.setEmissive(5, 0) ]]--
Entity.addSphereCollider(5) 
Entity.getSphereCollider.setRadius(5, 50) 
Entity.getSphereCollider.addTag(5, "MESHCULL")
Entity.addAABBCollider(5, 1) 
Entity.getAABBCollider.setHalfSize(5, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(5, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(5, 1, "wall")
Entity.addMeshCollider(5)
Entity.getMeshCollider.setName(5, "CUBE")

Entity.New(6 , 'wall 2' ) 
Entity.setActive(6 , true) 
Entity.addTag(6 , "wall") 
Entity.getTransform.setPosition(6, 0, 180, 50) 
Entity.getTransform.setRotation(6, 90, 0, 0) 
Entity.getTransform.setScale(6, 100, 1, 180) 
--[[Entity.addMeshRenderer(6) 
Entity.getMeshRenderer.setName(6, 'CUBE') 
Entity.getMeshRenderer.setColor(6, 1, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(6, 32) 
Entity.getMeshRenderer.setEmissive(6, 0) ]]--
Entity.addSphereCollider(6) 
Entity.getSphereCollider.setRadius(6, 50) 
Entity.getSphereCollider.addTag(6, "MESHCULL")
Entity.addAABBCollider(6, 1) 
Entity.getAABBCollider.setHalfSize(6, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(6, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(6, 1, "wall")
Entity.addMeshCollider(6)
Entity.getMeshCollider.setName(6, "CUBE")

Entity.New(7 , 'wall 3' ) 
Entity.setActive(7 , true) 
Entity.addTag(7 , "wall") 
Entity.getTransform.setPosition(7, 51, 180, 2) 
Entity.getTransform.setRotation(7, 90, 90, 0) 
Entity.getTransform.setScale(7, 100, 1, 180) 
--[[Entity.addMeshRenderer(7) 
Entity.getMeshRenderer.setName(7, 'CUBE') 
Entity.getMeshRenderer.setColor(7, 1, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(7, 32) 
Entity.getMeshRenderer.setEmissive(7, 0) ]]--
Entity.addSphereCollider(7) 
Entity.getSphereCollider.setRadius(7, 50) 
Entity.getSphereCollider.addTag(7, "MESHCULL")
Entity.addAABBCollider(7, 1) 
Entity.getAABBCollider.setHalfSize(7, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(7, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(7, 1, "wall")
Entity.addMeshCollider(7)
Entity.getMeshCollider.setName(7, "CUBE")


Entity.New(8 , 'wall 4' ) 
Entity.setActive(8, true) 
Entity.addTag(8, "wall") 
Entity.getTransform.setPosition(8, -49, 180, 2) 
Entity.getTransform.setRotation(8, 90, 90, 0) 
Entity.getTransform.setScale(8, 100, 1, 180) 
--[[Entity.addMeshRenderer(8) 
Entity.getMeshRenderer.setName(8, 'CUBE') 
Entity.getMeshRenderer.setColor(8, 1, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(8, 32) 
Entity.getMeshRenderer.setEmissive(8, 0) ]]--
Entity.addSphereCollider(8) 
Entity.getSphereCollider.setRadius(8, 50) 
Entity.getSphereCollider.addTag(8, "MESHCULL")
Entity.addAABBCollider(8, 1) 
Entity.getAABBCollider.setHalfSize(8, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(8, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(8, 1, "wall")
Entity.addMeshCollider(8)
Entity.getMeshCollider.setName(8, "CUBE")

--]]

-----------------------------------------------

--[[ Level 2 ]]--

Entity.New(21, 'Level 2 - 1' ) 
Entity.setActive(21, true) 
Entity.addTag(21, "wall") 
Entity.getTransform.setPosition(21, 30, 130, 0) 
Entity.getTransform.setRotation(21, 0, 0, 0) 
Entity.getTransform.setScale(21, 40, 2.3, 100.5) 
Entity.addMeshRenderer(21) 
Entity.getMeshRenderer.setName(21, 'CUBE') 
Entity.getMeshRenderer.setColor(21, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(21, 32) 
Entity.getMeshRenderer.setEmissive(21, 0) 
Entity.addSphereCollider(21) 
Entity.getSphereCollider.setRadius(21, 50) 
Entity.getSphereCollider.addTag(21, "MESHCULL")
Entity.addAABBCollider(21, 1) 
Entity.getAABBCollider.setHalfSize(21, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(21, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(21, 1, "wall")
Entity.addMeshCollider(21)
Entity.getMeshCollider.setName(21, "CUBE")

Entity.New(22, 'Level 2 - 2' ) 
Entity.setActive(22, true) 
Entity.addTag(22, "wall") 
Entity.getTransform.setPosition(22, -20, 130, -33) 
Entity.getTransform.setRotation(22, 0, 0, 0) 
Entity.getTransform.setScale(22, 60, 2.3, 35) 
Entity.addMeshRenderer(22) 
Entity.getMeshRenderer.setName(22, 'CUBE') 
Entity.getMeshRenderer.setColor(22, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(22, 32) 
Entity.getMeshRenderer.setEmissive(22, 0) 
Entity.addSphereCollider(22) 
Entity.getSphereCollider.setRadius(22, 50) 
Entity.getSphereCollider.addTag(22, "MESHCULL")
Entity.addAABBCollider(22, 1) 
Entity.getAABBCollider.setHalfSize(22, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(22, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(22, 1, "wall")
Entity.addMeshCollider(22)
Entity.getMeshCollider.setName(22, "CUBE")


Entity.New(23, 'Level 2 - 3' ) 
Entity.setActive(23, true) 
Entity.addTag(23, "wall") 
Entity.getTransform.setPosition(23, -20, 130, 33) 
Entity.getTransform.setRotation(23, 0, 0, 0) 
Entity.getTransform.setScale(23, 60, 2.3, 35) 
Entity.addMeshRenderer(23) 
Entity.getMeshRenderer.setName(23, 'CUBE') 
Entity.getMeshRenderer.setColor(23, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(23, 32) 
Entity.getMeshRenderer.setEmissive(23, 0) 
Entity.addSphereCollider(23) 
Entity.getSphereCollider.setRadius(23, 50) 
Entity.getSphereCollider.addTag(23, "MESHCULL")
Entity.addAABBCollider(23, 1) 
Entity.getAABBCollider.setHalfSize(23, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(23, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(23, 1, "wall")
Entity.addMeshCollider(23)
Entity.getMeshCollider.setName(23, "CUBE")

Entity.New(24, 'Level 2 - 4' ) 
Entity.setActive(24, true) 
Entity.addTag(24, "wall") 
Entity.getTransform.setPosition(24, -24, 130, 0) 
Entity.getTransform.setRotation(24, 0, 0, 0) 
Entity.getTransform.setScale(24, 24, 2.3, 32) 
Entity.addMeshRenderer(24) 
Entity.getMeshRenderer.setName(24, 'CUBE') 
Entity.getMeshRenderer.setColor(24, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(24, 32) 
Entity.getMeshRenderer.setEmissive(24, 0) 
Entity.addSphereCollider(24) 
Entity.getSphereCollider.setRadius(24, 50) 
Entity.getSphereCollider.addTag(24, "MESHCULL")
Entity.addAABBCollider(24, 1) 
Entity.getAABBCollider.setHalfSize(24, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(24, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(24, 1, "wall")
Entity.addMeshCollider(24)
Entity.getMeshCollider.setName(24, "CUBE")

Entity.New(25, 'Level 2 platform' ) 
Entity.setActive(25, true) 
Entity.addTag(25, "wall") 
Entity.addParent(25, 4)
Entity.getTransform.setPosition(25, 0, 30, 0) 
Entity.getTransform.setRotation(25, 0, 0, 0) 
Entity.getTransform.setScale(25, 25, 1, 35) 
Entity.addMeshRenderer(25) 
Entity.getMeshRenderer.setName(25, 'CUBE') 
Entity.getMeshRenderer.setColor(25, 0.5, 1, 0.5) 
Entity.getMeshRenderer.setShininess(25, 32) 
Entity.getMeshRenderer.setEmissive(25, 0) 
Entity.addSphereCollider(25) 
Entity.getSphereCollider.setRadius(25, 100) 
Entity.getSphereCollider.addTag(25, "MESHCULL")
Entity.addAABBCollider(25, 1) 
Entity.getAABBCollider.setHalfSize(25, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(25, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(25, 1, "wall")
Entity.addMeshCollider(25)
Entity.getMeshCollider.setName(25, "CUBE")

Entity.New(26, 'Level 2 ramp' ) 
Entity.setActive(26, true) 
Entity.addTag(26, "wall") 
Entity.getTransform.setPosition(26, -42.5, 121, 1) 
Entity.getTransform.setRotation(26, 0, 0, 0)  -- 25
Entity.getTransform.setScale(26, 13.5, 1, 37) 
Entity.addMeshRenderer(26) 
Entity.getMeshRenderer.setName(26, 'CUBE') 
Entity.getMeshRenderer.setColor(26, 0.5, 0.5, 1) 
Entity.getMeshRenderer.setShininess(26, 32) 
Entity.getMeshRenderer.setEmissive(26, 0) 
Entity.addSphereCollider(26) 
Entity.getSphereCollider.setRadius(26, 100) 
Entity.getSphereCollider.addTag(26, "MESHCULL")
Entity.addAABBCollider(26, 1) 
Entity.getAABBCollider.setHalfSize(26, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(26, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(26, 1, "wall")
Entity.addMeshCollider(26)
Entity.getMeshCollider.setName(26, "CUBE")
Entity.addTrigger(26)
Entity.addScript(26)
Entity.getScript.setPath(26, 'Content//scripts//RampMove1.lua')


-- Cloud
AddCloudEntity(27, 
-44, 109, 25,   -- Pos
10, 2, 10,    -- Scale
0.4, 1, 0.9)  -- Color

Entity.New(28, 'Level 2 booster' ) 
Entity.setActive(28, true) 
Entity.addTag(28, "wall") 
Entity.getTransform.setPosition(28, -42.5, 102, 33) 
Entity.getTransform.setRotation(28, 0, 0, 0) 
Entity.getTransform.setScale(28, 10, 1, 35) 
Entity.addMeshRenderer(28) 
Entity.getMeshRenderer.setName(28, 'CUBE') 
Entity.getMeshRenderer.setColor(28, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(28, 32) 
Entity.getMeshRenderer.setEmissive(28, 0) 
Entity.addSphereCollider(28) 
Entity.getSphereCollider.setRadius(28, 100) 
Entity.getSphereCollider.addTag(28, "MESHCULL")
Entity.addAABBCollider(28, 1) 
Entity.getAABBCollider.setHalfSize(28, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(28, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(28, 1, "wall")
Entity.addMeshCollider(28)
Entity.getMeshCollider.setName(28, "CUBE")

Entity.New(291, 'Level 2 button 1' ) 
Entity.setActive(291, true) 
Entity.addTag(291, "button") 
Entity.getTransform.setPosition(291, 30, 101, 15) 
Entity.getTransform.setRotation(291, 0, 0, 0) 
Entity.getTransform.setScale(291, 7, 1, 7) 
Entity.addMeshRenderer(291) 
Entity.getMeshRenderer.setName(291, 'CUBE') 
Entity.getMeshRenderer.setColor(291, 1, 0, 0) 
Entity.getMeshRenderer.setShininess(291, 32) 
Entity.getMeshRenderer.setEmissive(291, 0) 
Entity.addSphereCollider(291) 
Entity.getSphereCollider.setRadius(291, 100) 
Entity.getSphereCollider.addTag(291, "MESHCULL")
Entity.addAABBCollider(291, 1) 
Entity.getAABBCollider.setHalfSize(291, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(291, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(291, 1, "button")
Entity.addMeshCollider(291)
Entity.getMeshCollider.setName(291, "CUBE")
Entity.addScript(291) 
Entity.getScript.setPath(291, 'Content//scripts//L4_F1B1.lua')
Entity.TriggerLock(291, 26)
--]]

Entity.New(292, 'Level 2 button 2' ) 
Entity.setActive(292, true) 
Entity.addTag(292, "button") 
Entity.getTransform.setPosition(292, 30, 101, -15) 
Entity.getTransform.setRotation(292, 0, 0, 0) 
Entity.getTransform.setScale(292, 7, 1, 7) 
Entity.addMeshRenderer(292) 
Entity.getMeshRenderer.setName(292, 'CUBE') 
Entity.getMeshRenderer.setColor(292, 1, 0, 0) 
Entity.getMeshRenderer.setShininess(292, 32) 
Entity.getMeshRenderer.setEmissive(292, 0) 
Entity.addSphereCollider(292) 
Entity.getSphereCollider.setRadius(292, 100) 
Entity.getSphereCollider.addTag(292, "MESHCULL")
Entity.addAABBCollider(292, 1) 
Entity.getAABBCollider.setHalfSize(292, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(292, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(292, 1, "button")
Entity.addMeshCollider(292)
Entity.getMeshCollider.setName(292, "CUBE")
Entity.addScript(292) 
Entity.getScript.setPath(292, 'Content//scripts//L4_F1B2.lua')
Entity.TriggerLock(292, 26)

-----------------------------------------------

--[[ Level 3 ]]--


Entity.New(31, 'Level 3 - 1' ) 
Entity.setActive(31, true) 
Entity.addTag(31, "wall") 
Entity.getTransform.setPosition(31, 30, 160, 0) 
Entity.getTransform.setRotation(31, 0, 0, 0) 
Entity.getTransform.setScale(31, 40, 2, 100.5) 
Entity.addMeshRenderer(31) 
Entity.getMeshRenderer.setName(31, 'CUBE') 
Entity.getMeshRenderer.setColor(31, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(31, 32) 
Entity.getMeshRenderer.setEmissive(31, 0) 
Entity.addSphereCollider(31) 
Entity.getSphereCollider.setRadius(31, 50) 
Entity.getSphereCollider.addTag(31, "MESHCULL")
Entity.addAABBCollider(31, 1) 
Entity.getAABBCollider.setHalfSize(31, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(31, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(31, 1, "wall")
Entity.addMeshCollider(31)
Entity.getMeshCollider.setName(31, "CUBE")

Entity.New(32, 'Level 3 - 2' ) 
Entity.setActive(32, true) 
Entity.addTag(32, "wall") 
Entity.getTransform.setPosition(32, -20, 160, -33) 
Entity.getTransform.setRotation(32, 0, 0, 0) 
Entity.getTransform.setScale(32, 60, 2, 35) 
Entity.addMeshRenderer(32) 
Entity.getMeshRenderer.setName(32, 'CUBE') 
Entity.getMeshRenderer.setColor(32, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(32, 32) 
Entity.getMeshRenderer.setEmissive(32, 0) 
Entity.addSphereCollider(32) 
Entity.getSphereCollider.setRadius(32, 50) 
Entity.getSphereCollider.addTag(32, "MESHCULL")
Entity.addAABBCollider(32, 1) 
Entity.getAABBCollider.setHalfSize(32, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(32, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(32, 1, "wall")
Entity.addMeshCollider(32)
Entity.getMeshCollider.setName(32, "CUBE")


Entity.New(33, 'Level 3 - 3' ) 
Entity.setActive(33, true) 
Entity.addTag(33, "wall") 
Entity.getTransform.setPosition(33, -20, 160, 33) 
Entity.getTransform.setRotation(33, 0, 0, 0) 
Entity.getTransform.setScale(33, 60, 2, 35) 
Entity.addMeshRenderer(33) 
Entity.getMeshRenderer.setName(33, 'CUBE') 
Entity.getMeshRenderer.setColor(33, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(33, 32) 
Entity.getMeshRenderer.setEmissive(33, 0) 
Entity.addSphereCollider(33) 
Entity.getSphereCollider.setRadius(33, 50) 
Entity.getSphereCollider.addTag(33, "MESHCULL")
Entity.addAABBCollider(33, 1) 
Entity.getAABBCollider.setHalfSize(33, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(33, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(33, 1, "wall")
Entity.addMeshCollider(33)
Entity.getMeshCollider.setName(33, "CUBE")

Entity.New(34, 'Level 3 - 4' ) 
Entity.setActive(34, true) 
Entity.addTag(34, "wall") 
Entity.getTransform.setPosition(34, -24, 160, 0) 
Entity.getTransform.setRotation(34, 0, 0, 0) 
Entity.getTransform.setScale(34, 24, 2, 32) 
Entity.addMeshRenderer(34) 
Entity.getMeshRenderer.setName(34, 'CUBE') 
Entity.getMeshRenderer.setColor(34, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(34, 32) 
Entity.getMeshRenderer.setEmissive(34, 0) 
Entity.addSphereCollider(34) 
Entity.getSphereCollider.setRadius(34, 50) 
Entity.getSphereCollider.addTag(34, "MESHCULL")
Entity.addAABBCollider(34, 1) 
Entity.getAABBCollider.setHalfSize(34, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(34, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(34, 1, "wall")
Entity.addMeshCollider(34)
Entity.getMeshCollider.setName(34, "CUBE")

Entity.New(35, 'Level 3 platform' ) 
Entity.setActive(35, true) 
Entity.addTag(35, "wall") 
Entity.getTransform.setPosition(35, 0, 160, 0) 
Entity.getTransform.setRotation(35, 0, 0, 0) 
Entity.getTransform.setScale(35, 25, 1, 35) 
Entity.addMeshRenderer(35) 
Entity.getMeshRenderer.setName(35, 'CUBE') 
Entity.getMeshRenderer.setColor(35, 0.5, 1, 0.5) 
Entity.getMeshRenderer.setShininess(35, 32) 
Entity.getMeshRenderer.setEmissive(35, 0) 
Entity.addSphereCollider(35) 
Entity.getSphereCollider.setRadius(35, 100) 
Entity.getSphereCollider.addTag(35, "MESHCULL")
Entity.addAABBCollider(35, 1) 
Entity.getAABBCollider.setHalfSize(35, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(35, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(35, 1, "wall")
Entity.addMeshCollider(35)
Entity.getMeshCollider.setName(35, "CUBE")

--[[ Lift ]]--
-- OG y - 160
Entity.New(361, 'Level 3 lift 1' ) 
Entity.setActive(361, true) 
Entity.addTag(361, "wall") 
Entity.getTransform.setPosition(361, -42.5, 160, 7) -- 137
Entity.getTransform.setRotation(361, 0, 0, 0) 
Entity.getTransform.setScale(361, 13.5, 1, 35) 
Entity.addMeshRenderer(361) 
Entity.getMeshRenderer.setName(361, 'CUBE') 
Entity.getMeshRenderer.setColor(361, 0.5, 0.5, 1) 
Entity.getMeshRenderer.setShininess(361, 32) 
Entity.getMeshRenderer.setEmissive(361, 0) 
Entity.addSphereCollider(361) 
Entity.getSphereCollider.setRadius(361, 100) 
Entity.getSphereCollider.addTag(361, "MESHCULL")
Entity.addAABBCollider(361, 1) 
Entity.getAABBCollider.setHalfSize(361, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(361, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(361, 1, "wall")
Entity.addMeshCollider(361)
Entity.getMeshCollider.setName(361, "CUBE")

Entity.New(362, 'Level 3 lift 2' ) 
Entity.setActive(362, true) 
Entity.addTag(362, "wall") 
Entity.getTransform.setPosition(362, -42.5, 160, 0) -- 144
Entity.getTransform.setRotation(362, 0, 0, 0) 
Entity.getTransform.setScale(362, 13.5, 1, 25) 
Entity.addMeshRenderer(362) 
Entity.getMeshRenderer.setName(362, 'CUBE') 
Entity.getMeshRenderer.setColor(362, 0.5, 0.5, 1) 
Entity.getMeshRenderer.setShininess(362, 32) 
Entity.getMeshRenderer.setEmissive(362, 0) 
Entity.addSphereCollider(362) 
Entity.getSphereCollider.setRadius(362, 100) 
Entity.getSphereCollider.addTag(362, "MESHCULL")
Entity.addAABBCollider(362, 1) 
Entity.getAABBCollider.setHalfSize(362, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(362, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(362, 1, "wall")
Entity.addMeshCollider(362)
Entity.getMeshCollider.setName(362, "CUBE")


Entity.New(363, 'Level 3 lift 3' ) 
Entity.setActive(363, true) 
Entity.addTag(363, "wall") 
Entity.getTransform.setPosition(363, -42.5, 160, -6) -- 151
Entity.getTransform.setRotation(363, 0, 0, 0) 
Entity.getTransform.setScale(363, 13.5, 1, 15) 
Entity.addMeshRenderer(363) 
Entity.getMeshRenderer.setName(363, 'CUBE') 
Entity.getMeshRenderer.setColor(363, 0.5, 0.5, 1) 
Entity.getMeshRenderer.setShininess(363, 32) 
Entity.getMeshRenderer.setEmissive(363, 0) 
Entity.addSphereCollider(363) 
Entity.getSphereCollider.setRadius(363, 100) 
Entity.getSphereCollider.addTag(363, "MESHCULL")
Entity.addAABBCollider(363, 1) 
Entity.getAABBCollider.setHalfSize(363, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(363, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(363, 1, "wall")
Entity.addMeshCollider(363)
Entity.getMeshCollider.setName(363, "CUBE")

Entity.New(364, 'Level 3 lift 4' ) 
Entity.setActive(364, true) 
Entity.addTag(364, "wall") 
Entity.getTransform.setPosition(364, -42.5, 160, -11) -- 158
Entity.getTransform.setRotation(364, 0, 0, 0) 
Entity.getTransform.setScale(364, 13.5, 1, 8) 
Entity.addMeshRenderer(364) 
Entity.getMeshRenderer.setName(364, 'CUBE') 
Entity.getMeshRenderer.setColor(364, 0.5, 0.5, 1) 
Entity.getMeshRenderer.setShininess(364, 32) 
Entity.getMeshRenderer.setEmissive(364, 0) 
Entity.addSphereCollider(364) 
Entity.getSphereCollider.setRadius(364, 100) 
Entity.getSphereCollider.addTag(364, "MESHCULL")
Entity.addAABBCollider(364, 1) 
Entity.getAABBCollider.setHalfSize(364, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(364, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(364, 1, "wall")
Entity.addMeshCollider(364)
Entity.getMeshCollider.setName(364, "CUBE")

--]]

Entity.New(38, 'Level 3 button holder' ) 
Entity.setActive(38, true) 
Entity.addTag(38, "button") 
Entity.getTransform.setPosition(38, 35, 130, -15) 
Entity.getTransform.setRotation(38, 0, 0, 0) 
Entity.getTransform.setScale(38, 15, 1.2, 20) 
Entity.addMeshRenderer(38) 
Entity.getMeshRenderer.setName(38, 'CUBE') 
Entity.getMeshRenderer.setColor(38, 0.5, 1, 0.5) 
Entity.getMeshRenderer.setShininess(38, 32) 
Entity.getMeshRenderer.setEmissive(38, 0) 
Entity.addSphereCollider(38) 
Entity.getSphereCollider.setRadius(38, 100) 
Entity.getSphereCollider.addTag(38, "MESHCULL")
Entity.addAABBCollider(38, 1) 
Entity.getAABBCollider.setHalfSize(38, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(38, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(38, 1, "button")
Entity.addMeshCollider(38)
Entity.getMeshCollider.setName(38, "CUBE")
Entity.addTrigger(38)
Entity.addScript(38) 
Entity.getScript.setPath(38, 'Content//scripts//L4_buttonholder.lua')

Entity.New(381, 'Level 3 button holder 2' ) 
Entity.setActive(381, true) 
Entity.addTag(381, "button") 
Entity.getTransform.setPosition(381, -10, 130, -25)
Entity.getTransform.setScale(381, 1, 1, 1) 
Entity.addTrigger(381)
Entity.addScript(381) 
Entity.getScript.setPath(381, 'Content//scripts//L4_buttonmove.lua')



Entity.New(371, 'Level 3 button 1' ) 
Entity.setActive(371, true) 
Entity.addTag(371, "button") 
Entity.getTransform.setPosition(371, 10, 131.2, 30) 
Entity.getTransform.setRotation(371, 0, 0, 0) 
Entity.getTransform.setScale(371, 7, 1, 7) 
Entity.addMeshRenderer(371) 
Entity.getMeshRenderer.setName(371, 'CUBE') 
Entity.getMeshRenderer.setColor(371, 1, 0, 0) 
Entity.getMeshRenderer.setShininess(371, 32) 
Entity.getMeshRenderer.setEmissive(371, 0) 
Entity.addSphereCollider(371) 
Entity.getSphereCollider.setRadius(371, 100) 
Entity.getSphereCollider.addTag(371, "MESHCULL")
Entity.addAABBCollider(371, 1) 
Entity.getAABBCollider.setHalfSize(371, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(371, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(371, 1, "button")
Entity.addMeshCollider(371)
Entity.getMeshCollider.setName(371, "CUBE")
Entity.addScript(371) 
Entity.getScript.setPath(371, 'Content//scripts//L4_F2B1.lua')
Entity.TriggerLock(371, 38)

Entity.New(372, 'Level 3 button 2' ) 
Entity.setActive(372, true) 
Entity.addTag(372, "button") 
Entity.addParent(372, 38)
Entity.getTransform.setPosition(372, 0, 0.86, 0) 
Entity.getTransform.setRotation(372, 0, 0, 0) 
Entity.getTransform.setScale(372, 7, 0.5, 7) 
Entity.addMeshRenderer(372) 
Entity.getMeshRenderer.setName(372, 'CUBE') 
Entity.getMeshRenderer.setColor(372, 1, 0, 0) 
Entity.getMeshRenderer.setShininess(372, 32) 
Entity.getMeshRenderer.setEmissive(372, 0) 
Entity.addSphereCollider(372) 
Entity.getSphereCollider.setRadius(372, 100) 
Entity.getSphereCollider.addTag(372, "MESHCULL")
Entity.addAABBCollider(372, 1) 
Entity.getAABBCollider.setHalfSize(372, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(372, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(372, 1, "button")
Entity.addMeshCollider(372)
Entity.getMeshCollider.setName(372, "CUBE")
Entity.addScript(372) 
Entity.getScript.setPath(372, 'Content//scripts//L4_F2B2.lua')
Entity.TriggerLock(372, 381)

Entity.New(373, 'Level 3 button 3' ) 
Entity.setActive(373, true) 
Entity.addTag(373, "button") 
Entity.addParent(373, 381)
Entity.getTransform.setPosition(373, 0, 0, 0) 
Entity.getTransform.setRotation(373, 0, 0, 0) 
Entity.getTransform.setScale(373, 7, 1, 7) 
Entity.addMeshRenderer(373) 
Entity.getMeshRenderer.setName(373, 'CUBE') 
Entity.getMeshRenderer.setColor(373, 1, 0, 1) 
Entity.getMeshRenderer.setShininess(373, 32) 
Entity.getMeshRenderer.setEmissive(373, 0) 
Entity.addSphereCollider(373) 
Entity.getSphereCollider.setRadius(373, 100) 
Entity.getSphereCollider.addTag(373, "MESHCULL")
Entity.addAABBCollider(373, 1) 
Entity.getAABBCollider.setHalfSize(373, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(373, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(373, 1, "button")
Entity.addMeshCollider(373)
Entity.getMeshCollider.setName(373, "CUBE")
Entity.addScript(373) 
Entity.getScript.setPath(373, 'Content//scripts//L4_F2B3.lua')
Entity.TriggerLock(373, 4)

-----------------------------------------------

--[[ Level 4 ]--

Entity.New(41, 'Level 4 - 1' ) 
Entity.setActive(41, true) 
Entity.addTag(41, "wall") 
Entity.getTransform.setPosition(41, 30, 190, 0) 
Entity.getTransform.setRotation(41, 0, 0, 0) 
Entity.getTransform.setScale(41, 40, 2, 100.5) 
Entity.addMeshRenderer(41) 
Entity.getMeshRenderer.setName(41, 'CUBE') 
Entity.getMeshRenderer.setColor(41, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(41, 32) 
Entity.getMeshRenderer.setEmissive(41, 0) 
Entity.addSphereCollider(41) 
Entity.getSphereCollider.setRadius(41, 50) 
Entity.getSphereCollider.addTag(41, "MESHCULL")
Entity.addAABBCollider(41, 1) 
Entity.getAABBCollider.setHalfSize(41, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(41, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(41, 1, "wall")
Entity.addMeshCollider(41)
Entity.getMeshCollider.setName(41, "CUBE")

Entity.New(42, 'Level 4 - 2' ) 
Entity.setActive(42, true) 
Entity.addTag(42, "wall") 
Entity.getTransform.setPosition(42, -20, 190, -33) 
Entity.getTransform.setRotation(42, 0, 0, 0) 
Entity.getTransform.setScale(42, 60, 2, 35) 
Entity.addMeshRenderer(42) 
Entity.getMeshRenderer.setName(42, 'CUBE') 
Entity.getMeshRenderer.setColor(42, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(42, 32) 
Entity.getMeshRenderer.setEmissive(42, 0) 
Entity.addSphereCollider(42) 
Entity.getSphereCollider.setRadius(42, 50) 
Entity.getSphereCollider.addTag(42, "MESHCULL")
Entity.addAABBCollider(42, 1) 
Entity.getAABBCollider.setHalfSize(42, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(42, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(42, 1, "wall")
Entity.addMeshCollider(42)
Entity.getMeshCollider.setName(42, "CUBE")


Entity.New(43, 'Level 4 - 3' ) 
Entity.setActive(43, true) 
Entity.addTag(43, "wall") 
Entity.getTransform.setPosition(43, -20, 190, 33) 
Entity.getTransform.setRotation(43, 0, 0, 0) 
Entity.getTransform.setScale(43, 60, 2, 35) 
Entity.addMeshRenderer(43) 
Entity.getMeshRenderer.setName(43, 'CUBE') 
Entity.getMeshRenderer.setColor(43, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(43, 32) 
Entity.getMeshRenderer.setEmissive(43, 0) 
Entity.addSphereCollider(43) 
Entity.getSphereCollider.setRadius(43, 50) 
Entity.getSphereCollider.addTag(43, "MESHCULL")
Entity.addAABBCollider(43, 1) 
Entity.getAABBCollider.setHalfSize(43, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(43, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(43, 1, "wall")
Entity.addMeshCollider(43)
Entity.getMeshCollider.setName(43, "CUBE")

Entity.New(44, 'Level 4 - 4' ) 
Entity.setActive(44, true) 
Entity.addTag(44, "wall") 
Entity.getTransform.setPosition(44, -24, 190, 0) 
Entity.getTransform.setRotation(44, 0, 0, 0) 
Entity.getTransform.setScale(44, 24, 2, 32) 
Entity.addMeshRenderer(44) 
Entity.getMeshRenderer.setName(44, 'CUBE') 
Entity.getMeshRenderer.setColor(44, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(44, 32) 
Entity.getMeshRenderer.setEmissive(44, 0) 
Entity.addSphereCollider(44) 
Entity.getSphereCollider.setRadius(44, 50) 
Entity.getSphereCollider.addTag(44, "MESHCULL")
Entity.addAABBCollider(44, 1) 
Entity.getAABBCollider.setHalfSize(44, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(44, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(44, 1, "wall")
Entity.addMeshCollider(44)
Entity.getMeshCollider.setName(44, "CUBE")

Entity.New(45, 'Level 4 platform' ) 
Entity.setActive(45, true) 
Entity.addTag(45, "wall") 
Entity.getTransform.setPosition(45, 0, 190, 0) 
Entity.getTransform.setRotation(45, 0, 0, 0) 
Entity.getTransform.setScale(45, 25, 1, 35) 
Entity.addMeshRenderer(45) 
Entity.getMeshRenderer.setName(45, 'CUBE') 
Entity.getMeshRenderer.setColor(45, 0.5, 1, 0.5) 
Entity.getMeshRenderer.setShininess(45, 32) 
Entity.getMeshRenderer.setEmissive(45, 0) 
Entity.addSphereCollider(45) 
Entity.getSphereCollider.setRadius(45, 100) 
Entity.getSphereCollider.addTag(45, "MESHCULL")
Entity.addAABBCollider(45, 1) 
Entity.getAABBCollider.setHalfSize(45, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(45, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(45, 1, "wall")
Entity.addMeshCollider(45)
Entity.getMeshCollider.setName(45, "CUBE")


Entity.New(46, 'Level 4 ramp' ) 
Entity.setActive(46, true) 
Entity.addTag(46, "wall") 
Entity.getTransform.setPosition(46, -42.5, 160, 0) 
Entity.getTransform.setRotation(46, 0, 0, 0) 
Entity.getTransform.setScale(46, 13.5, 1, 33) 
Entity.addMeshRenderer(46) 
Entity.getMeshRenderer.setName(46, 'CUBE') 
Entity.getMeshRenderer.setColor(46, 0.5, 0.5, 1) 
Entity.getMeshRenderer.setShininess(46, 32) 
Entity.getMeshRenderer.setEmissive(46, 0) 
Entity.addSphereCollider(46) 
Entity.getSphereCollider.setRadius(46, 100) 
Entity.getSphereCollider.addTag(46, "MESHCULL")
Entity.addAABBCollider(46, 1) 
Entity.getAABBCollider.setHalfSize(46, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(46, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(46, 1, "wall")
Entity.addMeshCollider(46)
Entity.getMeshCollider.setName(46, "CUBE")
--]]
-----------------------------------------------


--AddDinoEntity(517, 20, 20, 20)

-- Important entities
Entity.New(1 , 'dirlight' ) 
Entity.setActive(1 , true) 
Entity.addTag(1 , "dirlight") 
Entity.getTransform.setPosition(1, 33.8344, 406.25, 120.335) 
Entity.getTransform.setRotation(1, 0, 0, 0) 
Entity.getTransform.setScale(1, 1, 1, 1) 
Entity.addDirLight(1) 
Entity.getDirLight.setAmbient(1, 0.07, 0.07, 0.07) 
Entity.getDirLight.setDiffuse(1, 0.2, 0.2, 0.2) 
Entity.getDirLight.setSpecular(1, 0.1, 0.1, 0.1) 
Entity.getDirLight.setLightColor(1, 0.8, 0.6, 0.5) 
Entity.getDirLight.setLightDirection(1, -0.5, -0.7, 0) 

Entity.New(2 , 'player' ) 
Entity.setActive(2 , true) 
Entity.addTag(2 , "player") 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//CameraLookAtPlayerMovement.lua')



Entity.New(3 , 'gerald scene' ) 
Entity.setActive(3 , true) 
Entity.addScript(3) 
Entity.getScript.setPath(3, 'Content//scripts//sceneCheck.lua') 
Entity.addScript(3) 
Entity.getScript.setPath(3, 'Content//scripts//level4KeepTrack.lua') 

AddFinalEndPointEntity(
400, 
0, 10, 0, -- position
-90, 0, 0, -- rotation
50, 50, 50 -- scale
)

Camera.setPosition(-6.83085, 5.7, 2.723) 
Camera.setTarget(-6.83085, -0.8, 17.523) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(0) -- FPS
Camera.setMouseControl(true)
Camera.setLookingDir(0, -1, 0.8) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(16.5) 
Camera.setPitchLimit(80) 

Entity.New(200 , 'Cont' ) 
Entity.setActive(200 , true) 
Entity.addTag(200 , "font") 
Entity.getTransform.setPosition(200, 0.015, -0.025, 0) 
Entity.getTransform.setScale(200, 1.25, 1, 1) 
Entity.addGUIText(200)
Entity.getGUIText.setTextString(200, "0000000")
Entity.getGUIText.setTextColor(200, 1, 1, 1, 0)
Entity.getGUIText.setFontType(200, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(200, 
  0.5, -- width
  0.005, -- edge
  0.7, -- borderwidth
  0.3, -- borderedge
  -0.001, -- oy
  0.001, -- ox
  0.1, 0.1, 0.1) -- outlinecolor
Entity.addScript(200) 
Entity.getScript.setPath(200, 'Content//scripts//guiPoint.lua') 

