require("Content//scripts//vec3")

Entity.New(1 , 'dirlight' ) 
Entity.setActive(1 , true) 
Entity.addTag(1 , "dirlight") 
Entity.getTransform.setPosition(1, 33.8344, 56.25, 120.335) 
Entity.getTransform.setRotation(1, 0, 0, 0) 
Entity.getTransform.setScale(1, 1, 1, 1) 
Entity.addDirLight(1) 
Entity.getDirLight.setAmbient(1, 0.005, 0.005, 0.005) 
Entity.getDirLight.setDiffuse(1, 0.01, 0.01, 0.01) 
Entity.getDirLight.setSpecular(1, 0.02, 0.02, 0.02) 
Entity.getDirLight.setLightColor(1, 0.5, 0.7, 0.8) 
Entity.getDirLight.setLightDirection(1, -0.0, -1.0, 0.0) 

Entity.New(2 , 'title' ) 
Entity.setActive(2 , true) 
Entity.addScript(2) 
Entity.getScript.setPath(2, 'Content//scripts//Title_Script.lua') 

Entity.New(4 , 'big platform' ) 
Entity.setActive(4 , true) 
Entity.addTag(4 , "wall") 
Entity.getTransform.setPosition(4, 0, 0, 0) 
Entity.getTransform.setRotation(4, 0, 0, 0) 
Entity.getTransform.setScale(4, 20, 0.5, 20) 
Entity.addMeshRenderer(4) 
Entity.getMeshRenderer.setName(4, 'CUBE') 
Entity.getMeshRenderer.setColor(4, 1.0, 1.0, 1.0) 
Entity.getMeshRenderer.setShininess(4, 16) 
Entity.getMeshRenderer.setEmissive(4, 0) 

Entity.New(5 , 'Big ' ) 
Entity.setActive(5 , true) 
Entity.addTag(5 , "wall") 
Entity.getTransform.setPosition(5, 0, 0, 0) 
Entity.getTransform.setRotation(5, 0, 0, 0) 
Entity.getTransform.setScale(5, 50, 50, 50) 
Entity.addMeshRenderer(5) 
Entity.getMeshRenderer.setName(5, 'CUBEIN') 
Entity.getMeshRenderer.setColor(5, 1, 1, 1) 
Entity.getMeshRenderer.setShininess(5, 16) 
Entity.getMeshRenderer.setEmissive(5, 0) 


math.randomseed(os.time())


id = 600
for i = 1, 5, 1 do 
	
	r = math.random(5, 11)
	g = math.random(5, 11)
	b = math.random(5, 11)

	Entity.New(id , 'pointlight ' ) 
	Entity.setActive(id , true) 
	Entity.addTag(id , "pointlight") 
	Entity.getTransform.setPosition(id, 0, 0, 0) 
	Entity.getTransform.setRotation(id, 0, 0, 0) 
	Entity.getTransform.setScale(id, 0.4, 0.4, 0.4) 
	Entity.addMeshRenderer(id) 
	Entity.getMeshRenderer.setName(id, 'CUBE') 
	Entity.getMeshRenderer.setColor(id, 1, 1, 1) 
	Entity.getMeshRenderer.setShininess(id, 16) 
	Entity.getMeshRenderer.setEmissive(id, 1) 
	Entity.addPointLight(id)
	Entity.getPointLight.setDiffuse(id, 0.3, 0.3, 0.3)
	Entity.getPointLight.setSpecular(id, 0.3, 0.3, 0.3)
	Entity.getPointLight.setLightColor(id, r/ 10.0, g / 10.0, b / 10.0)
	Entity.addSphereCollider(id) 
	Entity.getSphereCollider.setRadius(id, 0.5) 
	Entity.getSphereCollider.addTag(id, "MESHCULL")
	
	id = id + 1
	
end

Entity.getTransform.setPosition(600, 6, 1.1, 0) 
Entity.getTransform.setPosition(601, -5, 1.5, 0) 
Entity.getTransform.setPosition(602, 7, 1.25, 6)
Entity.getTransform.setPosition(603, -7, 2.5, 7) 
Entity.getTransform.setPosition(604, 7, 1.7, -6) 


vec = vec3.New()
origin = vec3.New()
origin:Set(0, 0, 0)

for i = 1, 15, 1 do 
	
	repeat
		vec:Set(math.random(-20, 20), math.random(-20, 20), math.random(-20, 20))
		distance = (vec - origin):Length()
	
	until distance > 19 
	
	r = math.random(4, 11)
	g = math.random(4, 11)
	b = math.random(4, 11)

	Entity.New(id , 'pointlight ' ) 
	Entity.setActive(id , true) 
	Entity.addTag(id , "pointlight") 
	Entity.getTransform.setPosition(id, vec.x, vec.y, vec.z) 
	Entity.getTransform.setRotation(id, 0, 0, 0) 
	Entity.getTransform.setScale(id, 0.4, 0.4, 0.4) 
	Entity.addMeshRenderer(id) 
	Entity.getMeshRenderer.setName(id, 'CUBE') 
	Entity.getMeshRenderer.setColor(id, 1, 1, 1) 
	Entity.getMeshRenderer.setShininess(id, 16) 
	Entity.getMeshRenderer.setEmissive(id, 1) 
	Entity.addPointLight(id)
	Entity.getPointLight.setDiffuse(id, 0.3, 0.3, 0.3)
	Entity.getPointLight.setSpecular(id, 0.3, 0.3, 0.3)
	Entity.getPointLight.setLightColor(id, r/ 10.0, g / 10.0, b / 10.0)
	Entity.addSphereCollider(id) 
	Entity.getSphereCollider.setRadius(id, 0.5) 
	Entity.getSphereCollider.addTag(id, "MESHCULL")
	
	id = id + 1
	
end

Entity.New(69 , 'Parent' ) 
Entity.setActive(69 , true) 
Entity.getTransform.setPosition(69, 0, 0, 0) 
Entity.getTransform.setScale(69, 1, 1, 1) 
Entity.addScript(69) 
Entity.getScript.setPath(69, 'Content//scripts//canvas.lua')
Entity.addCanvas(69)


Entity.New(420 , 'Bravely' ) 
Entity.setActive(420 , true) 
Entity.addTag(420 , "font") 
Entity.addParent(420, 69)
Entity.getTransform.setPosition(420, 0.15, -0.12, 0) 
Entity.getTransform.setScale(420, 7.5, 7, 7) 
Entity.addGUIText(420)
Entity.getGUIText.setTextString(420, "Bravely")
Entity.getGUIText.setTextColor(420, 1.5, 0.5, 0, 0)
Entity.getGUIText.setFontType(420, "PRISMFONT")
Entity.getGUIText.setTextMaterial(420, 
  0.45, -- width
  0.05, -- edge
  0.49, -- borderwidth
  0.03, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  1.8, 0.1, 0.1) -- outlinecolor

Entity.New(421 , 'Dragon' ) 
Entity.setActive(421 , true) 
Entity.addTag(421 , "font") 
Entity.addParent(421, 69)
Entity.getTransform.setPosition(421, 0.48, -0.37, 0) 
Entity.getTransform.setScale(421, 8, 7, 7) 
Entity.addGUIText(421)
Entity.getGUIText.setTextString(421, "Dragon")
Entity.getGUIText.setTextColor(421, 1.5, 0.5, 0, 0)
Entity.getGUIText.setFontType(421, "PRISMFONT")
Entity.getGUIText.setTextMaterial(421, 
  0.45, -- width
  0.05, -- edge
  0.49, -- borderwidth
  0.03, -- borderedge
  -0.001, -- oy
  0.001, -- ox
  1.8, 0.1, 0.1) -- outlinecolor




Entity.New(422 , 'Cont' ) 
Entity.setActive(422 , true) 
Entity.addTag(422 , "font") 
Entity.addParent(422, 69)
Entity.getTransform.setPosition(422, 0.29, -0.8, 0) 
Entity.getTransform.setScale(422, 2, 1.5, 1.5) 
Entity.addGUIText(422)
Entity.getGUIText.setTextString(422, "Press any SPACE to continue")
Entity.getGUIText.setTextColor(422, 0.9, 0.9, 0.9, 0)
Entity.getGUIText.setFontType(422, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(422, 
  0.5, -- width
  0.005, -- edge
  0.7, -- borderwidth
  0.3, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0.8, 0.4, 0) -- outlinecolor
Entity.addScript(422) 
Entity.getScript.setPath(422, 'Content//scripts//fontalphachange.lua') 

--[[ Main Menu ]]--

Entity.New(13 , 'Level Select' ) 
Entity.setActive(13 , true) 
Entity.addTag(13 , "font") 
Entity.addParent(13, 69)
Entity.getTransform.setPosition(13, 0.75, -1.89, 0) 
Entity.getTransform.setScale(13, 2.25, 0.1, 1) 
Entity.addScript(13) 
Entity.addGUIText(13)
Entity.getGUIText.setTextString(13, "Level Select")
Entity.getGUIText.setTextColor(13, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(13, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(13, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(13) 
Entity.getScript.setPath(13, 'Content//scripts//levelselect.lua')
Entity.addAABBCollider(13, 1)
Entity.getAABBCollider.addTag(13, 1, "GUI")
Entity.getAABBCollider.setHalfSize(13, 1, 0.125, 0.03, 0.1)
Entity.getAABBCollider.setPosition(13, 1, 0.1, -0.01, 0)


Entity.New(14 , 'Continue' ) 
Entity.setActive(14 , true) 
Entity.addTag(14 , "font") 
Entity.addParent(14, 69)
Entity.getTransform.setPosition(14, 0.81, -1.96, 0) 
Entity.getTransform.setScale(14, 2.25, 0.1, 1) 
Entity.addScript(14) 
Entity.addGUIText(14)
Entity.getGUIText.setTextString(14, "Continue")
Entity.getGUIText.setTextColor(14, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(14, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(14, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(14) 
Entity.getScript.setPath(14, 'Content//scripts//continue.lua')
Entity.addAABBCollider(14, 1)
Entity.getAABBCollider.addTag(14, 1, "GUI")
Entity.getAABBCollider.setHalfSize(14, 1, 0.1, 0.03, 0.1)
Entity.getAABBCollider.setPosition(14, 1, 0.055, -0.015, 0)


Entity.New(15 , 'Options' ) 
Entity.setActive(15 , true) 
Entity.addTag(15 , "font") 
Entity.addParent(15, 69)
Entity.getTransform.setPosition(15, 0.835, -2.03, 0) 
Entity.getTransform.setScale(15, 2.25, 0.1, 1) 
Entity.addScript(15) 
Entity.addGUIText(15)
Entity.getGUIText.setTextString(15, "Options")
Entity.getGUIText.setTextColor(15, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(15, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(15, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(15) 
Entity.getScript.setPath(15, 'Content//scripts//options.lua')
Entity.addAABBCollider(15, 1)
Entity.getAABBCollider.addTag(15, 1, "GUI")
Entity.getAABBCollider.setHalfSize(15, 1, 0.08, 0.03, 0.1)
Entity.getAABBCollider.setPosition(15, 1, 0.05, -0.015, 0)

Entity.New(16 , 'Quit' ) 
Entity.setActive(16 , true) 
Entity.addTag(16 , "font") 
Entity.addParent(16, 69)
Entity.getTransform.setPosition(16, 0.9, -2.1, 0) 
Entity.getTransform.setScale(16, 2.25, 0.1, 1) 
Entity.addScript(16) 
Entity.addGUIText(16)
Entity.getGUIText.setTextString(16, "Quit")
Entity.getGUIText.setTextColor(16, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(16, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(16, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(16) 
Entity.getScript.setPath(16, 'Content//scripts//quit.lua') 
Entity.addAABBCollider(16, 1)
Entity.getAABBCollider.addTag(16, 1, "GUI")
Entity.getAABBCollider.setHalfSize(16, 1, 0.07, 0.03, 0.1)
Entity.getAABBCollider.setPosition(16, 1, 0, -0.015, 0)

--[[ Level Select ]]--

Entity.New(20 , 'Level Select Screen' ) 
Entity.setActive(20 , true) 
Entity.addTag(20 , "font") 
Entity.addParent(20, 69)
Entity.getTransform.setPosition(20, 1.548, -1.3, 0) 
Entity.getTransform.setScale(20, 6, 3, 5)
Entity.addScript(20)
Entity.addGUIText(20)
Entity.getGUIText.setTextString(20, "Level Select")
Entity.getGUIText.setTextColor(20, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(20, "PRISMFONT")
Entity.getGUIText.setTextMaterial(20, 
  0.45, -- width
  0.05, -- edge
  0.5, -- borderwidth
  0.03, -- borderedge
  -0.006, -- oy
  0.006, -- ox
  0.15, 0.05, 0) -- outlinecolor


Entity.New(21 , 'Level Select Back' ) 
Entity.setActive(21 , true) 
Entity.addTag(21 , "font") 
Entity.addParent(21, 69)
Entity.getTransform.setPosition(21, 1.265, -2.18, 0) 
Entity.getTransform.setScale(21, 2.25, 0.1, 1) 
Entity.addGUIText(21)
Entity.getGUIText.setTextString(21, "Back")
Entity.getGUIText.setTextColor(21, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(21, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(21, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(21) 
Entity.getScript.setPath(21, 'Content//scripts//back_ls.lua') 
Entity.addAABBCollider(21, 1)
Entity.getAABBCollider.addTag(21, 1, "GUI")
Entity.getAABBCollider.setHalfSize(21, 1, 0.06, 0.03, 0.1)
Entity.getAABBCollider.setPosition(21, 1, 0.04, -0.015, 0)


Entity.New(211 , 'Level1' ) 
Entity.setActive(211 , true) 
Entity.addTag(211 , "font") 
Entity.addParent(211, 69)
Entity.getTransform.setPosition(211, 1.565, -1.7, 0) 
Entity.getTransform.setScale(211, 2.25, 0.1, 1) 
Entity.addGUIText(211)
Entity.getGUIText.setTextString(211, "LEVEL 1")
Entity.getGUIText.setTextColor(211, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(211, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(211, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(211) 
Entity.getScript.setPath(211, 'Content//scripts//Level1Press.lua') 
Entity.addAABBCollider(211, 1)
Entity.getAABBCollider.addTag(211, 1, "GUI")
Entity.getAABBCollider.setHalfSize(211, 1, 0.06, 0.03, 0.1)
Entity.getAABBCollider.setPosition(211, 1, 0.04, -0.015, 0)


Entity.New(212 , 'Level2' ) 
Entity.setActive(212 , true) 
Entity.addTag(212 , "font") 
Entity.addParent(212, 69)
Entity.getTransform.setPosition(212, 1.865, -1.7, 0) 
Entity.getTransform.setScale(212, 2.25, 0.1, 1) 
Entity.addGUIText(212)
Entity.getGUIText.setTextString(212, "LEVEL 2")
Entity.getGUIText.setTextColor(212, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(212, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(212, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(212) 
Entity.getScript.setPath(212, 'Content//scripts//Level2Press.lua') 
Entity.addAABBCollider(212, 1)
Entity.getAABBCollider.addTag(212, 1, "GUI")
Entity.getAABBCollider.setHalfSize(212, 1, 0.06, 0.03, 0.1)
Entity.getAABBCollider.setPosition(212, 1, 0.04, -0.015, 0)


Entity.New(213 , 'Level3' ) 
Entity.setActive(213 , true) 
Entity.addTag(213 , "font") 
Entity.addParent(213, 69)
Entity.getTransform.setPosition(213, 1.565, -1.9, 0) 
Entity.getTransform.setScale(213, 2.25, 0.1, 1) 
Entity.addGUIText(213)
Entity.getGUIText.setTextString(213, "LEVEL 3")
Entity.getGUIText.setTextColor(213, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(213, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(213, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(213) 
Entity.getScript.setPath(213, 'Content//scripts//Level3Press.lua') 
Entity.addAABBCollider(213, 1)
Entity.getAABBCollider.addTag(213, 1, "GUI")
Entity.getAABBCollider.setHalfSize(213, 1, 0.06, 0.03, 0.1)
Entity.getAABBCollider.setPosition(213, 1, 0.04, -0.015, 0)


Entity.New(214 , 'Level4' ) 
Entity.setActive(214 , true) 
Entity.addTag(214 , "font") 
Entity.addParent(214, 69)
Entity.getTransform.setPosition(214, 1.865, -1.9, 0) 
Entity.getTransform.setScale(214, 2.25, 0.1, 1) 
Entity.addGUIText(214)
Entity.getGUIText.setTextString(214, "LEVEL 4")
Entity.getGUIText.setTextColor(214, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(214, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(214, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(214) 
Entity.getScript.setPath(214, 'Content//scripts//Level4Press.lua') 
Entity.addAABBCollider(214, 1)
Entity.getAABBCollider.addTag(214, 1, "GUI")
Entity.getAABBCollider.setHalfSize(214, 1, 0.06, 0.03, 0.1)
Entity.getAABBCollider.setPosition(214, 1, 0.04, -0.015, 0)

-- [[ Options ]] --

Entity.New(30 , 'Options Screen' ) 
Entity.setActive(30 , true) 
Entity.addTag(30 , "font") 
Entity.addParent(30, 69)
Entity.getTransform.setPosition(30, -0.93, -1.3, 0) 
Entity.getTransform.setScale(30, 5, 3, 5)
Entity.addScript(30)
Entity.addGUIText(30)
Entity.getGUIText.setTextString(30, "Options")
Entity.getGUIText.setTextColor(30, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(30, "PRISMFONT")
Entity.getGUIText.setTextMaterial(30, 
  0.45, -- width
  0.05, -- edge
  0.5, -- borderwidth
  0.03, -- borderedge
  -0.006, -- oy
  0.006, -- ox
  0.15, 0.05, 0) -- outlinecolor


Entity.New(31 , 'Options Back' ) 
Entity.setActive(31 , true) 
Entity.addTag(31 , "font") 
Entity.addParent(31, 69)
Entity.getTransform.setPosition(31, -0.4, -2.18, 0) 
Entity.getTransform.setScale(31, 2.25, 0.1, 1) 
Entity.addScript(31) 
Entity.addGUIText(31)
Entity.getGUIText.setTextString(31, "Back")
Entity.getGUIText.setTextColor(31, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(31, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(31, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(31) 
Entity.getScript.setPath(31, 'Content//scripts//back_op.lua') 
Entity.addAABBCollider(31, 1)
Entity.getAABBCollider.addTag(31, 1, "GUI")
Entity.getAABBCollider.setHalfSize(31, 1, 0.06, 0.03, 0.1)
Entity.getAABBCollider.setPosition(31, 1, 0.04, -0.015, 0)

--------

Entity.New(33 , 'Sensitivity' ) 
Entity.setActive(33 , true) 
Entity.addTag(33 , "font") 
Entity.addParent(33, 69)
Entity.getTransform.setPosition(33, -1.17, -1.5, 0) 
Entity.getTransform.setScale(33, 2.25, 0.1, 1) 
Entity.addScript(33) 
Entity.addGUIText(33)
Entity.getGUIText.setTextString(33, "Sensitivity")
Entity.getGUIText.setTextColor(33, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(33, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(33, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor




-- Sensitivity Slider --

Entity.New(331 , 'Sensitivity slider line' ) 
Entity.setActive(331 , true) 
Entity.addTag(331, "font") 
Entity.addParent(331, 69)
Entity.getTransform.setPosition(331, -0.87, -1.495, 0) 
Entity.getTransform.setScale(331, 2.25, 0.1, 1) 
Entity.addScript(331) 
Entity.addGUIText(331)
Entity.getGUIText.setTextString(331, "-------------------")
Entity.getGUIText.setTextColor(331, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(331, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(331, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(332, 'Sensitivity slider right line' ) 
Entity.setActive(332, true) 
Entity.addTag(332, "font") 
Entity.addParent(332, 69)
Entity.getTransform.setPosition(332, -0.49, -1.5, 0) 
Entity.getTransform.setScale(332, 2.25, 0.1, 1) 
Entity.addScript(332) 
Entity.addGUIText(332)
Entity.getGUIText.setTextString(332, "l")
Entity.getGUIText.setTextColor(332, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(332, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(332, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(333, 'Sensitivity slider left line' ) 
Entity.setActive(333 , true) 
Entity.addTag(333, "font") 
Entity.addParent(333, 69)
Entity.getTransform.setPosition(333, -0.87, -1.5, 0) 
Entity.getTransform.setScale(333, 2.25, 0.1, 1) 
Entity.addScript(333) 
Entity.addGUIText(333)
Entity.getGUIText.setTextString(333, "l")
Entity.getGUIText.setTextColor(333, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(333, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(333, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(334, 'Sens min val' ) 
Entity.setActive(334 , true) 
Entity.addTag(334, "font") 
Entity.addParent(334, 69)
Entity.getTransform.setPosition(334, -0.925, -1.495, 0) 
Entity.getTransform.setScale(334, 1.75, 0.1, 1) 
Entity.addScript(334) 
Entity.addGUIText(334)
Entity.getGUIText.setTextString(334, "100")
Entity.getGUIText.setTextColor(334, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(334, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(334, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(335, 'Sens max val' ) 
Entity.setActive(335 , true) 
Entity.addTag(335, "font") 
Entity.addParent(335, 69)
Entity.getTransform.setPosition(335, -0.472, -1.495, 0) 
Entity.getTransform.setScale(335, 1.75, 0.1, 1) 
Entity.addScript(335) 
Entity.addGUIText(335)
Entity.getGUIText.setTextString(335, "150")
Entity.getGUIText.setTextColor(335, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(335, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(335, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(336, 'Sensitivity slider' ) 
Entity.setActive(336 , true) 
Entity.addTag(336, "font") 
Entity.addParent(336, 69)
Entity.getTransform.setPosition(336, -0.68, -1.495, 0) 
Entity.getTransform.setScale(336, 2, 0.1, 1) 
Entity.addScript(336) 
Entity.addGUIText(336)
Entity.getGUIText.setTextString(336, "0")
Entity.getGUIText.setTextColor(336, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(336, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(336, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(336) 
Entity.getScript.setPath(336, 'Content//scripts//slider_sens.lua') 
Entity.addAABBCollider(336, 1)
Entity.getAABBCollider.addTag(336, 1, "GUI")
Entity.getAABBCollider.setHalfSize(336, 1, 0.007, 0.02, 0.1)
Entity.getAABBCollider.setPosition(336, 1, 0.003, -0.02, 0)

------


Entity.New(34 , 'Line' ) 
Entity.setActive(34 , true) 
Entity.addTag(34 , "font") 
Entity.addParent(34, 69)
Entity.getTransform.setPosition(34, -1.17, -1.6, 0) 
Entity.getTransform.setScale(34, 2.25, 0.1, 1) 
Entity.addScript(34) 
Entity.addGUIText(34)
Entity.getGUIText.setTextString(34, "------------------------------------")
Entity.getGUIText.setTextColor(34, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(34, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(34, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(35 , 'SSAO Control' ) 
Entity.setActive(35 , true) 
Entity.addTag(35 , "font") 
Entity.addParent(35, 69)
Entity.getTransform.setPosition(35, -1.17, -1.9, 0) 
Entity.getTransform.setScale(35, 2.25, 0.1, 1) 
Entity.addScript(35) 
Entity.addGUIText(35)
Entity.getGUIText.setTextString(35, "SSAO")
Entity.getGUIText.setTextColor(35, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(35, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(35, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

-- SSAO Checkbox --

Entity.New(351, 'SSAO Checkbox top' ) 
Entity.setActive(351 , true) 
Entity.addTag(351, "font") 
Entity.addParent(351, 69)
Entity.getTransform.setPosition(351, -0.891, -1.87, 0) 
Entity.getTransform.setScale(351, 2.25, 0.1, 1) 
Entity.addScript(351) 
Entity.addGUIText(351)
Entity.getGUIText.setTextString(351, "-")
Entity.getGUIText.setTextColor(351, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(351, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(351, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(352, 'SSAO Checkbox bottom' ) 
Entity.setActive(352 , true) 
Entity.addTag(352, "font") 
Entity.addParent(352, 69)
Entity.getTransform.setPosition(352, -0.891, -1.907, 0) 
Entity.getTransform.setScale(352, 2.25, 0.1, 1) 
Entity.addScript(352) 
Entity.addGUIText(352)
Entity.getGUIText.setTextString(352, "-")
Entity.getGUIText.setTextColor(352, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(352, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(352, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(353, 'SSAO Checkbox right' ) 
Entity.setActive(353 , true) 
Entity.addTag(353, "font") 
Entity.addParent(353, 69)
Entity.getTransform.setPosition(353, -0.87, -1.89, 0) 
Entity.getTransform.setScale(353, 2.25, 0.1, 1) 
Entity.addScript(353) 
Entity.addGUIText(353)
Entity.getGUIText.setTextString(353, "l")
Entity.getGUIText.setTextColor(353, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(353, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(353, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(354, 'SSAO Checkbox left' ) 
Entity.setActive(354 , true) 
Entity.addTag(354, "font") 
Entity.addParent(354, 69)
Entity.getTransform.setPosition(354, -0.895, -1.89, 0) 
Entity.getTransform.setScale(354, 2.25, 0.1, 1) 
Entity.addScript(354) 
Entity.addGUIText(354)
Entity.getGUIText.setTextString(354, "l")
Entity.getGUIText.setTextColor(354, 0.8, 0.8, 0.8, 0)
Entity.getGUIText.setFontType(354, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(354, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(355, 'SSAO Checkbox' ) 
Entity.setActive(355 , true) 
Entity.addTag(355, "font") 
Entity.addParent(355, 69)
Entity.getTransform.setPosition(355, -0.886, -1.897, 0) 
Entity.getTransform.setScale(355, 1.4, 0.1, 1) 
Entity.addScript(355) 
Entity.addGUIText(355)
Entity.getGUIText.setTextString(355, "o")
Entity.getGUIText.setTextColor(355, 2, 0, 0, 0)
Entity.getGUIText.setFontType(355, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(355, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(355) 
Entity.getScript.setPath(355, 'Content//scripts//checkboxSSAO.lua') 
Entity.addAABBCollider(355, 1)
Entity.getAABBCollider.addTag(355, 1, "GUI")
Entity.getAABBCollider.setHalfSize(355, 1, 0.025, 0.025, 0.025)
Entity.getAABBCollider.setPosition(355, 1, 0.0035, -0.02, 0)

------

Entity.New(36 , 'FXAA Control' ) 
Entity.setActive(36 , true) 
Entity.addTag(36 , "font") 
Entity.addParent(36, 69)
Entity.getTransform.setPosition(36, -1.17, -2.05, 0) 
Entity.getTransform.setScale(36, 2.25, 0.1, 1) 
Entity.addScript(36) 
Entity.addGUIText(36)
Entity.getGUIText.setTextString(36, "FXAA")
Entity.getGUIText.setTextColor(36, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(36, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(36, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

--[[ FXAA Checkbox ]]--

Entity.New(361, 'FXAA Checkbox top' ) 
Entity.setActive(361 , true) 
Entity.addTag(361, "font") 
Entity.addParent(361, 69)
Entity.getTransform.setPosition(361, -0.891, -2.02, 0) 
Entity.getTransform.setScale(361, 2.25, 0.1, 1) 
Entity.addScript(361) 
Entity.addGUIText(361)
Entity.getGUIText.setTextString(361, "-")
Entity.getGUIText.setTextColor(361, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(361, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(361, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(362, 'FXAA Checkbox bottom' ) 
Entity.setActive(362 , true) 
Entity.addTag(362, "font") 
Entity.addParent(362, 69)
Entity.getTransform.setPosition(362, -0.891, -2.057, 0) 
Entity.getTransform.setScale(362, 2.25, 0.1, 1) 
Entity.addScript(362) 
Entity.addGUIText(362)
Entity.getGUIText.setTextString(362, "-")
Entity.getGUIText.setTextColor(362, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(362, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(362, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(363, 'FXAA Checkbox right' ) 
Entity.setActive(363 , true) 
Entity.addTag(363, "font") 
Entity.addParent(363, 69)
Entity.getTransform.setPosition(363, -0.87, -2.04, 0) 
Entity.getTransform.setScale(363, 2.25, 0.1, 1) 
Entity.addScript(363) 
Entity.addGUIText(363)
Entity.getGUIText.setTextString(363, "l")
Entity.getGUIText.setTextColor(363, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(363, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(363, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(364, 'FXAA Checkbox left' ) 
Entity.setActive(364 , true) 
Entity.addTag(364, "font") 
Entity.addParent(364, 69)
Entity.getTransform.setPosition(364, -0.895, -2.04, 0) 
Entity.getTransform.setScale(364, 2.25, 0.1, 1) 
Entity.addScript(364) 
Entity.addGUIText(364)
Entity.getGUIText.setTextString(364, "l")
Entity.getGUIText.setTextColor(364, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(364, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(364, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(365, 'FXAA Checkbox' ) 
Entity.setActive(365 , true) 
Entity.addTag(365, "font") 
Entity.addParent(365, 69)
Entity.getTransform.setPosition(365, -0.886, -2.047, 0) 
Entity.getTransform.setScale(365, 1.4, 0.1, 1) 
Entity.addScript(365) 
Entity.addGUIText(365)
Entity.getGUIText.setTextString(365, "o")
Entity.getGUIText.setTextColor(365, 2, 0, 0, 0)
Entity.getGUIText.setFontType(365, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(365, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(365) 
Entity.getScript.setPath(365, 'Content//scripts//checkboxFXAA.lua') 
Entity.addAABBCollider(365, 1)
Entity.getAABBCollider.addTag(365, 1, "GUI")
Entity.getAABBCollider.setHalfSize(365, 1, 0.025, 0.025, 0.025)
Entity.getAABBCollider.setPosition(365, 1, 0.0035, -0.02, 0)

------

Entity.New(37 , 'Bloom Control' ) 
Entity.setActive(37 , true) 
Entity.addTag(37 , "font") 
Entity.addParent(37, 69)
Entity.getTransform.setPosition(37, -0.79, -1.9, 0) 
Entity.getTransform.setScale(37, 2.25, 0.1, 1) 
Entity.addScript(37) 
Entity.addGUIText(37)
Entity.getGUIText.setTextString(37, "Bloom")
Entity.getGUIText.setTextColor(37, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(37, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(37, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

--[[ Bloom Checkbox ]]--

Entity.New(371, 'Bloom Checkbox top' ) 
Entity.setActive(371 , true) 
Entity.addTag(371, "font") 
Entity.addParent(371, 69)
Entity.getTransform.setPosition(371, -0.511, -1.87, 0) 
Entity.getTransform.setScale(371, 2.25, 0.1, 1) 
Entity.addScript(371) 
Entity.addGUIText(371)
Entity.getGUIText.setTextString(371, "-")
Entity.getGUIText.setTextColor(371, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(371, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(371, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(372, 'Bloom Checkbox bottom' ) 
Entity.setActive(372 , true) 
Entity.addTag(372, "font") 
Entity.addParent(372, 69)
Entity.getTransform.setPosition(372, -0.511, -1.907, 0) 
Entity.getTransform.setScale(372, 2.25, 0.1, 1) 
Entity.addScript(372) 
Entity.addGUIText(372)
Entity.getGUIText.setTextString(372, "-")
Entity.getGUIText.setTextColor(372, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(372, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(372, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(373, 'Bloom Checkbox right' ) 
Entity.setActive(373 , true) 
Entity.addTag(373, "font") 
Entity.addParent(373, 69)
Entity.getTransform.setPosition(373, -0.49, -1.89, 0) 
Entity.getTransform.setScale(373, 2.25, 0.1, 1) 
Entity.addScript(373) 
Entity.addGUIText(373)
Entity.getGUIText.setTextString(373, "l")
Entity.getGUIText.setTextColor(373, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(373, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(373, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(374, 'Bloom Checkbox left' ) 
Entity.setActive(374 , true) 
Entity.addTag(374, "font") 
Entity.addParent(374, 69)
Entity.getTransform.setPosition(374, -0.515, -1.89, 0) 
Entity.getTransform.setScale(374, 2.25, 0.1, 1) 
Entity.addScript(374) 
Entity.addGUIText(374)
Entity.getGUIText.setTextString(374, "l")
Entity.getGUIText.setTextColor(374, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(374, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(374, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(375, 'Bloom Checkbox' ) 
Entity.setActive(375 , true) 
Entity.addTag(375, "font") 
Entity.addParent(375, 69)
Entity.getTransform.setPosition(375, -0.506, -1.897, 0) 
Entity.getTransform.setScale(375, 1.4, 0.1, 1) 
Entity.addScript(375) 
Entity.addGUIText(375)
Entity.getGUIText.setTextString(375, "o")
Entity.getGUIText.setTextColor(375, 2, 0, 0, 0)
Entity.getGUIText.setFontType(375, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(375, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(375) 
Entity.getScript.setPath(375, 'Content//scripts//checkboxBLOOM.lua') 
Entity.addAABBCollider(375, 1)
Entity.getAABBCollider.addTag(375, 1, "GUI")
Entity.getAABBCollider.setHalfSize(375, 1, 0.025, 0.025, 0.025)
Entity.getAABBCollider.setPosition(375, 1, 0.003, -0.02, 0)

------

Entity.New(38 , 'MB Control' ) 
Entity.setActive(38 , true) 
Entity.addTag(38 , "font") 
Entity.addParent(38, 69)
Entity.getTransform.setPosition(38, -0.79, -2.05, 0) 
Entity.getTransform.setScale(38, 2.25, 0.1, 1) 
Entity.addScript(38) 
Entity.addGUIText(38)
Entity.getGUIText.setTextString(38, "Motion Blur")
Entity.getGUIText.setTextColor(38, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(38, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(38, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

--[[ MB Checkbox ]]--

Entity.New(381, 'MB Checkbox top' ) 
Entity.setActive(381 , true) 
Entity.addTag(381, "font") 
Entity.addParent(381, 69)
Entity.getTransform.setPosition(381, -0.511, -2.02, 0) 
Entity.getTransform.setScale(381, 2.25, 0.1, 1) 
Entity.addScript(381) 
Entity.addGUIText(381)
Entity.getGUIText.setTextString(381, "-")
Entity.getGUIText.setTextColor(381, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(381, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(381, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(382, 'MB Checkbox bottom' ) 
Entity.setActive(382 , true) 
Entity.addTag(382, "font") 
Entity.addParent(382, 69)
Entity.getTransform.setPosition(382, -0.511, -2.057, 0) 
Entity.getTransform.setScale(382, 2.25, 0.1, 1) 
Entity.addScript(382) 
Entity.addGUIText(382)
Entity.getGUIText.setTextString(382, "-")
Entity.getGUIText.setTextColor(382, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(382, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(382, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(383, 'MB Checkbox right' ) 
Entity.setActive(383 , true) 
Entity.addTag(383, "font") 
Entity.addParent(383, 69)
Entity.getTransform.setPosition(383, -0.49, -2.04, 0) 
Entity.getTransform.setScale(383, 2.25, 0.1, 1) 
Entity.addScript(383) 
Entity.addGUIText(383)
Entity.getGUIText.setTextString(383, "l")
Entity.getGUIText.setTextColor(383, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(383, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(383, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(384, 'MB Checkbox left' ) 
Entity.setActive(384 , true) 
Entity.addTag(384, "font") 
Entity.addParent(384, 69)
Entity.getTransform.setPosition(384, -0.515, -2.04, 0) 
Entity.getTransform.setScale(384, 2.25, 0.1, 1) 
Entity.addScript(384) 
Entity.addGUIText(384)
Entity.getGUIText.setTextString(384, "l")
Entity.getGUIText.setTextColor(384, 0.7, 0.7, 0.7, 0)
Entity.getGUIText.setFontType(384, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(384, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor

Entity.New(385, 'MB Checkbox' ) 
Entity.setActive(385 , true) 
Entity.addTag(385, "font") 
Entity.addParent(385, 69)
Entity.getTransform.setPosition(385, -0.506, -2.047, 0) 
Entity.getTransform.setScale(385, 1.4, 0.1, 1) 
Entity.addScript(385) 
Entity.addGUIText(385)
Entity.getGUIText.setTextString(385, "o")
Entity.getGUIText.setTextColor(385, 2, 0, 0, 0)
Entity.getGUIText.setFontType(385, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(385, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(385) 
Entity.getScript.setPath(385, 'Content//scripts//checkboxMB.lua') 
Entity.addAABBCollider(385, 1)
Entity.getAABBCollider.addTag(385, 1, "GUI")
Entity.getAABBCollider.setHalfSize(385, 1, 0.025, 0.025, 0.025)
Entity.getAABBCollider.setPosition(385, 1, 0.003, -0.02, 0)

------


-- graphics high med low
Entity.New(39 , 'graphics Control' ) 
Entity.setActive(39 , true) 
Entity.addTag(39 , "font") 
Entity.addParent(39, 69)
Entity.getTransform.setPosition(39, -1.17, -1.75, 0) 
Entity.getTransform.setScale(39, 2.25, 0.1, 1) 
Entity.addScript(39) 
Entity.addGUIText(39)
Entity.getGUIText.setTextString(39, "Graphics")
Entity.getGUIText.setTextColor(39, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(39, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(39, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
  
Entity.New(395, 'graphics Checkbox' ) 
Entity.setActive(395 , true) 
Entity.addTag(395, "font") 
Entity.addParent(395, 69)
Entity.getTransform.setPosition(395, -0.908, -1.76, 0) 
Entity.getTransform.setScale(395, 1.4, 0.1, 1) 
Entity.addScript(395) 
Entity.addGUIText(395)
Entity.getGUIText.setTextString(395, "HIGH")
Entity.getGUIText.setTextColor(395, 2, 0, 0, 0)
Entity.getGUIText.setFontType(395, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(395, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(395) 
Entity.getScript.setPath(395, 'Content//scripts//graphicsCheckbox.lua') 
Entity.addAABBCollider(395, 1)
Entity.getAABBCollider.addTag(395, 1, "GUI")
Entity.getAABBCollider.setHalfSize(395, 1, 0.05, 0.025, 0.05)
Entity.getAABBCollider.setPosition(395, 1, 0.033, -0.02, 0)



-- shadow quality high med low
Entity.New(40 , 'shadow q Control' ) 
Entity.setActive(40 , true) 
Entity.addTag(40 , "font") 
Entity.addParent(40, 69)
Entity.getTransform.setPosition(40, -0.79, -1.75, 0) 
Entity.getTransform.setScale(40, 2.25, 0.1, 1) 
Entity.addScript(40) 
Entity.addGUIText(40)
Entity.getGUIText.setTextString(40, "Shadow")
Entity.getGUIText.setTextColor(40, 1, 0.5, 0, 0)
Entity.getGUIText.setFontType(40, "POLYGONFONT")
Entity.getGUIText.setTextMaterial(40, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
  
Entity.New(41, 'shadow q Checkbox' ) 
Entity.setActive(41 , true) 
Entity.addTag(41, "font") 
Entity.addParent(41, 69)
Entity.getTransform.setPosition(41, -0.53, -1.76, 0) 
Entity.getTransform.setScale(41, 1.4, 0.1, 1) 
Entity.addScript(41) 
Entity.addGUIText(41)
Entity.getGUIText.setTextString(41, "HIGH")
Entity.getGUIText.setTextColor(41, 2, 0, 0, 0)
Entity.getGUIText.setFontType(41, "FORCESQUARE")
Entity.getGUIText.setTextMaterial(41, 
  0.5, -- width
  0.005, -- edge
  0.55, -- borderwidth
  0.2, -- borderedge
  -0.00, -- oy
  0.00, -- ox
  0, 0, 0) -- outlinecolor
Entity.addScript(41) 
Entity.getScript.setPath(41, 'Content//scripts//shadowCheckbox.lua') 
Entity.addAABBCollider(41, 1)
Entity.getAABBCollider.addTag(41, 1, "GUI")
Entity.getAABBCollider.setHalfSize(41, 1, 0.05, 0.025, 0.05)
Entity.getAABBCollider.setPosition(41, 1, 0.033, -0.02, 0)











--[[ HEAD ]]--

Entity.New(400 , 'dragon head display' ) 
Entity.setActive(400 , true) 
Entity.getTransform.setPosition(400, 0, 1.25, 2) 
Entity.getTransform.setRotation(400, 0, 30, 0) 
Entity.getTransform.setScale(400, 1.5, 1.5, 2.0) 
Entity.addMeshRenderer(400) 
Entity.getMeshRenderer.setName(400, 'DRAGONHEAD') 
Entity.getMeshRenderer.setColor(400, 1.25, 0.5, 0.1) 
Entity.getMeshRenderer.setShininess(400, 64) 
Entity.getMeshRenderer.setEmissive(400, 0) 

Entity.New(401 , 'dragon horn display' ) 
Entity.setActive(401 , true) 
Entity.addParent(401, 400)
Entity.getTransform.setPosition(401, 0, 0, 0) 
Entity.getTransform.setRotation(401, 0, 0, 0) 
Entity.getTransform.setScale(401, 1.5, 1.5, 2.0) 
Entity.addMeshRenderer(401) 
Entity.getMeshRenderer.setName(401, 'DRAGONHEADHORN') 
Entity.getMeshRenderer.setColor(401, 0.1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(401, 64) 
Entity.getMeshRenderer.setEmissive(401, 0)

Entity.New(402 , 'dragon teeth display' ) 
Entity.setActive(402 , true) 
Entity.addParent(402, 400)
Entity.getTransform.setPosition(402, 0, 0, 0) 
Entity.getTransform.setRotation(402, 0, 0, 0) 
Entity.getTransform.setScale(402, 1.5, 1.5, 2.0) 
Entity.addMeshRenderer(402) 
Entity.getMeshRenderer.setName(402, 'DRAGONTEETH') 
Entity.getMeshRenderer.setColor(402, 0.1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(402, 64) 
Entity.getMeshRenderer.setEmissive(402, 0)


Entity.New(403 , 'dragon cube display' ) 
Entity.setActive(403 , true) 
Entity.addParent(403, 400)
Entity.getTransform.setPosition(403, 0, 0, 0) 
Entity.getTransform.setRotation(403, 0, 0, 0) 
Entity.getTransform.setScale(403, 1.5, 1.5, 2.0) 
Entity.addMeshRenderer(403) 
Entity.getMeshRenderer.setName(403, 'DRAGONPOWERCUBE') 
Entity.getMeshRenderer.setColor(403, 0.5, 0.5, 0.9) 
Entity.getMeshRenderer.setShininess(403, 64) 
Entity.getMeshRenderer.setEmissive(403, 1)


--[[ BODY ]]--

Entity.New(404 , 'dragon body display' ) 
Entity.setActive(404 , true) 
Entity.getTransform.setPosition(404, -5, 1, -2) 
Entity.getTransform.setRotation(404, 0, -45, 0) 
Entity.getTransform.setScale(404, 1, 1, 1) 
Entity.addMeshRenderer(404) 
Entity.getMeshRenderer.setName(404, 'DRAGONBODY') 
Entity.getMeshRenderer.setColor(404, 1.25, 0.5, 0.1) 
Entity.getMeshRenderer.setShininess(404, 64) 
Entity.getMeshRenderer.setEmissive(404, 0) 

Entity.New(405 , 'dragon body horn display' ) 
Entity.setActive(405 , true) 
Entity.addParent(405, 404)
Entity.getTransform.setPosition(405, 0, 0, 0) 
Entity.getTransform.setRotation(405, 0, 0, 0) 
Entity.getTransform.setScale(405, 1, 1, 1) 
Entity.addMeshRenderer(405) 
Entity.getMeshRenderer.setName(405, 'DRAGONBODY1HORN') 
Entity.getMeshRenderer.setColor(405, 0.1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(405, 64) 
Entity.getMeshRenderer.setEmissive(405, 0) 


--[[ BODY2 ]]--

Entity.New(407 , 'dragon body display' ) 
Entity.setActive(407 , true) 
Entity.getTransform.setPosition(407, 7, 1, -9) 
Entity.getTransform.setRotation(407, 0, -110, 0) 
Entity.getTransform.setScale(407, 1, 1, 1) 
Entity.addMeshRenderer(407) 
Entity.getMeshRenderer.setName(407, 'DRAGONBODY') 
Entity.getMeshRenderer.setColor(407, 1.25, 0.5, 0.1) 
Entity.getMeshRenderer.setShininess(407, 64) 
Entity.getMeshRenderer.setEmissive(407, 0) 

Entity.New(406 , 'dragon body horn display' ) 
Entity.setActive(406 , true) 
Entity.addParent(406, 407)
Entity.getTransform.setPosition(406, 0, 0, 0) 
Entity.getTransform.setRotation(406, 0, 0, 0) 
Entity.getTransform.setScale(406, 1, 1, 1) 
Entity.addMeshRenderer(406) 
Entity.getMeshRenderer.setName(406, 'DRAGONBODY1HORN') 
Entity.getMeshRenderer.setColor(406, 0.1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(406, 64) 
Entity.getMeshRenderer.setEmissive(406, 0) 



--[[ TAIL ]]--

Entity.New(408 , 'dragon tail display' ) 
Entity.setActive(408 , true) 
Entity.getTransform.setPosition(408, -8, 1, 7) 
Entity.getTransform.setRotation(408, 0, 70, 0) 
Entity.getTransform.setScale(408, 1, 1, 1) 
Entity.addMeshRenderer(408) 
Entity.getMeshRenderer.setName(408, 'DRAGONTAIL') 
Entity.getMeshRenderer.setColor(408, 1.25, 0.5, 0.1) 
Entity.getMeshRenderer.setShininess(408, 64) 
Entity.getMeshRenderer.setEmissive(408, 0) 

Entity.New(409 , 'dragon body horn display' ) 
Entity.setActive(409 , true) 
Entity.addParent(409, 408)
Entity.getTransform.setPosition(409, 0, 0, 0) 
Entity.getTransform.setRotation(409, 0, 0, 0) 
Entity.getTransform.setScale(409, 1, 1, 1) 
Entity.addMeshRenderer(409) 
Entity.getMeshRenderer.setName(409, 'DRAGONTAILHORN') 
Entity.getMeshRenderer.setColor(409, 0.1, 0.1, 0.1) 
Entity.getMeshRenderer.setShininess(409, 64) 
Entity.getMeshRenderer.setEmissive(409, 0) 

--[[ Camera ]]--

Camera.setPosition(-6.83085, 5.7, 2.723) 
Camera.setTarget(-6.83085, -0.8, 17.523) 
Camera.setUp(0, 1, 0) 
Camera.setCamMode(0) -- FPS
Camera.setMouseControl(true)
Camera.setLookingDir(0, -1, 0.8) 
Camera.setMouseSentivity(125) 
Camera.setZoomDistance(16.5) 
Camera.setPitchLimit(80) 
