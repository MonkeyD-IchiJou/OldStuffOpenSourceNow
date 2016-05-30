require("Content//assets//endpointassets")
require("Content//assets//cloudassets")
require("Content//assets//platformassets")


for i = 1, 30, 1 do 
	x = math.random(-15, 50) 
	y = math.random(0, 3) 
	z = math.random(-50, 50) 
	
	Entity.addCollectable(x, y, z)
end

for i = 1, 20, 1 do 
	Entity.addCollectable(-40, 45 - i * 1.95, -45 + i * 5)
end

for i = 1, 16, 1 do 
	Entity.addCollectable(-55, 3, 50 - i * 6)
end


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

AddPlatformEntity(
4, 
0, -1.9, 0, 
125, 1, 125, 
0, 0, 0
)

AddPlatformEntity(
600, 
-50, 15, 0, 
60, 1, 125, 
0, 0, 90
)

AddPlatformEntity(
601, 
60, -1.9, 0, 
10, 1, 125,
0, 0, 90
)

AddPlatformEntity(
602, 
0, -1.9, 60, 
125, 1, 10, 
90, 0, 0
)

AddPlatformEntity(
603, 
0, -1.9, -60, 
125, 1, 10, 
90, 0, 0
)

AddPlatformEntity(
604, 
-30, 1, 0, 
40, 6, 125, 
0, 0, 0
)

AddPlatformEntity(
605, 
-40, 20, 0, 
20, 1, 100, 
20, 0, 0
)



AddPlatformEntity(
606, 
-50, 37, -67, 
40, 1, 40, 
0, 0, 0
)

AddCloudEntity(902, 
-65, 37, -40, 
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(903, 
-75, 37, -30, 
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(904, 
-85, 37, -20, 
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(905, 
-95, 37, -10, 
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(906, 
-105, 37, 0, 
10, 2.0, 10,
0.4, 1.0, 1.9)

AddCloudEntity(907, 
-115, 37, 10, 
10, 2.0, 10,
0.4, 1.0, 1.9)


AddPlatformEntity(
607, 
-125, 10, 50, 
70, 1, 20, 
0, 0, 0
)

AddPlatformEntity(
608, 
-240, 10, 0, 
100, 1, 60, 
0, 0, 0
)

AddPlatformEntity(
609, 
-220, 15, 0, 
10, 10, 10, 
0, 0, 0
)

AddCloudEntity(911, 
-170, 15, 30, 
10, 2.0, 10,
0.4, 1.0, 1.9)



Entity.New(10000 , 'WALL' ) 
Entity.setActive(10000 , true) 
Entity.addTag(10000 , "Door") 
Entity.getTransform.setPosition(10000, -250, 20, 0) 
Entity.getTransform.setRotation(10000, 0, 0, 0) 
Entity.getTransform.setScale(10000, 5, 30, 100) 
Entity.addMeshRenderer(10000) 
Entity.getMeshRenderer.setName(10000, 'CUBE') 
Entity.getMeshRenderer.setColor(10000, 1, 0.5, 0.7) 
Entity.getMeshRenderer.setShininess(10000, 32) 
Entity.getMeshRenderer.setEmissive(10000, 0) 
Entity.addSphereCollider(10000) 
Entity.getSphereCollider.setRadius(10000, 50) 
Entity.getSphereCollider.addTag(10000, "MESHCULL")
Entity.addMeshCollider(10000)
Entity.getMeshCollider.setName(10000, "CUBE")
Entity.addTrigger(10000)
Entity.addScript(10000) 
Entity.getScript.setPath(10000, 'Content//scripts//DoorUpDown.lua')

Entity.New(1000 , 'button' ) 
Entity.setActive(1000 , true) 
Entity.addTag(1000 , "button") 
Entity.getTransform.setPosition(1000, -220, 20.5, 0) 
Entity.getTransform.setRotation(1000, 0, 0, 0) 
Entity.getTransform.setScale(1000, 5, 2.5, 5) 
Entity.addMeshRenderer(1000) 
Entity.getMeshRenderer.setName(1000, 'CUBE') 
Entity.getMeshRenderer.setColor(1000, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(1000, 32) 
Entity.getMeshRenderer.setEmissive(1000, 0) 
Entity.addSphereCollider(1000) 
Entity.getSphereCollider.setRadius(1000, 5) 
Entity.getSphereCollider.addTag(1000, "MESHCULL")
Entity.addAABBCollider(1000, 1) 
Entity.getAABBCollider.setHalfSize(1000, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(1000, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(1000, 1, "cloud")
Entity.addMeshCollider(1000)
Entity.getMeshCollider.setName(1000, "CUBE")
Entity.addScript(1000) 
Entity.getScript.setPath(1000, 'Content//scripts//BodyButton.lua')
Entity.TriggerLock(1000, 10000)

Entity.New(10002 , 'button' ) 
Entity.setActive(10002 , true) 
Entity.addTag(10002 , "button") 
Entity.getTransform.setPosition(10002, -230, 10.5, -20) 
Entity.getTransform.setRotation(10002, 0, 0, 0) 
Entity.getTransform.setScale(10002, 5, 2.5, 5) 
Entity.addMeshRenderer(10002) 
Entity.getMeshRenderer.setName(10002, 'CUBE') 
Entity.getMeshRenderer.setColor(10002, 1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(10002, 32) 
Entity.getMeshRenderer.setEmissive(10002, 0) 
Entity.addSphereCollider(10002) 
Entity.getSphereCollider.setRadius(10002, 5) 
Entity.getSphereCollider.addTag(10002, "MESHCULL")
Entity.addAABBCollider(10002, 1) 
Entity.getAABBCollider.setHalfSize(10002, 1, -0.1, -0.25, -0.1)
Entity.getAABBCollider.setPosition(10002, 1, 0, 0.9, 0)
Entity.getAABBCollider.addTag(10002, 1, "cloud")
Entity.addMeshCollider(10002)
Entity.getMeshCollider.setName(10002, "CUBE")
Entity.addScript(10002) 
Entity.getScript.setPath(10002, 'Content//scripts//BodyButton2.lua')
Entity.TriggerLock(10002, 10000)

--[[

AddCloudEntity(900, 
90, 1.0, -10, 
10, 2.0, 10,
0.4, 1.0, 1.9)
Entity.addCollectable(90, 6.0, -10)

AddCloudEntity(902, 
70, 1.0, 10, 
10, 2.0, 10,
0.4, 1.0, 1.9)
Entity.addCollectable(70, 6.0, 10)

AddCloudEntity(901, 
50, 3.0, -10, 
10, 2.0, 10,
0.4, 1.0, 1.9)
Entity.addCollectable(50, 8.0, -10)

]]--
	

-- important assets

AddEndPointEntity(
400, 
-290, 25, 0,
0, 90, 0,
-260, 12, 20
)

Entity.New(7 , 'player' ) 
Entity.setActive(7 , true) 
Entity.addTag(7 , "player") 
Entity.addScript(7) 
Entity.getScript.setPath(7, 'Content//scripts//CameraLookAtPlayerMovement.lua')

Entity.New(2 , 'jou scene' ) 
Entity.setActive(2 , true) 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//sceneCheck.lua') 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//level1KeepTrack.lua')

Entity.New(422 , 'Cont' ) 
Entity.setActive(422 , true) 
Entity.addTag(422 , "font") 
Entity.getTransform.setPosition(422, 0.015, -0.025, 0) 
Entity.getTransform.setScale(422, 1.25, 1, 1) 
Entity.addGUIText(422)
Entity.getGUIText.setTextString(422, "0000000")
Entity.getGUIText.setTextColor(422, 1, 1, 1, 0)
Entity.getGUIText.setFontType(422, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(422, 
  0.5, -- width
  0.005, -- edge
  0.7, -- borderwidth
  0.3, -- borderedge
  -0.001, -- oy
  0.001, -- ox
  0.1, 0.1, 0.1) -- outlinecolor
Entity.addScript(422) 
Entity.getScript.setPath(422, 'Content//scripts//guiPoint.lua')  

Camera.setPosition(-6.83085, 5.7, 2.723) 
Camera.setTarget(-6.83085, -0.8, 17.523) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(0) -- FPS
Camera.setMouseControl(true)
Camera.setLookingDir(0, -1, 0.8) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(16.5) 
Camera.setPitchLimit(80) 

