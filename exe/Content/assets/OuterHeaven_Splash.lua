Entity.New(1 , 'dirlight' ) 
Entity.setActive(1 , true) 
Entity.addTag(1 , "dirlight") 
Entity.getTransform.setPosition(1, 33.8344, 56.25, 120.335) 
Entity.getTransform.setRotation(1, 0, 0, 0) 
Entity.getTransform.setScale(1, 1, 1, 1) 
Entity.addDirLight(1) 
Entity.getDirLight.setAmbient(1, 0.01, 0.01, 0.01) 
Entity.getDirLight.setDiffuse(1, 0.5, 0.5, 0.5) 
Entity.getDirLight.setSpecular(1, 0.3, 0.3, 0.3) 
Entity.getDirLight.setLightColor(1, 0.8, 0.6, 0.5) 
Entity.getDirLight.setLightDirection(1, 0.0, -0.4, -1) 
Entity.addScript(1) 
Entity.getScript.setPath(1, 'Content//scripts//dirlight.lua') 

Entity.New(2 , 'OuterHeaven' ) 
Entity.setActive(2 , true) 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//OuterHeaven_Script.lua') 

Entity.New(4 , 'big platform' ) 
Entity.setActive(4 , true) 
Entity.addTag(4 , "wall") 
Entity.getTransform.setPosition(4, 0, 0, 0) 
Entity.getTransform.setRotation(4, 0, 0, 0) 
Entity.getTransform.setScale(4, 90, 0.5, 90) 
Entity.addMeshRenderer(4) 
Entity.getMeshRenderer.setName(4, 'CUBE') 
Entity.getMeshRenderer.setColor(4, 0.25, 0.5, 1.0) 
Entity.getMeshRenderer.setShininess(4, 32) 
Entity.getMeshRenderer.setEmissive(4, 0) 

Entity.New(420 , 'Fonto' ) 
Entity.setActive(420 , true) 
Entity.getTransform.setPosition(420, 0.18, -0.8, 0) 
Entity.getTransform.setScale(420, 3.5, 2, 2)
Entity.addGUIText(420)
Entity.getGUIText.setTextString(420, "OuterHeaven Engine")
Entity.getGUIText.setTextColor(420, 1, 1, 1, 0)
Entity.getGUIText.setFontType(420, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(420, 
  0.45, -- width
  0.05, -- edge
  0.7, -- borderwidth
  0.03, -- borderedge
  0.002, -- ox
  0.004, -- oy
  0, 0, 0) -- outlinecolor
 Entity.addScript(420) 
Entity.getScript.setPath(420, 'Content//scripts//alphachange.lua')

Entity.New(4200 , 'Fonto' ) 
Entity.addParent(4200, 420)
Entity.setActive(4200 , true) 
Entity.getTransform.setPosition(4200, 0, 0.025, 0) 
Entity.getTransform.setScale(4200, 1, 2, 2)
Entity.addGUIText(4200)
Entity.getGUIText.setTextString(4200, "Powered By")
Entity.getGUIText.setTextColor(4200, 0, 0, 0, 0)
Entity.getGUIText.setFontType(4200, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(4200, 
  0.45, -- width
  0.05, -- edge
  0.7, -- borderwidth
  0.03, -- borderedge
  0.002, -- ox
  0.004, -- oy
  1, 1, 1) -- outlinecolor
Entity.addScript(4200) 
Entity.getScript.setPath(4200, 'Content//scripts//alphachange.lua')  

  
  
  

moveup = 4

Entity.New(55 , 'cube middle' ) 
Entity.setActive(55 , true) 
Entity.getTransform.setPosition(55, 0, 0, 0  + moveup) 
Entity.getTransform.setRotation(55, 0, 0, 0) 
Entity.getTransform.setScale(55, 3, 3, 3) 
Entity.addMeshRenderer(55) 
Entity.getMeshRenderer.setName(55, 'CUBE') 
Entity.getMeshRenderer.setColor(55, 1.8, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(55, 16) 
Entity.getMeshRenderer.setEmissive(55, 0) 

Entity.New(5 , 'O' ) 
Entity.setActive(5 , true) 
Entity.getTransform.setPosition(5, -0.175, 1, 6 + moveup) 
Entity.getTransform.setRotation(5, 0, 0, 0) 
Entity.getTransform.setScale(5, 15, 3, 3) 
Entity.addMeshRenderer(5) 
Entity.getMeshRenderer.setName(5, 'CUBE') 
Entity.getMeshRenderer.setColor(5, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(5, 16) 
Entity.getMeshRenderer.setEmissive(5, 0) 

Entity.New(6 , 'O' ) 
Entity.setActive(6 , true) 
Entity.getTransform.setPosition(6, -0.175, 1, -6 + moveup) 
Entity.getTransform.setRotation(6, 0, 0, 0) 
Entity.getTransform.setScale(6, 15, 3, 3) 
Entity.addMeshRenderer(6) 
Entity.getMeshRenderer.setName(6, 'CUBE') 
Entity.getMeshRenderer.setColor(6, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(6, 16) 
Entity.getMeshRenderer.setEmissive(6, 0) 

Entity.New(7 , 'O' ) 
Entity.setActive(7 , true) 
Entity.getTransform.setPosition(7, 6, 1, 0.05 + moveup) 
Entity.getTransform.setRotation(7, 0, 0, 0) 
Entity.getTransform.setScale(7, 3, 3, 14) 
Entity.addMeshRenderer(7) 
Entity.getMeshRenderer.setName(7, 'CUBE') 
Entity.getMeshRenderer.setColor(7, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(7, 16) 
Entity.getMeshRenderer.setEmissive(7, 0) 

Entity.New(8 , 'O' ) 
Entity.setActive(8 , true) 
Entity.getTransform.setPosition(8, -6, 1, 0.05+ moveup) 
Entity.getTransform.setRotation(8, 0, 0, 0) 
Entity.getTransform.setScale(8, 3, 3, 14) 
Entity.addMeshRenderer(8) 
Entity.getMeshRenderer.setName(8, 'CUBE') 
Entity.getMeshRenderer.setColor(8, 0.8, 0.8, 0.8) 
Entity.getMeshRenderer.setShininess(8, 16) 
Entity.getMeshRenderer.setEmissive(8, 0) 

Camera.setPosition(-6.83085, 5.7, 2.723) 
Camera.setTarget(-6.83085, -0.8, 17.523) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(0) -- FPS
Camera.setMouseControl(true)
Camera.setLookingDir(0, -1, 0.8) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(16.5) 
Camera.setPitchLimit(80) 









