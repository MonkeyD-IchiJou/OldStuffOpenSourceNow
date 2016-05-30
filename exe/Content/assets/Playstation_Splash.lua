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
Entity.getTransform.setPosition(420, 0.3, -0.35, 0) 
Entity.getTransform.setScale(420, 5, 2, 2)
Entity.addGUIText(420)
Entity.getGUIText.setTextString(420, "Team Dragon")
Entity.getGUIText.setTextColor(420, 2, 0.0, 0.0, 0)
Entity.getGUIText.setFontType(420, "PRISMFONT")
Entity.getGUIText.setTextMaterial(420, 
  0.45, -- width
  0.05, -- edge
  0.425, -- borderwidth
  0.03, -- borderedge
  -0.002, -- oy
  0.002, -- ox
  0.8, 0.8, 0.8) -- outlinecolor
Entity.addScript(420) 
Entity.getScript.setPath(420, 'Content//scripts//alphachange.lua') 
  
  
Entity.New(4200 , 'Fonto' ) 
Entity.setActive(4200 , true) 
Entity.addParent(4200, 420)
Entity.getTransform.setPosition(4200, 0.35, -0.15, 0) 
Entity.getTransform.setScale(4200, 1.5, 1, 1)
Entity.addGUIText(4200)
Entity.getGUIText.setTextString(4200, "present")
Entity.getGUIText.setTextColor(4200, 1, 1.0, 1.0, 0)
Entity.getGUIText.setFontType(4200, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(4200, 
  0.45, -- width
  0.05, -- edge
  0.5, -- borderwidth
  0.03, -- borderedge
  -0.006, -- oy
  0.006, -- ox
  2, 0, 0) -- outlinecolor
Entity.addScript(4200) 
Entity.getScript.setPath(4200, 'Content//scripts//alphachange.lua') 
 


Entity.New(6 , 'Big ' ) 
Entity.setActive(6 , true) 
Entity.getTransform.setPosition(6, 0, -0.25, 15) 
Entity.getTransform.setRotation(6, 0, 0, 0) 
Entity.getTransform.setScale(6, 1, 1, 1) 
Entity.addMeshRenderer(6) 
Entity.getMeshRenderer.setName(6, 'CUBE') 
Entity.getMeshRenderer.setColor(6, 1, 0.8, 0.9) 
Entity.getMeshRenderer.setShininess(6, 16) 
Entity.getMeshRenderer.setEmissive(6, 1) 
Entity.addScript(6) 
Entity.getScript.setPath(6, 'Content//scripts//CubeTranslate.lua') 
  

Entity.New(2 , 'playstation' ) 
Entity.setActive(2 , true) 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//Playstation_Script.lua') 


Camera.setPosition(0, 0, 0) 
Camera.setTarget(0, 0, 0) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(1) -- TPS
Camera.setMouseControl(false)
Camera.setLookingDir(1, 0, 0) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(106.5) 
Camera.setPitchLimit(80) 









