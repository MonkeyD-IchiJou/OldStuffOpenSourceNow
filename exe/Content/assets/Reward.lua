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

Entity.New(420 , 'Fonto' ) 
Entity.setActive(420 , true) 
Entity.getTransform.setPosition(420, 0.4, -0.2, 0) 
Entity.getTransform.setScale(420, 3, 2, 2)
Entity.addGUIText(420)
Entity.getGUIText.setTextString(420, "You WIN !!")
Entity.getGUIText.setTextColor(420, 2, 0.0, 0.0, 0)
Entity.getGUIText.setFontType(420, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(420, 
  0.45, -- width
  0.05, -- edge
  0.425, -- borderwidth
  0.03, -- borderedge
  -0.002, -- oy
  0.002, -- ox
  0.8, 0.8, 0.8) -- outlinecolor
  

Entity.New(2 , 'Reward' ) 
Entity.setActive(2 , true) 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//Reward_Script.lua') 


Camera.setPosition(0, 0, 0) 
Camera.setTarget(0, 0, 0) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(1) -- TPS
Camera.setMouseControl(false)
Camera.setLookingDir(1, 0, 0) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(106.5) 
Camera.setPitchLimit(80) 

Entity.New(422 , 'Cont' ) 
Entity.setActive(422 , true) 
Entity.addTag(422 , "font") 
Entity.getTransform.setPosition(422, 0.4, -0.525, 0) 
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
Entity.getScript.setPath(422, 'Content//scripts//showPoint.lua')  


Entity.New(423 , 'Cont' ) 
Entity.setActive(423 , true) 
Entity.addTag(423 , "font") 
Entity.getTransform.setPosition(423, 0.4, -0.625, 0) 
Entity.getTransform.setScale(423, 1.25, 1, 1) 
Entity.addGUIText(423)
Entity.getGUIText.setTextString(423, "time")
Entity.getGUIText.setTextColor(423, 1, 1, 1, 0)
Entity.getGUIText.setFontType(423, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(423, 
  0.5, -- width
  0.005, -- edge
  0.7, -- borderwidth
  0.3, -- borderedge
  -0.001, -- oy
  0.001, -- ox
  0.1, 0.1, 0.1) -- outlinecolor 
Entity.addScript(423) 
Entity.getScript.setPath(423, 'Content//scripts//showTime.lua') 









