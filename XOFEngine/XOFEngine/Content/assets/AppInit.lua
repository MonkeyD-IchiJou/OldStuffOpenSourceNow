

function Init()

	App.window.setSize(1280, 720)
	App.window.setFullScreen(false)

	App.scene.create("Playstation", "Playstation_Splash.lua")
	App.scene.create("OuterHeaven", "OuterHeaven_Splash.lua")
	App.scene.create("Title", "Title.lua")
	App.scene.create("Reward", "Reward.lua")
	
	App.scene.create("Level1", "jou.lua")
	App.scene.create("Level2", "Junsen.lua")
	App.scene.create("Level3", "jin.lua")
	App.scene.create("Level4", "gerald.lua")
	
	
	-- make it an active scene
	App.scene.LoadScene("Playstation")

	
	require("Content//assets//GraphicsOption")

end
