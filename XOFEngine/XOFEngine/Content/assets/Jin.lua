require("Content//assets//endpointassets")
require("Content//assets//dinoassets")
require("Content//assets//cloudassets")

--Coins
for i = 1, 10, 1 do 
	Entity.addCollectable(0,  0,  (6 * i) + 20)
end

for i = 1, 10, 1 do 
	Entity.addCollectable(0,  0,  (6 * i) - 85)
end

for i = 1, 5, 1 do 
	Entity.addCollectable((6 * i) + 25,  0, 0)
end

for i = 1, 6, 1 do 
	Entity.addCollectable((6 * i) + 180,  0, 0)
end

for i = 1, 12, 1 do 
	Entity.addCollectable(35,  0,  (6 * i) - 160)
end

for i = 1, 12, 1 do 
	Entity.addCollectable(-35,  0,  (6 * i) - 160)
end

for i = 1, 5, 1 do 
	Entity.addCollectable(130,  0,  (6 * i) - 18)
end

--Coins put for the steps 
Entity.addCollectable(-14,  9,  110)
Entity.addCollectable(-14,  14,  115)
Entity.addCollectable(-14,  19,  120)

-- Platforms
Entity.New(4 , 'main platform' ) 
Entity.setActive(4 , true) 
Entity.addTag(4 , "wall") 
Entity.getTransform.setPosition(4, 0, -1.9, 0) 
Entity.getTransform.setRotation(4, 0, 0, 0) 
Entity.getTransform.setScale(4, 50, 1, 50) 
Entity.addMeshRenderer(4) 
Entity.getMeshRenderer.setName(4, 'CUBE') 
Entity.getMeshRenderer.setColor(4, 0.8, 0.8, 0.8) 
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

Entity.New(5 , 'left road' ) 
Entity.setActive(5 , true) 
Entity.addTag(5 , "wall") 
Entity.getTransform.setPosition(5, 0, -1.9, -50) 
Entity.getTransform.setRotation(5, 0, 0, 0) 
Entity.getTransform.setScale(5, 10, 1, 100) 
Entity.addMeshRenderer(5) 
Entity.getMeshRenderer.setName(5, 'CUBE') 
Entity.getMeshRenderer.setColor(5, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(5, 32) 
Entity.getMeshRenderer.setEmissive(5, 0) 
Entity.addSphereCollider(5) 
Entity.getSphereCollider.setRadius(5, 50) 
Entity.getSphereCollider.addTag(5, "MESHCULL")
Entity.addAABBCollider(5, 1) 
Entity.getAABBCollider.setHalfSize(5, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(5, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(5, 1, "wall")
Entity.addMeshCollider(5)
Entity.getMeshCollider.setName(5, "CUBE") 

Entity.New(6 , 'left platform' ) 
Entity.setActive(6 , true) 
Entity.addTag(6 , "wall") 
Entity.getTransform.setPosition(6, 0, -1.9, -120) 
Entity.getTransform.setRotation(6, 0, 0, 0) 
Entity.getTransform.setScale(6, 80, 1, 80) 
Entity.addMeshRenderer(6) 
Entity.getMeshRenderer.setName(6, 'CUBE') 
Entity.getMeshRenderer.setColor(6, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(6, 32) 
Entity.getMeshRenderer.setEmissive(6, 0) 
Entity.addSphereCollider(6) 
Entity.getSphereCollider.setRadius(6, 50) 
Entity.getSphereCollider.addTag(6, "MESHCULL")
Entity.addAABBCollider(6, 1) 
Entity.getAABBCollider.setHalfSize(6, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(6, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(6, 1, "wall")
Entity.addMeshCollider(6)
Entity.getMeshCollider.setName(6, "CUBE") 

Entity.New(7 , 'right road' ) 
Entity.setActive(7 , true) 
Entity.addTag(7 , "wall") 
Entity.getTransform.setPosition(7, 0, -1.9, 50) 
Entity.getTransform.setRotation(7, 0, 0, 0) 
Entity.getTransform.setScale(7, 10, 1, 100) 
Entity.addMeshRenderer(7) 
Entity.getMeshRenderer.setName(7, 'CUBE') 
Entity.getMeshRenderer.setColor(7, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(7, 32) 
Entity.getMeshRenderer.setEmissive(7, 0) 
Entity.addSphereCollider(7) 
Entity.getSphereCollider.setRadius(7, 70) 
Entity.getSphereCollider.addTag(7, "MESHCULL")
Entity.addAABBCollider(7, 1) 
Entity.getAABBCollider.setHalfSize(7, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(7, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(7, 1, "wall")
Entity.addMeshCollider(7)
Entity.getMeshCollider.setName(7, "CUBE") 

Entity.New(8 , 'right platform' ) 
Entity.setActive(8 , true) 
Entity.addTag(8 , "wall") 
Entity.getTransform.setPosition(8, 0, -1.9, 120) 
Entity.getTransform.setRotation(8, 0, 0, 0) 
Entity.getTransform.setScale(8, 80, 1, 80) 
Entity.addMeshRenderer(8) 
Entity.getMeshRenderer.setName(8, 'CUBE') 
Entity.getMeshRenderer.setColor(8, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(8, 32) 
Entity.getMeshRenderer.setEmissive(8, 0) 
Entity.addSphereCollider(8) 
Entity.getSphereCollider.setRadius(8, 50) 
Entity.getSphereCollider.addTag(8, "MESHCULL")
Entity.addAABBCollider(8, 1) 
Entity.getAABBCollider.setHalfSize(8, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(8, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(8, 1, "wall")
Entity.addMeshCollider(8)
Entity.getMeshCollider.setName(8, "CUBE") 

Entity.New(9 , 'small platform w Enemy' ) 
Entity.setActive(9 , true) 
Entity.addTag(9 , "wall") 
Entity.getTransform.setPosition(9, 120, -1.9, 0) 
Entity.getTransform.setRotation(9, 0, 0, 0) 
Entity.getTransform.setScale(9, 120, 1, 80) 
Entity.addMeshRenderer(9) 
Entity.getMeshRenderer.setName(9, 'CUBE') 
Entity.getMeshRenderer.setColor(9, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(9, 32) 
Entity.getMeshRenderer.setEmissive(9, 0) 
Entity.addSphereCollider(9) 
Entity.getSphereCollider.setRadius(9, 50) 
Entity.getSphereCollider.addTag(9, "MESHCULL")
Entity.addAABBCollider(9, 1) 
Entity.getAABBCollider.setHalfSize(9, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(9, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(9, 1, "wall")
Entity.addMeshCollider(9)
Entity.getMeshCollider.setName(9, "CUBE")

Entity.New(11 , 'Entrance Door' ) 
Entity.setActive(11 , true) 
Entity.addTag(11 , "Door") 
Entity.getTransform.setPosition(11, 26, 14, 0) 
Entity.getTransform.setRotation(11, 0, 0, 0) 
Entity.getTransform.setScale(11, 1, 33, 50) 
Entity.addMeshRenderer(11) 
Entity.getMeshRenderer.setName(11, 'CUBE') 
Entity.getMeshRenderer.setColor(11, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(11, 32) 
Entity.getMeshRenderer.setEmissive(11, 0) 
Entity.addSphereCollider(11) 
Entity.getSphereCollider.setRadius(11, 50) 
Entity.getSphereCollider.addTag(11, "MESHCULL")
Entity.addMeshCollider(11)
Entity.getMeshCollider.setName(11, "CUBE")
Entity.addTrigger(11)
Entity.addScript(11) 
Entity.getScript.setPath(11, 'Content//scripts//EntranceDoorDownUp.lua')

Entity.New(203 , 'eDoorButton1' ) 
Entity.setActive(203 , true) 
Entity.addTag(203 , "button") 
Entity.getTransform.setPosition(203, 30, 0, -90) 
Entity.getTransform.setRotation(203, 0, 0, 0) 
Entity.getTransform.setScale(203, 5, 2.5, 5) 
Entity.addMeshRenderer(203) 
Entity.getMeshRenderer.setName(203, 'CUBE') 
Entity.getMeshRenderer.setColor(203, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(203, 32) 
Entity.getMeshRenderer.setEmissive(203, 0) 
Entity.addSphereCollider(203) 
Entity.getSphereCollider.setRadius(203, 5) 
Entity.getSphereCollider.addTag(203, "MESHCULL")
Entity.addAABBCollider(203, 1) 
Entity.getAABBCollider.setHalfSize(203, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(203, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(203, 1, "cloud")
Entity.addMeshCollider(203)
Entity.getMeshCollider.setName(203, "CUBE")
Entity.addScript(203) 
Entity.getScript.setPath(203, 'Content//scripts//L3FirstDoorButton.lua')
Entity.TriggerLock(203, 11)

Entity.New(204 , 'eDoorButton2' ) 
Entity.setActive(204 , true) 
Entity.addTag(204 , "button") 
Entity.getTransform.setPosition(204, -30, 0, -150) 
Entity.getTransform.setRotation(204, 0, 0, 0) 
Entity.getTransform.setScale(204, 5, 2.5, 5) 
Entity.addMeshRenderer(204) 
Entity.getMeshRenderer.setName(204, 'CUBE') 
Entity.getMeshRenderer.setColor(204, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(204, 32) 
Entity.getMeshRenderer.setEmissive(204, 0) 
Entity.addSphereCollider(204) 
Entity.getSphereCollider.setRadius(204, 5) 
Entity.getSphereCollider.addTag(204, "MESHCULL")
Entity.addAABBCollider(204, 1) 
Entity.getAABBCollider.setHalfSize(204, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(204, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(204, 1, "cloud")
Entity.addMeshCollider(204)
Entity.getMeshCollider.setName(204, "CUBE")
Entity.addScript(204) 
Entity.getScript.setPath(204, 'Content//scripts//L3SecondDoorButton.lua')
Entity.TriggerLock(204, 11)

Entity.New(12 , 'straight road' ) 
Entity.setActive(12 , true) 
Entity.addTag(12 , "wall") 
Entity.getTransform.setPosition(12, 50, -1.9, 0) 
Entity.getTransform.setRotation(12, 0, 0, 0) 
Entity.getTransform.setScale(12, 100, 1, 10) 
Entity.addMeshRenderer(12) 
Entity.getMeshRenderer.setName(12, 'CUBE') 
Entity.getMeshRenderer.setColor(12, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(12, 32) 
Entity.getMeshRenderer.setEmissive(12, 0) 
Entity.addSphereCollider(12) 
Entity.getSphereCollider.setRadius(12, 120) 
Entity.getSphereCollider.addTag(12, "MESHCULL")
Entity.addAABBCollider(12, 1) 
Entity.getAABBCollider.setHalfSize(12, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(12, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(12, 1, "wall")
Entity.addMeshCollider(12)
Entity.getMeshCollider.setName(12, "CUBE") 

Entity.New(14 , 'firstwallblock' ) 
Entity.setActive(14 , true) 
Entity.addTag(14 , "wall") 
Entity.getTransform.setPosition(14, -14, -0.5, 121) 
Entity.getTransform.setRotation(14, 0, -1, 0) 
Entity.getTransform.setScale(14, 10, 6, 1) 
Entity.addMeshRenderer(14) 
Entity.getMeshRenderer.setName(14, 'CUBE') 
Entity.getMeshRenderer.setColor(14, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(14, 32) 
Entity.getMeshRenderer.setEmissive(14, 0) 
Entity.addSphereCollider(14) 
Entity.getSphereCollider.setRadius(14, 140) 
Entity.getSphereCollider.addTag(14, "MESHCULL")
Entity.addAABBCollider(14, 1) 
Entity.getAABBCollider.setHalfSize(14, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(14, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(14, 1, "wall")
Entity.addMeshCollider(14)
Entity.getMeshCollider.setName(14, "CUBE") 

Entity.New(15 , 'secondwallblock' ) 
Entity.setActive(15 , true) 
Entity.addTag(15 , "wall") 
Entity.getTransform.setPosition(15, -14, 3, 126.5) 
Entity.getTransform.setRotation(15, 0, 0, 0) 
Entity.getTransform.setScale(15, 10, 15, 1) 
Entity.addMeshRenderer(15) 
Entity.getMeshRenderer.setName(15, 'CUBE') 
Entity.getMeshRenderer.setColor(15, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(15, 32) 
Entity.getMeshRenderer.setEmissive(15, 0) 
Entity.addSphereCollider(15) 
Entity.getSphereCollider.setRadius(15, 150) 
Entity.getSphereCollider.addTag(15, "MESHCULL")
Entity.addAABBCollider(15, 1) 
Entity.getAABBCollider.setHalfSize(15, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(15, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(15, 1, "wall")
Entity.addMeshCollider(15)
Entity.getMeshCollider.setName(15, "CUBE") 

Entity.New(16 , 'straight straight road' ) 
Entity.setActive(16 , true) 
Entity.addTag(16 , "wall") 
Entity.getTransform.setPosition(16, 190, -1.9, 0) 
Entity.getTransform.setRotation(16, 0, 0, 0) 
Entity.getTransform.setScale(16, 60, 1, 10) 
Entity.addMeshRenderer(16) 
Entity.getMeshRenderer.setName(16, 'CUBE') 
Entity.getMeshRenderer.setColor(16, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(16, 32) 
Entity.getMeshRenderer.setEmissive(16, 0) 
Entity.addSphereCollider(16) 
Entity.getSphereCollider.setRadius(16, 160) 
Entity.getSphereCollider.addTag(16, "MESHCULL")
Entity.addAABBCollider(16, 1) 
Entity.getAABBCollider.setHalfSize(16, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(16, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(16, 1, "wall")
Entity.addMeshCollider(16)
Entity.getMeshCollider.setName(16, "CUBE") 

Entity.New(17 , 'rightCoverWallNear' ) 
Entity.setActive(17 , true) 
Entity.addTag(17 , "wall") 
Entity.getTransform.setPosition(17, 0, -12, 81) 
Entity.getTransform.setRotation(17, 0, 0, 0) 
Entity.getTransform.setScale(17, 80, 20, 1) 
Entity.addMeshRenderer(17) 
Entity.getMeshRenderer.setName(17, 'CUBE') 
Entity.getMeshRenderer.setColor(17, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(17, 32) 
Entity.getMeshRenderer.setEmissive(17, 0) 
Entity.addSphereCollider(17) 
Entity.getSphereCollider.setRadius(17, 170) 
Entity.getSphereCollider.addTag(17, "MESHCULL")
Entity.addAABBCollider(17, 1) 
Entity.getAABBCollider.setHalfSize(17, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(17, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(17, 1, "wall")
Entity.addMeshCollider(17)
Entity.getMeshCollider.setName(17, "CUBE") 

Entity.New(18 , 'rightCoverWallFar' ) 
Entity.setActive(18 , true) 
Entity.addTag(18 , "wall") 
Entity.getTransform.setPosition(18, 0, -12, 160) 
Entity.getTransform.setRotation(18, 0, 0, 0) 
Entity.getTransform.setScale(18, 80, 20, 1) 
Entity.addMeshRenderer(18) 
Entity.getMeshRenderer.setName(18, 'CUBE') 
Entity.getMeshRenderer.setColor(18, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(18, 32) 
Entity.getMeshRenderer.setEmissive(18, 0) 
Entity.addSphereCollider(18) 
Entity.getSphereCollider.setRadius(18, 180) 
Entity.getSphereCollider.addTag(18, "MESHCULL")
Entity.addAABBCollider(18, 1) 
Entity.getAABBCollider.setHalfSize(18, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(18, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(18, 1, "wall")
Entity.addMeshCollider(18)
Entity.getMeshCollider.setName(18, "CUBE") 

Entity.New(19 , 'rightCoverWallLeft' ) 
Entity.setActive(19 , true) 
Entity.addTag(19 , "wall") 
Entity.getTransform.setPosition(19, 40, -12, 120) 
Entity.getTransform.setRotation(19, 0, 0, 0) 
Entity.getTransform.setScale(19, 1, 20, 80) 
Entity.addMeshRenderer(19) 
Entity.getMeshRenderer.setName(19, 'CUBE') 
Entity.getMeshRenderer.setColor(19, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(19, 32) 
Entity.getMeshRenderer.setEmissive(19, 0) 
Entity.addSphereCollider(19) 
Entity.getSphereCollider.setRadius(19, 190) 
Entity.getSphereCollider.addTag(19, "MESHCULL")
Entity.addAABBCollider(19, 1) 
Entity.getAABBCollider.setHalfSize(19, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(19, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(19, 1, "wall")
Entity.addMeshCollider(19)
Entity.getMeshCollider.setName(19, "CUBE") 

Entity.New(20 , 'rightCoverWallRight' ) 
Entity.setActive(20 , true) 
Entity.addTag(20 , "wall") 
Entity.getTransform.setPosition(20, -38, -12, 120) 
Entity.getTransform.setRotation(20, 0, 0, 0) 
Entity.getTransform.setScale(20, 1, 20, 80) 
Entity.addMeshRenderer(20) 
Entity.getMeshRenderer.setName(20, 'CUBE') 
Entity.getMeshRenderer.setColor(20, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(20, 32) 
Entity.getMeshRenderer.setEmissive(20, 0) 
Entity.addSphereCollider(20) 
Entity.getSphereCollider.setRadius(20, 200) 
Entity.getSphereCollider.addTag(20, "MESHCULL")
Entity.addAABBCollider(20, 1) 
Entity.getAABBCollider.setHalfSize(20, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(20, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(20, 1, "wall")
Entity.addMeshCollider(20)
Entity.getMeshCollider.setName(20, "CUBE") 

Entity.New(21 , 'puzzle2buttonplatform' ) 
Entity.setActive(21 , true) 
Entity.addTag(21 , "wall") 
Entity.getTransform.setPosition(21, 136.5, 6.8, 0) 
Entity.getTransform.setRotation(21, 0, 0, 0) 
Entity.getTransform.setScale(21, 8, 1, 8) 
Entity.addMeshRenderer(21) 
Entity.getMeshRenderer.setName(21, 'CUBE') 
Entity.getMeshRenderer.setColor(21, 0, 1, 0) 
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

Entity.New(22 , 'Entrance3Front' ) 
Entity.setActive(22 , true) 
Entity.addTag(22 , "button") 
Entity.getTransform.setPosition(22, 165, 2, -25) 
Entity.getTransform.setRotation(22, 0, 0, 0) 
Entity.getTransform.setScale(22, 1, 10, 10) 
Entity.addMeshRenderer(22) 
Entity.getMeshRenderer.setName(22, 'CUBE') 
Entity.getMeshRenderer.setColor(22, 0, 0, 1) 
Entity.getMeshRenderer.setShininess(22, 32) 
Entity.getMeshRenderer.setEmissive(22, 0) 
Entity.addSphereCollider(22) 
Entity.getSphereCollider.setRadius(22, 5) 
Entity.getSphereCollider.addTag(22, "MESHCULL")
Entity.addAABBCollider(22, 1) 
Entity.getAABBCollider.setHalfSize(22, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(22, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(22, 1, "cloud")
Entity.addMeshCollider(22)
Entity.getMeshCollider.setName(22, "CUBE")
Entity.addTrigger(22)
Entity.addScript(22) 
Entity.getScript.setPath(22, 'Content//scripts//DoorDownUp.lua')

Entity.New(23 , 'eDoorButton3' ) 
Entity.setActive(23 , true) 
Entity.addTag(23 , "button") 
Entity.getTransform.setPosition(23, 136, 7.8, 0) 
Entity.getTransform.setRotation(23, 0, 0, 0) 
Entity.getTransform.setScale(23, 5, 1, 5) 
Entity.addMeshRenderer(23) 
Entity.getMeshRenderer.setName(23, 'CUBE') 
Entity.getMeshRenderer.setColor(23, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(23, 32) 
Entity.getMeshRenderer.setEmissive(23, 0) 
Entity.addSphereCollider(23) 
Entity.getSphereCollider.setRadius(23, 5) 
Entity.getSphereCollider.addTag(23, "MESHCULL")
Entity.addAABBCollider(23, 1) 
Entity.getAABBCollider.setHalfSize(23, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(23, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(23, 1, "cloud")
Entity.addMeshCollider(23)
Entity.getMeshCollider.setName(23, "CUBE")
Entity.addScript(23) 
Entity.getScript.setPath(23, 'Content//scripts//L3ThirdDoorButton.lua')
Entity.TriggerLock(23, 22)

Entity.New(24 , 'Entrance3Back' ) 
Entity.setActive(24 , true) 
Entity.addTag(24 , "button") 
Entity.getTransform.setPosition(24, 175, 2, -25) 
Entity.getTransform.setRotation(24, 0, 0, 0) 
Entity.getTransform.setScale(24, 1, 10, 10) 
Entity.addMeshRenderer(24) 
Entity.getMeshRenderer.setName(24, 'CUBE') 
Entity.getMeshRenderer.setColor(24, 0, 0, 1) 
Entity.getMeshRenderer.setShininess(24, 32) 
Entity.getMeshRenderer.setEmissive(24, 0) 
Entity.addSphereCollider(24) 
Entity.getSphereCollider.setRadius(24, 5) 
Entity.getSphereCollider.addTag(24, "MESHCULL")
Entity.addAABBCollider(24, 1) 
Entity.getAABBCollider.setHalfSize(24, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(24, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(24, 1, "cloud")
Entity.addMeshCollider(24)
Entity.getMeshCollider.setName(24, "CUBE")

Entity.New(25 , 'Entrance3RightSide' ) 
Entity.setActive(25 , true) 
Entity.addTag(25 , "button") 
Entity.getTransform.setPosition(25, 170, 2, -20) 
Entity.getTransform.setRotation(25, 0, 0, 0) 
Entity.getTransform.setScale(25, 10, 10, 1) 
Entity.addMeshRenderer(25) 
Entity.getMeshRenderer.setName(25, 'CUBE') 
Entity.getMeshRenderer.setColor(25, 0, 0, 1) 
Entity.getMeshRenderer.setShininess(25, 32) 
Entity.getMeshRenderer.setEmissive(25, 0) 
Entity.addSphereCollider(25) 
Entity.getSphereCollider.setRadius(25, 5) 
Entity.getSphereCollider.addTag(25, "MESHCULL")
Entity.addAABBCollider(25, 1) 
Entity.getAABBCollider.setHalfSize(25, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(25, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(25, 1, "cloud")
Entity.addMeshCollider(25)
Entity.getMeshCollider.setName(25, "CUBE")

Entity.New(26 , 'Entrance3LeftSide' ) 
Entity.setActive(26 , true) 
Entity.addTag(26 , "button") 
Entity.getTransform.setPosition(26, 170, 2, -30) 
Entity.getTransform.setRotation(26, 0, 0, 0) 
Entity.getTransform.setScale(26, 10, 10, 1) 
Entity.addMeshRenderer(26) 
Entity.getMeshRenderer.setName(26, 'CUBE') 
Entity.getMeshRenderer.setColor(26, 0, 0, 1) 
Entity.getMeshRenderer.setShininess(26, 32) 
Entity.getMeshRenderer.setEmissive(26, 0) 
Entity.addSphereCollider(26) 
Entity.getSphereCollider.setRadius(26, 5) 
Entity.getSphereCollider.addTag(26, "MESHCULL")
Entity.addAABBCollider(26, 1) 
Entity.getAABBCollider.setHalfSize(26, 1, -0.1, -0.26, -0.1)
Entity.getAABBCollider.setPosition(26, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(26, 1, "cloud")
Entity.addMeshCollider(26)
Entity.getMeshCollider.setName(26, "CUBE")

Entity.New(27 , 'Entrance3Roof' ) 
Entity.setActive(27 , true) 
Entity.addTag(27 , "button") 
Entity.getTransform.setPosition(27, 170, 7, -25) 
Entity.getTransform.setRotation(27, 0, 0, 0) 
Entity.getTransform.setScale(27, 10, 1, 10) 
Entity.addMeshRenderer(27) 
Entity.getMeshRenderer.setName(27, 'CUBE') 
Entity.getMeshRenderer.setColor(27, 0, 0, 1) 
Entity.getMeshRenderer.setShininess(27, 32) 
Entity.getMeshRenderer.setEmissive(27, 0) 
Entity.addSphereCollider(27) 
Entity.getSphereCollider.setRadius(27, 5) 
Entity.getSphereCollider.addTag(27, "MESHCULL")
Entity.addAABBCollider(27, 1) 
Entity.getAABBCollider.setHalfSize(27, 1, -0.1, -0.27, -0.1)
Entity.getAABBCollider.setPosition(27, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(27, 1, "cloud")
Entity.addMeshCollider(27)
Entity.getMeshCollider.setName(27, "CUBE")


-- Hints

Entity.New(100 , 'Middle Tower' ) 
Entity.setActive(100 , true) 
Entity.addTag(100 , "wall") 
Entity.getTransform.setPosition(100, 0, 3, 120) 
Entity.getTransform.setRotation(100, 0, 0, 0) 
Entity.getTransform.setScale(100, 4, 13, 4) 
Entity.addMeshRenderer(100) 
Entity.getMeshRenderer.setName(100, 'CUBE') 
Entity.getMeshRenderer.setColor(100, 0, 1, 0) 
Entity.getMeshRenderer.setShininess(100, 32) 
Entity.getMeshRenderer.setEmissive(100, 0) 
Entity.addSphereCollider(100) 
Entity.getSphereCollider.setRadius(100, 50) 
Entity.getSphereCollider.addTag(100, "MESHCULL")
Entity.addAABBCollider(100, 1) 
Entity.getAABBCollider.setHalfSize(100, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(100, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(100, 1, "wall")
Entity.addMeshCollider(100)
Entity.getMeshCollider.setName(100, "CUBE") 


Entity.New(202 , 'doorButtonHints' ) 
Entity.setActive(202 , true) 
Entity.addTag(202 , "button") 
Entity.getTransform.setPosition(202, 0, 9, 120) 
--Entity.getTransform.setPosition(202, 0, 0, 100) 
Entity.getTransform.setRotation(202, 0, 0, 0) 
Entity.getTransform.setScale(202, 5, 2.5, 5) 
Entity.addMeshRenderer(202) 
Entity.getMeshRenderer.setName(202, 'CUBE') 
Entity.getMeshRenderer.setColor(202, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(202, 32) 
Entity.getMeshRenderer.setEmissive(202, 0) 
Entity.addSphereCollider(202) 
Entity.getSphereCollider.setRadius(202, 5) 
Entity.getSphereCollider.addTag(202, "MESHCULL")
Entity.addAABBCollider(202, 1) 
Entity.getAABBCollider.setHalfSize(202, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(202, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(202, 1, "door")
Entity.addMeshCollider(202)
Entity.getMeshCollider.setName(202, "CUBE")
Entity.addScript(202) 
Entity.getScript.setPath(202, 'Content//scripts//DoorHintsButton.lua')
Entity.addTrigger(202)

Entity.New(13 , 'LeftEntrance Door' ) 
Entity.setActive(13 , true) 
Entity.addTag(13 , "Door") 
Entity.getTransform.setPosition(13, 0, 14, -80) 
Entity.getTransform.setRotation(13, 0, 0, 0) 
Entity.getTransform.setScale(13, 80, 33, 1) 
Entity.addMeshRenderer(13) 
Entity.getMeshRenderer.setName(13, 'CUBE') 
Entity.getMeshRenderer.setColor(13, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(13, 32) 
Entity.getMeshRenderer.setEmissive(13, 0) 
Entity.addSphereCollider(13) 
Entity.getSphereCollider.setRadius(13, 50) 
Entity.getSphereCollider.addTag(13, "MESHCULL")
Entity.addMeshCollider(13)
Entity.getMeshCollider.setName(13, "CUBE")
Entity.addScript(13) 
Entity.getScript.setPath(13, 'Content//scripts//DoorDownUp.lua')
Entity.TriggerLock(13, 202)

Entity.New(101 , 'UpperLeft Hint' ) 
Entity.setActive(101 , true) 
Entity.addTag(101 , "wall") 
Entity.getTransform.setPosition(101, 30, -8, 90) 
Entity.getTransform.setRotation(101, 0, 0, 0) 
Entity.getTransform.setScale(101, 4, 4, 4) 
Entity.addMeshRenderer(101) 
Entity.getMeshRenderer.setName(101, 'CUBE') 
Entity.getMeshRenderer.setColor(101, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(101, 32) 
Entity.getMeshRenderer.setEmissive(101, 0) 
Entity.addSphereCollider(101) 
Entity.getSphereCollider.setRadius(101, 50) 
Entity.getSphereCollider.addTag(101, "MESHCULL")
Entity.addAABBCollider(101, 1) 
Entity.getAABBCollider.setHalfSize(101, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(101, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(101, 1, "wall")
Entity.addMeshCollider(101)
Entity.getMeshCollider.setName(101, "CUBE") 
Entity.addScript(101) 
Entity.getScript.setPath(101, 'Content//scripts//RisingHints.lua')
Entity.TriggerLock(101, 202)


Entity.New(102 , 'UpperRight Hint' ) 
Entity.setActive(102 , true) 
Entity.addTag(102 , "wall") 
Entity.getTransform.setPosition(102, 30, -8, 150) 
Entity.getTransform.setRotation(102, 0, 0, 0) 
Entity.getTransform.setScale(102, 4, 4, 4) 
Entity.addMeshRenderer(102) 
Entity.getMeshRenderer.setName(102, 'CUBE') 
Entity.getMeshRenderer.setColor(102, 0, 1, 0) 
Entity.getMeshRenderer.setShininess(102, 32) 
Entity.getMeshRenderer.setEmissive(102, 0) 
Entity.addSphereCollider(102) 
Entity.getSphereCollider.setRadius(102, 50) 
Entity.getSphereCollider.addTag(102, "MESHCULL")
Entity.addAABBCollider(102, 1) 
Entity.getAABBCollider.setHalfSize(102, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(102, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(102, 1, "wall")
Entity.addMeshCollider(102)
Entity.getMeshCollider.setName(102, "CUBE") 
Entity.addScript(102) 
Entity.getScript.setPath(102, 'Content//scripts//RisingHints.lua')
Entity.TriggerLock(102, 202)

Entity.New(103 , 'Bottom Left Hint' ) 
Entity.setActive(103 , true) 
Entity.addTag(103 , "wall") 
Entity.getTransform.setPosition(103, -30, -8, 90) 
Entity.getTransform.setRotation(103, 0, 0, 0) 
Entity.getTransform.setScale(103, 4, 4, 4) 
Entity.addMeshRenderer(103) 
Entity.getMeshRenderer.setName(103, 'CUBE') 
Entity.getMeshRenderer.setColor(103, 0, 1, 0) 
Entity.getMeshRenderer.setShininess(103, 32) 
Entity.getMeshRenderer.setEmissive(103, 0) 
Entity.addSphereCollider(103) 
Entity.getSphereCollider.setRadius(103, 50) 
Entity.getSphereCollider.addTag(103, "MESHCULL")
Entity.addAABBCollider(103, 1) 
Entity.getAABBCollider.setHalfSize(103, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(103, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(103, 1, "wall")
Entity.addMeshCollider(103)
Entity.getMeshCollider.setName(103, "CUBE")
Entity.addScript(103) 
Entity.getScript.setPath(103, 'Content//scripts//RisingHints.lua')
Entity.TriggerLock(103, 202)

Entity.New(104 , 'Bottom Right Hint' ) 
Entity.setActive(104 , true) 
Entity.addTag(104 , "wall") 
Entity.getTransform.setPosition(104, -30, -8, 150) 
Entity.getTransform.setRotation(104, 0, 0,0) 
Entity.getTransform.setScale(104, 4, 4, 4) 
Entity.addMeshRenderer(104) 
Entity.getMeshRenderer.setName(104, 'CUBE') 
Entity.getMeshRenderer.setColor(104, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(104, 32) 
Entity.getMeshRenderer.setEmissive(104, 0) 
Entity.addSphereCollider(104) 
Entity.getSphereCollider.setRadius(104, 50) 
Entity.getSphereCollider.addTag(104, "MESHCULL")
Entity.addAABBCollider(104, 1) 
Entity.getAABBCollider.setHalfSize(104, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(104, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(104, 1, "wall")
Entity.addMeshCollider(104)
Entity.getMeshCollider.setName(104, "CUBE")
Entity.addScript(104) 
Entity.getScript.setPath(104, 'Content//scripts//RisingHints.lua')
Entity.TriggerLock(104, 202)

Entity.New(105 , 'Middle Button Platform' ) 
Entity.setActive(105 , true) 
Entity.addTag(105 , "wall") 
Entity.getTransform.setPosition(105, 0, 8, 120) 
Entity.getTransform.setRotation(105, 0, 0, 0) 
Entity.getTransform.setScale(105, 8, 1, 8) 
Entity.addMeshRenderer(105) 
Entity.getMeshRenderer.setName(105, 'CUBE') 
Entity.getMeshRenderer.setColor(105, 0, 0, 0.5) 
Entity.getMeshRenderer.setShininess(105, 32) 
Entity.getMeshRenderer.setEmissive(105, 0) 
Entity.addSphereCollider(105) 
Entity.getSphereCollider.setRadius(105, 50) 
Entity.getSphereCollider.addTag(105, "MESHCULL")
Entity.addAABBCollider(105, 1) 
Entity.getAABBCollider.setHalfSize(105, 1, 0, 0, 0)
Entity.getAABBCollider.setPosition(105, 1, 0, 0, 0)
Entity.getAABBCollider.addTag(105, 1, "wall")
Entity.addMeshCollider(105)
Entity.getMeshCollider.setName(105, "CUBE") 

-- Clouds for puzzle part 1
AddCloudEntity(900, 
-14, 15, 120,
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(901, 
-14, 10, 115,
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(902, 
-14, 5, 110,
10, 2.0, 10,
0.4, 1.0, 1.9)

-- Clouds for puzzle part 2
AddCloudEntity(903, 
120, 6, 0,
10, 2.5, 10,
0.4, 1.0, 1.9)


-- Buttons
Entity.New(200 , 'dummy button1' ) 
Entity.setActive(200 , true) 
Entity.addTag(200 , "button") 
Entity.getTransform.setPosition(200, 30, 0, -150) 
Entity.getTransform.setRotation(200, 0, 0, 0) 
Entity.getTransform.setScale(200, 5, 2.5, 5) 
Entity.addMeshRenderer(200) 
Entity.getMeshRenderer.setName(200, 'CUBE') 
Entity.getMeshRenderer.setColor(200, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(200, 32) 
Entity.getMeshRenderer.setEmissive(200, 0) 
Entity.addSphereCollider(200) 
Entity.getSphereCollider.setRadius(200, 5) 
Entity.getSphereCollider.addTag(200, "MESHCULL")
Entity.addAABBCollider(200, 1) 
Entity.getAABBCollider.setHalfSize(200, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(200, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(200, 1, "cloud")
Entity.addMeshCollider(200)
Entity.getMeshCollider.setName(200, "CUBE")
Entity.addScript(200) 
Entity.getScript.setPath(200, 'Content//scripts//DummyButton.lua')

Entity.New(201 , 'dummy button2' ) 
Entity.setActive(201 , true) 
Entity.addTag(201 , "button") 
Entity.getTransform.setPosition(201, -30, 0, -90) 
Entity.getTransform.setRotation(201, 0, 0, 0) 
Entity.getTransform.setScale(201, 5, 2.5, 5) 
Entity.addMeshRenderer(201) 
Entity.getMeshRenderer.setName(201, 'CUBE') 
Entity.getMeshRenderer.setColor(201, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(201, 32) 
Entity.getMeshRenderer.setEmissive(201, 0) 
Entity.addSphereCollider(201) 
Entity.getSphereCollider.setRadius(201, 5) 
Entity.getSphereCollider.addTag(201, "MESHCULL")
Entity.addAABBCollider(201, 1) 
Entity.getAABBCollider.setHalfSize(201, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(201, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(201, 1, "cloud")
Entity.addMeshCollider(201)
Entity.getMeshCollider.setName(201, "CUBE")
Entity.addScript(201) 
Entity.getScript.setPath(201, 'Content//scripts//DummyButton.lua')

--Dinosaur AI
AddDinoEntity(600, 0, 20, -120, 'Content//scripts//L3DinoHeadMovement1.lua')
AddDinoEntity(620, 150, 20, -30, 'Content//scripts//L3DinoHeadMovement2.lua')
AddDinoEntity(640, 160, 20, 0, 'Content//scripts//L3DinoHeadMovement3.lua')

-- Important entities
Entity.New(1 , 'dirlight' ) 
Entity.setActive(1 , true) 
Entity.addTag(1 , "dirlight") 
Entity.getTransform.setPosition(1, 33.8344, 56.25, 120.335) 
Entity.getTransform.setRotation(1, 0, 0, 0) 
Entity.getTransform.setScale(1, 1, 1, 1) 
Entity.addDirLight(1) 
Entity.getDirLight.setAmbient(1, 0.07, 0.07, 0.07) 
Entity.getDirLight.setDiffuse(1, 0.2, 0.2, 0.2) 
Entity.getDirLight.setSpecular(1, 0.1, 0.1, 0.1) 
Entity.getDirLight.setLightColor(1, 0.8, 0.6, 0.5) 
Entity.getDirLight.setLightDirection(1, -0.5, -0.7, 0) 

Entity.New(7 , 'player' ) 
Entity.setActive(7 , true) 
Entity.addTag(7 , "player") 
Entity.addScript(7) 
Entity.getScript.setPath(7, 'Content//scripts//CameraLookAtPlayerMovement.lua')

AddEndPointEntity(
400, 
250, 5, 0, -- position
0, -90, -30, -- rotation
170, 0, -25 -- button pos
)

Entity.New(2 , 'jin scene' ) 
Entity.setActive(2 , true) 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//sceneCheck.lua') 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//level1KeepTrack.lua') 

Camera.setPosition(-6.83085, 5.7, 2.723) 
Camera.setTarget(-6.83085, -0.8, 17.523) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(0) -- FPS
Camera.setMouseControl(true)
Camera.setLookingDir(0, -1, 0.8) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(16.5) 
Camera.setPitchLimit(80) 

Entity.New(450 , 'Cont' ) 
Entity.setActive(450 , true) 
Entity.addTag(450 , "font") 
Entity.getTransform.setPosition(450, 0.015, -0.025, 0) 
Entity.getTransform.setScale(450, 1.25, 1, 1) 
Entity.addGUIText(450)
Entity.getGUIText.setTextString(450, "0000000")
Entity.getGUIText.setTextColor(450, 1, 1, 1, 0)
Entity.getGUIText.setFontType(450, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(450, 
  0.5, -- width
  0.005, -- edge
  0.7, -- borderwidth
  0.3, -- borderedge
  -0.001, -- oy
  0.001, -- ox
  0.1, 0.1, 0.1) -- outlinecolor
Entity.addScript(450) 
Entity.getScript.setPath(450, 'Content//scripts//guiPoint.lua') 

